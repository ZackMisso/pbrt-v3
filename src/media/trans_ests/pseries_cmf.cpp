#include "trans_est.h"
#include "spectrum.h"
#include "sampler.h"

namespace pbrt
{

Spectrum Pseries_CMF::Tr(const Ray& ray,
                         Sampler& sampler,
                         Float tMin,
                         Float tMax,
                         Float maxD) const
{
    sampler.BeforeTransmittanceSample();

    Float runningCDF = 0.0;
    Float bMa = tMax - tMin;
    Float i = 1.0;
    Float pdf = sigma_t * bMa;
    Spectrum W = (1.0);
    Float tau = pdf * maxD;
    Spectrum Tr = Spectrum(0.0);

    Float exponent = exp(-tau);
    double goal = 0.99;
    Float lastPDF = exponent;

    Float rr;
    do
    {
        rr = sampler.Get1D();
    } while (rr == 0.0);

    while (runningCDF < goal)
    {
        Float tmpT = sampler.Get1D() * bMa + tMin;
        runningCDF += lastPDF;
        Float invI = 1.0 / i;
        Spectrum dense = density->D(ray(tmpT));
        Spectrum wi = invI * pdf * (Spectrum(maxD) - dense);
        lastPDF *= tau * invI;
        Tr += W;
        W *= wi;
        i += 1.0;
    }

    while (true)
    {
        // double accept = 1.0 - lastPDF / (1.0 - runningCDF);
        // double accept = 0.8;
        double accept = tau / i;

        Tr += W;

        if (accept <= rr) break;

        rr /= accept;

        runningCDF += lastPDF;

        Float tmpT = tMin + sampler.Get1D() * bMa;
        Float invI = 1.0 / i;
        Spectrum dense = density->D(ray(tmpT));
        Spectrum wi = invI * (Spectrum(maxD) - dense) * pdf;

        lastPDF *= tau * invI;
        W *= (wi / accept);
        i += 1.0;
    }

    return (Tr * exponent);
}

}
