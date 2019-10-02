#include "trans_est.h"
#include "spectrum.h"
#include "sampler.h"

namespace pbrt
{

Spectrum NextFlight_Ratio::Tr(const Ray& ray,
                              Sampler& sampler,
                              Float tMin,
                              Float tMax,
                              Float maxD) const
{
    sampler.BeforeTransmittanceSample();

    Float t = tMin;

    Float bMa = tMax - tMin;

    Float invMaxD = 1.0 / maxD;

    Spectrum Tr = Spectrum(exp(-maxD * bMa * sigma_t));

    Spectrum runningProd = Spectrum(1.0);

    while (true) {
        t -= std::log(1 - sampler.Get1D()) * invMaxD / sigma_t;

        if (t >= tMax) return Tr;

        Spectrum dense = density->D(ray(t));

        runningProd *= (Spectrum(maxD) - dense) * invMaxD;

        Tr += runningProd * exp(-maxD * sigma_t * (tMax - t));
    }

    return Spectrum(0.0);
}

}
