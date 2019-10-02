#pragma once

// this file contains the definitions of all of the different
// majorant functions. Macrogrid majorants and other acceleration data
// structures are topics I will explore in the future

#include "../density/density_func.h"

namespace pbrt
{

class MajorantFunction
{
public:
    virtual ~MajorantFunction() { }

    MajorantFunction(const DensityFunction* density) { }

    virtual Float Maj(const Point3f& pa, const Point3f& pb) const = 0;

    void setScale(Float param) { scale = param; }
protected:
    Float scale;
};

class ConstBoundedMajorant : public MajorantFunction
{
public:
    ConstBoundedMajorant(const DensityFunction* density);

    virtual Float Maj(const Point3f& pa, const Point3f& pb) const;

    Float maxDensity;
};

}
