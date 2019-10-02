#include "trans_est.h"
#include "spectrum.h"
#include "sampler.h"

namespace pbrt
{

struct BidirPath
{
    BidirPath(int i, int j)
    {
        end_i = i;
        end_j = j;
    }

    int end_i;
    int end_j;
};

Spectrum Bidirectional::Tr(const Ray& ray,
                           Sampler& sampler,
                           Float tMin,
                           Float tMax,
                           Float maxD) const
{
    sampler.BeforeTransmittanceSample();

    // Only unidirectional paths
    Spectrum Tr = 0.0;

    Float invMaxD = 1.0 / maxD;

    Float y = tMin;

    std::vector<Float> a2b = std::vector<Float>();
    std::vector<Float> b2a = std::vector<Float>();

    a2b.push_back(tMin);
    do {
        y -= std::log(1.0 - sampler.Get1D()) * invMaxD / sigma_t;

        if (y >= tMax) break;

        a2b.push_back(y);
    } while (true);
    a2b.push_back(tMax);

    y = tMax;

    b2a.push_back(tMax);
    do {
        y += std::log(1.0 - sampler.Get1D()) * invMaxD / sigma_t;

        if (y <= tMin) break;

        b2a.push_back(y);
    } while (true);
    b2a.push_back(tMin);

    double majTmp = -maxD * sigma_t;

    double val = exp(majTmp * (tMax - tMin));

    std::vector<Spectrum> extValsA2B = std::vector<Spectrum>();
    std::vector<Spectrum> extValsB2A = std::vector<Spectrum>();

    std::vector<Spectrum> densitiesA2B = std::vector<Spectrum>();
    std::vector<Spectrum> densitiesB2A = std::vector<Spectrum>();

    std::vector<Float> expB2A = std::vector<Float>();
    std::vector<Float> expA2B = std::vector<Float>();

    Spectrum densityA = density->D(ray(tMin));
    Spectrum densityB = density->D(ray(tMax));
    Spectrum lastDensity = densityA;

    extValsA2B.push_back(Spectrum(-1.0)); // a
    densitiesA2B.push_back(densityA);
    for (int i = 1; i < a2b.size() - 1; ++i) {
        Spectrum dense = density->D(ray(a2b[i]));
        densitiesA2B.push_back(dense);
        Spectrum ex = (Spectrum(maxD) - dense) / maxD;
        extValsA2B.push_back(ex);
        Float dist = a2b[i] - a2b[i - 1];
        Float tau_bar = dist * maxD * sigma_t;
        Float tau = dist * (dense[0] + lastDensity[0]) / 2.0 * sigma_t;
        lastDensity = dense;
        Float ratio = 1.0;
        expA2B.push_back(ratio * val / exp(majTmp * (dist)));
    }
    densitiesA2B.push_back(densityB);
    expA2B.push_back(val / exp(majTmp * (a2b[a2b.size() - 1] - a2b[a2b.size() - 2])));
    extValsA2B.push_back(Spectrum(-1.0)); // b

    lastDensity = densityB;
    densitiesB2A.push_back(densityB);
    extValsB2A.push_back(Spectrum(-1.0)); // b
    for (int i = 1; i < b2a.size() - 1; ++i) {
        Spectrum dense = density->D(ray(b2a[i]));
        densitiesB2A.push_back(dense);
        Spectrum ex = (Spectrum(maxD) - dense) / maxD;
        extValsB2A.push_back(ex);
        Float dist = b2a[i - 1] - b2a[i];
        Float tau_bar = dist * maxD * sigma_t;
        Float tau = dist * (dense[0] + lastDensity[0]) / 2.0 * sigma_t;
        lastDensity = dense;
        Float ratio = 1.0;
        expB2A.push_back(ratio * val / exp(majTmp * (dist)));
    }
    densitiesB2A.push_back(densityA);
    expB2A.push_back(val / exp(majTmp * (b2a[b2a.size() - 2] - b2a[b2a.size() - 1])));
    extValsB2A.push_back(Spectrum(-1.0)); // a

    int n = a2b.size() + b2a.size() - 4; // max possible path length

    for (int l = 0; l <= n; ++l) {
        std::vector<BidirPath> paths;

        for (int i = 0; i <= l; ++i) {
            int j = l - i;

            if (a2b.size() - 2 < i) {
                i = l + 1;
                continue;
            }

            if (b2a.size() - 2 < j) continue;
            if (b2a[j] - a2b[i] <= 0.0) continue;

            Float pdfPath = 0.0;
            Spectrum prod = Spectrum(1.0);

            Float dist = b2a[j] - a2b[i];
            Float tau_bar = dist * maxD * sigma_t;
            Float tau = dist * (densitiesA2B[i][0] + densitiesB2A[j][0]) / 2.0 * sigma_t;
            Float ratio = 1.0;

            Float nee = exp(majTmp * (dist));
            Float pdf = val / nee * ratio;

            Float pdfLight = 0.0;

            for (int q = 1; q <= i; ++q) {
                prod *= extValsA2B[q];
                pdfPath += expA2B[q - 1];
            }

            for (int q = 1; q <= j; ++q) {
                prod *= extValsB2A[q];
                pdfLight += expB2A[q - 1];
            }

            Float weight = pdf / (pdf + pdfLight + pdfPath);

            Spectrum ist = prod * nee;

            Tr += ist * weight;

            // TODO: VERIFY THIS
            // check camera path
            // if (b2a[j] <= a2b[i + 1])
            // {
            //     weight = val / ((2.0 * (l+1)) * val);
            //     ist = prod * weight;
            //     Tr += ist;
            // }
            //
            // // check light path
            // if (a2b[i] >= b2a[j + 1])
            // {
            //     weight = val / ((2.0 * (l+1)) * val);
            //     ist = prod * weight;
            //     Tr += ist;
            // }
        }
    }

    return Tr;
}

}
