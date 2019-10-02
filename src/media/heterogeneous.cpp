#include "heterogeneous.h"
#include "samplers/random.h"

namespace pbrt
{

long HeterogeneousMedium::nTrCalls = 0;
long HeterogeneousMedium::nDensityCalls = 0;

HeterogeneousMedium::HeterogeneousMedium(const Spectrum& sigma_a,
                                         const Spectrum& sigma_s,
                                         Float g,
                                         T_Estimator* t_est,
                                         DensityFunction* density,
                                         MinorantFunction* minorant,
                                         MajorantFunction* majorant,
                                         FF_Sampler* ff,
                                         const Transform& WorldToMedium,
                                         const Bounds3f b)
    : sigma_a(sigma_a),
      sigma_s(sigma_s),
      sigma_t(sigma_s + sigma_a),
      g(g),
      t_est(t_est),
      density(density),
      minorant(minorant),
      majorant(majorant),
      ff_sampler(ff),
      WorldToMedium(Inverse(WorldToMedium)),
      mediumBounds(b)
{
    density->preProcess(WorldToMedium,
                        mediumBounds);

    t_est->minorant = minorant;
    t_est->majorant = majorant;
    t_est->density = density;
    t_est->sigma_t = sigma_t[0];
    t_est->preProcess();

    ff_sampler->mediumRef = this;
    ff_sampler->majorant = majorant;
    ff_sampler->density = density;
    ff_sampler->sigma_s = sigma_s[0];
    ff_sampler->sigma_t = sigma_t[0];
    ff_sampler->g = g;

    nTrCalls = 0;
    nDensityCalls = 0;

    t_est->preProcess();
}

HeterogeneousMedium::~HeterogeneousMedium()
{
    delete density;
    delete t_est;
    delete majorant;
    delete minorant;
    delete ff_sampler;
}

void HeterogeneousMedium::setMajScale(Float scale)
{
    majorant->setScale(scale);
}

Spectrum HeterogeneousMedium::Tr(const Ray& rWorld, Sampler& sampler) const
{
    ProfilePhase _(Prof::MediumTr);
    ++nTrCalls;

    Ray ray;
    Float tMin, tMax;

    // generate a transformed ray and bounds
    bool outsideBounds = TransformToLocalSpace(rWorld, ray, tMin, tMax);

    // check bounds
    if (outsideBounds)
    {
        return Spectrum(1.f);
    }

    // calculate transmittance using the specified estimator
    density->clearDensityCalls();

    Spectrum tr = t_est->Tr(ray, sampler, tMin, tMax);

    nDensityCalls += density->getDensityCalls();

    return tr;
}

Spectrum HeterogeneousMedium::LocalTr(const Ray& ray,
                                      Sampler& sampler,
                                      Float tMin,
                                      Float tMax) const
{
    ++nTrCalls;

    density->clearDensityCalls();

    Spectrum tr = t_est->Tr(ray, sampler, tMin, tMax);

    nDensityCalls += density->getDensityCalls();

    return tr;
}

Spectrum HeterogeneousMedium::Sample(const Ray& rWorld,
                                     Sampler& ff_samp,
                                     Sampler& trans_samp,
                                     MemoryArena& arena,
                                     MediumInteraction* mi) const
{
    ProfilePhase _(Prof::MediumSample);

    Ray ray;
    Float tMin, tMax;

    // generate a transformed ray and bounds
    bool outsideBounds = TransformToLocalSpace(rWorld, ray, tMin, tMax);

    // check bounds
    if (outsideBounds) return Spectrum(1.f);

    // return the sampled contribution and medium interaction
    Spectrum ret = ff_sampler->Sample(ray,
                                      rWorld,
                                      ff_samp,
                                      arena,
                                      mi,
                                      tMin,
                                      tMax);

    // multiply by transmittance if ff sampling method requires it
    if (ff_sampler->RequiresTr())
    {
        ret *= LocalTr(ray, trans_samp, tMin, tMax);
    }

    return ret;
}

// This returns true if the ray is outside the medium bounds
bool HeterogeneousMedium::TransformToLocalSpace(const Ray& rWorld,
                                                Ray& ray,
                                                Float& tMin,
                                                Float& tMax) const
{
    // I do not know why this is a thing, but it is
    if (rWorld.d.LengthSquared() == 0.0) return true;

    // transform the ray to medium space
    ray = WorldToMedium(Ray(rWorld.o,
                        Normalize(rWorld.d),
                        rWorld.tMax * rWorld.d.Length()));

    if (!mediumBounds.IntersectP(ray, &tMin, &tMax))
    {
        return true;
    }

    return false;
}

}
