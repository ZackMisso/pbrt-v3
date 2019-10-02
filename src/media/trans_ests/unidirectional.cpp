#include "trans_est.h"
#include "spectrum.h"
#include "sampler.h"

namespace pbrt
{

Spectrum Unidirectional::Tr(const Ray& ray,
                            Sampler& sampler,
                            Float tMin,
                            Float tMax,
                            Float maxD) const
{
    sampler.BeforeTransmittanceSample();

    Float t = tMin;

    Float bMa = tMax - tMin;

    Float invMaxD = 1.0 / maxD;

    Spectrum Tr = 0.0;
    Spectrum weight = 1.0;

    Spectrum densityA = 1.0;

    while (true)
    {
        Float newt = t - std::log(1 - sampler.Get1D()) * invMaxD / sigma_t;

        Float val = exp(-maxD * sigma_t * (tMax - t));

        Float nfrProb = 1.0;
        Float ratProb = val;
        Float contrNFR = val / (nfrProb + ratProb);
        Float contrRat = 1.0 / (nfrProb + ratProb);

        if (newt >= tMax)
        {
            Tr += weight * (contrNFR * nfrProb + contrRat * ratProb);
            break;
        }

        Tr += weight * (contrNFR * nfrProb);

        t = newt;

        densityA = density->D(ray(t));

        weight *= (Spectrum(maxD) - densityA) * invMaxD;
    }

    return Tr;
}

}
