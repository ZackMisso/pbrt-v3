#pragma once

#include "density_func.h"

namespace pbrt
{

class GridDensityFunction : public DensityFunction
{
public:
    GridDensityFunction();

    virtual Spectrum D(const Point3f& p) const;
    Spectrum D(const Point3i& p) const;

    virtual Spectrum getMaxDensity() const;
    virtual Spectrum getMinDensity() const;

    virtual Spectrum getMaxDensityInRange(const Point3f& a,
                                       const Point3f& b) const;

    virtual Spectrum getMinDensityInRange(const Point3f& a,
                                       const Point3f& b) const;

    virtual Spectrum getMaxDensityInCube(const Point3i& a,
                                      const Point3i& b) const;

    virtual int getWidth() const { return width; }
    virtual int getHeight() const { return height; }
    virtual int getDepth() const { return depth; }

    virtual bool requiresLocalSpace() const { return true; }

    Float* density;
    int width;
    int height;
    int depth;
};

}
