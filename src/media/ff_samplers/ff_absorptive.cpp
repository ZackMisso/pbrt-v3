#include "ff_sampler.h"
#include "interaction.h"

namespace pbrt
{

Spectrum FF_Absorptive_Sampler::Sample(const Ray& ray,
                                       const Ray& rWorld,
                                       Sampler& sampler,
                                       MemoryArena& arena,
                                       MediumInteraction* mi,
                                       Float tMin,
                                       Float tMax) const
{
    sampler.BeforeFreeFlightSample();

    // absorptive mediums are not sampled, only transmittance is returned

    return Spectrum(1.f);
}

}
