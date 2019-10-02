#include "trans_est.h"
#include "spectrum.h"
#include "sampler.h"

namespace pbrt
{

Spectrum Pseries_Ratio::Tr(const Ray& ray,
                           Sampler& sampler,
                           Float tMin,
                           Float tMax,
                           Float maxD) const
{
    sampler.BeforeTransmittanceSample();

    Float tau = maxD * (tMax - tMin) * sigma_t;
    Float sample = sampler.Get1D();
    Float val = exp(-tau);
    Float cdf = val;
    Float prob = val;
    Spectrum Tr = Spectrum(1.0);
    Float invMaxD = 1.0 / maxD;
    Float i = 1.0;

    while(cdf < sample)
    {
        Float x = sampler.Get1D() * (tMax - tMin) + tMin;
        Spectrum dense = density->D(ray(x));
        Tr *= (Spectrum(maxD) - dense) * invMaxD;
        prob *= tau / i;

        cdf += prob;
        i += 1.0;
    }

    return Tr;
}

}
