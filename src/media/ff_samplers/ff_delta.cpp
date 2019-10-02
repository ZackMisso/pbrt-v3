#include "ff_sampler.h"
#include "interaction.h"

namespace pbrt
{

Spectrum FF_Trans_Sampler::Sample(const Ray& ray,
                                  const Ray& rWorld,
                                  Sampler& sampler,
                                  MemoryArena& arena,
                                  MediumInteraction* mi,
                                  Float tMin,
                                  Float tMax) const
{
    sampler.BeforeFreeFlightSample();
    Float invMaxDensity = 1.0;

    // Run delta-tracking iterations to sample a medium interaction
    Float t = tMin;
    while (true) {
        t -= std::log(1 - sampler.Get1D()) * invMaxDensity / sigma_t;
        if (t >= tMax) break;

        Float dense = ThreeWiseMax(density->D(ray(t))[0],
                                   density->D(ray(t))[1],
                                   density->D(ray(t))[2]);

        if (dense * invMaxDensity > sampler.Get1D()) {
            // Populate _mi_ with medium interaction information and return
            PhaseFunction *phase = ARENA_ALLOC(arena, HenyeyGreenstein)(g);
            *mi = MediumInteraction(rWorld(t),
                                    -rWorld.d,
                                    rWorld.time,
                                    mediumRef,
                                    phase,
                                    ray,
                                    t,
                                    tMin);

            return sigma_s / sigma_t;
        }
    }

    return Spectrum(1.f);
}

}
