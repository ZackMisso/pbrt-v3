#if defined(_MSC_VER)
#define NOMINMAX
#pragma once
#endif

#ifndef PBRT_HETEROGENEOUSMEDIA_H
#define PBRT_HETEROGENEOUSMEDIA_H

// media/heterogeneous.h*
#include "pbrt.h"
#include "medium.h"
#include "transform.h"
#include "stats.h"
#include "trans_ests/trans_est.h"
#include "minorant/minorant.h"
#include "majorant/majorant.h"
#include "ff_samplers/ff_sampler.h"

namespace pbrt
{

class HeterogeneousMedium : public Medium
{
public:
    HeterogeneousMedium(const Spectrum& sigma_a,
                        const Spectrum& sigma_s,
                        Float g,
                        T_Estimator* t_est,
                        DensityFunction* density,
                        MinorantFunction* minorant,
                        MajorantFunction* majorant,
                        FF_Sampler* ff,
                        const Transform& WorldToMedium,
                        const Bounds3f b);

    ~HeterogeneousMedium();

    // temporary clean later
    void setMajScale(Float scale);

    Spectrum Tr (const Ray& ray,
                 Sampler& sampler) const;

    Spectrum LocalTr (const Ray& ray,
                      Sampler& sampler,
                      Float tMin,
                      Float tMax) const;

    Spectrum Sample(const Ray& rWorld,
                    Sampler& sampler,
                    MemoryArena& arena,
                    MediumInteraction* mi) const
    {
        return Sample(rWorld,
                      sampler,
                      sampler,
                      arena,
                      mi);
    }

    Spectrum Sample(const Ray& rWorld,
                    Sampler& ff_sampler,
                    Sampler& trans_sampler,
                    MemoryArena& arena,
                    MediumInteraction* mi) const;

    bool TransformToLocalSpace(const Ray& rWorld,
                               Ray& ray,
                               Float& tMin,
                               Float& tMax) const;

    Float G() const { return g; }
    Spectrum ScatCoeff(const Point3f& pt) const { return density->D(pt) * sigma_s; }

    static long nTrCalls;
    static long nDensityCalls;

private:
    DensityFunction* density;
    T_Estimator* t_est;
    MajorantFunction* majorant;
    MinorantFunction* minorant;
    FF_Sampler* ff_sampler;

    const Bounds3f mediumBounds;
    const Transform WorldToMedium;
    const Spectrum sigma_a, sigma_s, sigma_t;
    const Float g;
};

};

#endif // PBRT_HETEROGENEOUS_MEDIA_H
