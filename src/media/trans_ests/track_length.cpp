#include "trans_est.h"
#include "spectrum.h"
#include "sampler.h"

namespace pbrt
{

Spectrum Track_Length::Tr(const Ray& ray,
                          Sampler& sampler,
                          Float tMin,
                          Float tMax,
                          Float maxD) const
{
    sampler.BeforeTransmittanceSample();

    Float t = tMin;

    Float invMaxD = 1.0 / maxD;

    Spectrum ret = Spectrum(1.0);

    while (true) {
        t -= std::log(1 - sampler.Get1D()) * invMaxD / sigma_t;
        if (t >= tMax) break;

        Spectrum dense = density->D(ray(t));

        Float rrOne = sampler.Get1D();

        if (rrOne <= dense[0] * invMaxD) ret[0] = 0.0;
        if (rrOne <= dense[1] * invMaxD) ret[1] = 0.0;
        if (rrOne <= dense[2] * invMaxD) ret[2] = 0.0;
    }

    return ret;
}

}
