#pragma once

#include "pbrt.h"
#include "integrator.h"
#include "lightdistrib.h"

namespace pbrt
{

class VolPathRecursiveIntegrator : public SamplerIntegrator
{
public:
    VolPathRecursiveIntegrator(int maxDepth,
                               std::shared_ptr<const Camera> camera,
                               std::shared_ptr<Sampler> sampler,
                               const Bounds2i& pixelBounds,
                               long maxSeconds,
                               long maxExtCalls,
                               std::string trans_sampler = "independent",
                               std::string ff_sampler = "independent",
                               bool ff_correlated = false,
                               Float rrThreshold = 1,
                               const std::string& lightSampleStrategy = "spatial",
                               bool multithreaded = false)
        : SamplerIntegrator(camera,
                            sampler,
                            pixelBounds,
                            maxSeconds,
                            maxExtCalls,
                            trans_sampler,
                            ff_sampler,
                            ff_correlated,
                            multithreaded),
        maxDepth(maxDepth),
        rrThreshold(rrThreshold),
        lightSampleStrategy(lightSampleStrategy) { }

    void Preprocess(const Scene& scene, Sampler& sampler);

    virtual Spectrum Li(const RayDifferential &ray,
                        const Scene &scene,
                        Sampler &sampler,
                        MemoryArena &arena,
                        int depth = 0) const
    {
        return Li(ray,
                  scene,
                  sampler,
                  sampler,
                  sampler,
                  arena,
                  depth);
    }

    Spectrum Li(const RayDifferential& ray,
                const Scene& scene,
                Sampler& sampler,
                Sampler& trans_sampler,
                Sampler& ff_sampler,
                MemoryArena& arena,
                int depth) const;

    Spectrum Li(const RayDifferential& ray,
                const Scene& scene,
                Sampler& sampler,
                Sampler& trans_sampler,
                Sampler& ff_sampler,
                MemoryArena& arena,
                int depth,
                int maxBounces,
                Spectrum beta,
                Float etaScale,
                bool specularBounce) const;

private:
    const int maxDepth;
    const Float rrThreshold;
    const std::string lightSampleStrategy;
    std::unique_ptr<LightDistribution> lightDistribution;
};

VolPathRecursiveIntegrator* CreateVolPathRecursiveIntegrator(
        const ParamSet& params,
        std::shared_ptr<Sampler> sampler,
        std::shared_ptr<const Camera> camera
);

}
