#include "integrators/volpath_recursive.h"
#include "bssrdf.h"
#include "camera.h"
#include "film.h"
#include "interaction.h"
#include "paramset.h"
#include "scene.h"
#include "stats.h"

namespace pbrt
{

STAT_INT_DISTRIBUTION("Integrator/Path length", pathLength);
STAT_COUNTER("Integrator/Volume interactions", volumeInteractions);
STAT_COUNTER("Integrator/Surface interactions", surfaceInteractions);

void VolPathRecursiveIntegrator::Preprocess(const Scene& scene, Sampler& sampler)
{
    lightDistribution = CreateLightSampleDistribution(lightSampleStrategy, scene);
}

Spectrum VolPathRecursiveIntegrator::Li(const RayDifferential& r,
                                        const Scene& scene,
                                        Sampler& sampler,
                                        Sampler& trans_sampler,
                                        Sampler& ff_sampler,
                                        MemoryArena& arena,
                                        int depth,
                                        int maxBounces,
                                        Spectrum beta,
                                        Float etaScale,
                                        bool specularBounce) const
{
    ProfilePhase p(Prof::SamplerIntegratorLi);

    Spectrum L(0.f);

    RayDifferential ray(r);

    SurfaceInteraction isect;
    bool foundIntersection = scene.Intersect(ray, &isect);

    MediumInteraction mi;
    if (ray.medium)
    {
        beta *= ray.medium->Sample(ray,
                                   ff_sampler,
                                   trans_sampler,
                                   arena,
                                   &mi);
    }

    if (beta.IsBlack())
    {
        if (beta[0] < 0.0) std::cout << "what the frick" << std::endl;
        return L;
    }

    if (mi.IsValid())
    {
        if (depth <= 0)
        {
            return L;
        }

        ++volumeInteractions;

        const Distribution1D* lightDistrib = lightDistribution->Lookup(mi.p);

        for (int i = 0; i < int(scene.lights.size()); ++i)
        {
            const std::shared_ptr<Light> &light = scene.lights[i];
            Point2f uLight = sampler.Get2D();
            Point2f uScattering = sampler.Get2D();
            L += beta * EstimateDirect(mi,
                                       uScattering,
                                       *light,
                                       uLight,
                                       scene,
                                       sampler,
                                       trans_sampler,
                                       arena,
                                       true);
        }

        Vector3f wo = -ray.d;
        Vector3f wi;
        mi.phase->Sample_p(wo, &wi, sampler.Get2D());
        ray = mi.SpawnRay(wi);
        specularBounce = false;

        Spectrum rrBeta = beta * etaScale;

        if (rrBeta.MaxAbsComponentValue() < rrThreshold && maxBounces - depth > 3)
        {
            Float q = std::max((Float)0.05, 1.0 - rrBeta.MaxAbsComponentValue());
            if (sampler.Get1D() < q)
            {
                return L;
            }
            beta /= 1 - q;
            #if LOGGING
                DCHECK(std::isinf(beta.y()) == false);
            #endif
        }

        return L + Li(ray,
                      scene,
                      sampler,
                      trans_sampler,
                      ff_sampler,
                      arena,
                      depth-1,
                      maxBounces,
                      beta,
                      etaScale,
                      specularBounce);
    }
    else
    {
        ++surfaceInteractions;

        if (depth == maxBounces || specularBounce)
        {
            if (foundIntersection)
            {
                L += beta * isect.Le(-ray.d);
            }
            else
            {
                for (const auto& light : scene.infiniteLights)
                {
                    L += beta * light->Le(ray);
                }
            }
        }

        if (!foundIntersection || depth <= 0)
        {
            return L;
        }

        // this is probably what should be changed
        isect.ComputeScatteringFunctions(ray, arena, true);

        if (!isect.bsdf)
        {
            ray = isect.SpawnRay(ray.d);

            return L + Li(ray,
                          scene,
                          sampler,
                          trans_sampler,
                          ff_sampler,
                          arena,
                          depth,
                          maxBounces,
                          beta,
                          etaScale,
                          specularBounce);
        }

        for (int i = 0; i < int(scene.lights.size()); ++i)
        {
            const std::shared_ptr<Light> &light = scene.lights[i];
            Point2f uLight = sampler.Get2D();
            Point2f uScattering = sampler.Get2D();
            L += beta * EstimateDirect(isect,
                                       uScattering,
                                       *light,
                                       uLight,
                                       scene,
                                       sampler,
                                       trans_sampler,
                                       arena,
                                       true);
        }

        // ignoring all russian roulette
        // NOTE: THIS ALWAYS OCCURS NOW
        if (maxBounces - depth < 5 || true)
        {
            Vector3f wo_refl = -ray.d;
            Vector3f wo_refr = -ray.d;

            Vector3f wi_refl;
            Vector3f wi_refr;

            Float dummy_var;

            BxDFType flags_refl;
            BxDFType flags_refr;

            Spectrum f_refl = isect.bsdf->Sample_refl(wo_refl,
                                                      &wi_refl,
                                                      sampler.Get2D(),
                                                      &dummy_var,
                                                      &flags_refl);

            Spectrum f_refr = isect.bsdf->Sample_refr(wo_refr,
                                                      &wi_refr,
                                                      sampler.Get2D(),
                                                      &dummy_var,
                                                      &flags_refr);

            Spectrum refl_contrib = Spectrum(0.0);
            Spectrum refr_contrib = Spectrum(0.0);

            if (!f_refl.IsBlack())
            {
                Spectrum beta_refl = beta;
                beta_refl *= f_refl * AbsDot(wi_refl, isect.shading.n);
                Float etaScale_refl = etaScale;
                bool specularBounce_refl = (flags_refl & BSDF_SPECULAR) != 0;

                if ((flags_refl & BSDF_SPECULAR) && (flags_refl & BSDF_TRANSMISSION))
                {
                    Float eta = isect.bsdf->eta;
                    etaScale_refl *= (Dot(wo_refl, isect.n) > 0) ? (eta * eta) : 1.0 / (eta * eta);
                }

                RayDifferential ray_refl = isect.SpawnRay(wi_refl);
                Spectrum rrBeta_refl = beta_refl * etaScale_refl;

                refl_contrib = Li(ray_refl,
                                  scene,
                                  sampler,
                                  trans_sampler,
                                  ff_sampler,
                                  arena,
                                  depth-1,
                                  maxBounces,
                                  beta_refl,
                                  etaScale_refl,
                                  specularBounce_refl);
            }

            if (!f_refr.IsBlack())
            {
                Spectrum beta_refr = beta;
                Float etaScale_refr = etaScale;
                beta_refr *= f_refr * AbsDot(wi_refr, isect.shading.n);
                bool specularBounce_refr = (flags_refr & BSDF_SPECULAR) != 0;

                if ((flags_refr & BSDF_SPECULAR) && (flags_refr & BSDF_TRANSMISSION))
                {
                    Float eta = isect.bsdf->eta;
                    etaScale_refr *= (Dot(wo_refr, isect.n) > 0) ? (eta * eta) : 1.0 / (eta * eta);
                }

                RayDifferential ray_refr = isect.SpawnRay(wi_refr);
                Spectrum rrBeta_refr = beta_refr * etaScale_refr;

                refr_contrib = Li(ray_refr,
                                  scene,
                                  sampler,
                                  trans_sampler,
                                  ff_sampler,
                                  arena,
                                  depth-1,
                                  maxBounces,
                                  beta_refr,
                                  etaScale_refr,
                                  specularBounce_refr);
            }

            return L + refl_contrib + refr_contrib;
        }
    }

    Spectrum rrBeta = beta * etaScale;
    if (rrBeta.MaxAbsComponentValue() < rrThreshold && maxBounces - depth > 3)
    {
        Float q = std::max((Float)0.05, 1.0 - rrBeta.MaxAbsComponentValue());
        if (sampler.Get1D() < q)
        {
            return L;
        }
        beta /= 1 - q;
        #if LOGGING
            DCHECK(std::isinf(beta.y()) == false);
        #endif
    }

    return L + Li(ray,
                  scene,
                  sampler,
                  trans_sampler,
                  ff_sampler,
                  arena,
                  depth-1,
                  maxBounces,
                  beta,
                  etaScale,
                  specularBounce);
}

Spectrum VolPathRecursiveIntegrator::Li(const RayDifferential& r,
                                        const Scene& scene,
                                        Sampler& sampler,
                                        Sampler& trans_sampler,
                                        Sampler& ff_sampler,
                                        MemoryArena& arena,
                                        int depth) const
{
    Spectrum L = Li(r,
                    scene,
                    sampler,
                    trans_sampler,
                    ff_sampler,
                    arena,
                    maxDepth,
                    maxDepth,
                    Spectrum(1.0),
                    1.0,
                    false);

    return L;
}

VolPathRecursiveIntegrator* CreateVolPathRecursiveIntegrator(const ParamSet& params,
                                                             std::shared_ptr<Sampler> sampler,
                                                             std::shared_ptr<const Camera> camera)
{
    int maxDepth = params.FindOneInt("maxdepth", 5);
    long maxSeconds = (long)params.FindOneInt("maxSeconds", 100000);
    long maxExtCalls = (long)params.FindOneLong("maxExtCalls", -1);
    std::string trans_sampler = params.FindOneString("trans_sampler", "independent");
    std::string ff_sampler = params.FindOneString("ff_sampler", "independent");
    bool ff_correlated = params.FindOneBool("ff_correlated", false);
    bool multithreaded = params.FindOneBool("multithreaded", false);
    int np;
    const int *pb = params.FindInt("pixelbounds", &np);
    Bounds2i pixelBounds = camera->film->GetSampleBounds();

    if (pb) {
        if (np != 4)
            Error("Expected four values for \"pixelbounds\" parameter. Got %d.",
                  np);
        else {
            pixelBounds = Intersect(pixelBounds,
                                    Bounds2i{{pb[0], pb[2]}, {pb[1], pb[3]}});
            if (pixelBounds.Area() == 0)
                Error("Degenerate \"pixelbounds\" specified.");
        }
    }

    Float rrThreshold = params.FindOneFloat("rrthreshold", 1.);

    std::string lightStrategy =
        params.FindOneString("lightsamplestrategy", "uniform");

    return new VolPathRecursiveIntegrator(maxDepth,
                                          camera,
                                          sampler,
                                          pixelBounds,
                                          maxSeconds,
                                          maxExtCalls,
                                          trans_sampler,
                                          ff_sampler,
                                          ff_correlated,
                                          rrThreshold,
                                          lightStrategy,
                                          multithreaded);
}

}
