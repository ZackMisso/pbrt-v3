#include "trans_est.h"
#include "spectrum.h"
#include "sampler.h"

namespace pbrt
{

Spectrum Pseries_NextFlight_Ratio::Tr(const Ray& ray,
                                      Sampler& sampler,
                                      Float tMin,
                                      Float tMax,
                                      Float maxD) const
{
    sampler.BeforeTransmittanceSample();

    Float tau = maxD * (tMax - tMin) * sigma_t;
    Float sample = sampler.Get1D();
    Float prob = exp(-tau);
    Float cdf = prob;
    Spectrum Tr = Spectrum(prob);
    Spectrum prod = Tr;
    Float i = 1.0;

    while(cdf < sample)
    {
        Float x = sampler.Get1D() * (tMax - tMin) + tMin;
        Spectrum dense = density->D(ray(x));
        prod *= (Spectrum(maxD) - dense) * (1.0 / i) * sigma_t * (tMax - tMin);
        Tr += prod / (1.0 - cdf);
        prob *= tau / i;

        cdf += prob;
        i += 1.0;
    }

    return Tr;
}

}
