#pragma once

// this file contains the definitions of all the different
// transmittance estimators

#include "../minorant/minorant.h"
#include "../majorant/majorant.h"
#include "../density/density_func.h"
#include "../trans_samplers/trans_sampler.h"

namespace pbrt
{

class T_Estimator
{
public:
    virtual ~T_Estimator() { }

    virtual Spectrum Tr(const Ray& ray,
                        Sampler& sampler,
                        Float tMin,
                        Float tMax) const
    {
        Float maxD = majorant->Maj(ray(tMin), ray(tMax));

        return Tr(ray,
                  sampler,
                  tMin,
                  tMax,
                  maxD);
    }

    virtual Spectrum Tr(const Ray& ray,
                        Sampler& sampler,
                        Float tMin,
                        Float tMax,
                        Float maxD) const = 0;

    virtual void preProcess() { }

    MinorantFunction* minorant;
    MajorantFunction* majorant;
    DensityFunction* density;
    Float sigma_t;
};

class Bidirectional : public T_Estimator
{
public:
    virtual Spectrum Tr(const Ray& ray,
                        Sampler& sampler,
                        Float tMin,
                        Float tMax,
                        Float maxD) const;
};

class NextFlight_Ratio : public T_Estimator
{
public:
    virtual Spectrum Tr(const Ray& ray,
                        Sampler& sampler,
                        Float tMin,
                        Float tMax,
                        Float maxD) const;
};

class Pseries_CMF : public T_Estimator
{
public:
    virtual Spectrum Tr(const Ray& ray,
                        Sampler& sampler,
                        Float tMin,
                        Float tMax,
                        Float maxD) const;
};

class Pseries_Cumulative : public T_Estimator
{
public:
    virtual Spectrum Tr(const Ray& ray,
                        Sampler& sampler,
                        Float tMin,
                        Float tMax,
                        Float maxD) const;
};

class Pseries_NextFlight_Ratio : public T_Estimator
{
public:
    virtual Spectrum Tr(const Ray& ray,
                        Sampler& sampler,
                        Float tMin,
                        Float tMax,
                        Float maxD) const;
};

class Pseries_Ratio : public T_Estimator
{
public:
    virtual Spectrum Tr(const Ray& ray,
                        Sampler& sampler,
                        Float tMin,
                        Float tMax,
                        Float maxD) const;
};

class Ratio : public T_Estimator
{
public:
    virtual Spectrum Tr(const Ray& ray,
                        Sampler& sampler,
                        Float tMin,
                        Float tMax,
                        Float maxD) const;
};

class Track_Length : public T_Estimator
{
public:
    virtual Spectrum Tr(const Ray& ray,
                        Sampler& sampler,
                        Float tMin,
                        Float tMax,
                        Float maxD) const;
};

class Unidirectional : public T_Estimator
{
public:
    virtual Spectrum Tr(const Ray& ray,
                        Sampler& sampler,
                        Float tMin,
                        Float tMax,
                        Float maxD) const;
};



} // namespace pbrt
