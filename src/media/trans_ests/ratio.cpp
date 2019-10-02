#include "trans_est.h"
#include "spectrum.h"
#include "sampler.h"

namespace pbrt
{

Spectrum Ratio::Tr(const Ray& ray,
                   Sampler& sampler,
                   Float tMin,
                   Float tMax,
                   Float maxD) const
{
    sampler.BeforeTransmittanceSample();

    Float invMaxD = 1.0 / maxD;

    // Perform ratio tracking to estimate the transmittance value
    Spectrum Tr = Spectrum(1.0);
    Float t = tMin;

    while (true)
    {
        t -= std::log(1 - sampler.Get1D()) * invMaxD / sigma_t;
        if (t >= tMax) break;

        Spectrum dens = density->D(ray(t));

        Tr *= (Spectrum(maxD) - dens) * invMaxD;
    }

    return Tr;
}

}
