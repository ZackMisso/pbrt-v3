#if defined(_MSC_VER)
#define NOMINMAX
#pragma once
#endif

#ifndef PBRT_DENSITYFUNCTION_H
#define PBRT_DENSITYFUNCTION_H

// media/densityfunc.h*
#include "pbrt.h"
#include "transform.h"
#include "spectrum.h"

namespace pbrt
{

class DensityFunction
{
public:
    virtual ~DensityFunction() { };

    virtual Spectrum D(const Point3f& p) const = 0;
    virtual Spectrum getMaxDensity() const = 0;
    virtual Spectrum getMinDensity() const = 0;

    virtual void preProcess(const Transform& medToWorld,
                            const Bounds3f medBounds) { }

    virtual Spectrum getMaxDensityInRange(const Point3f& a,
                                          const Point3f& b) const = 0;

    virtual Spectrum getMinDensityInRange(const Point3f& a,
                                          const Point3f& b) const = 0;

    virtual Spectrum getMaxDensityInCube(const Point3i& a,
                                         const Point3i& b) const { return Spectrum(0.0); }

    virtual bool requiresLocalSpace() const = 0;

    void clearDensityCalls() { nDensityCalls = 0; }
    long getDensityCalls() { return nDensityCalls; }

    static long nDensityCalls;
};

}

#endif  // PBRT_DENSITYFUNCTION_H
