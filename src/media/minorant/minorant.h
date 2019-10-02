#pragma once

// this file contains the definitions of all of the different
// minorant functions. Macrogrid minorants and other acceleration data
// structures are topics I will explore in the future

#include "../density/density_func.h"

namespace pbrt
{

class MinorantFunction
{
public:
    virtual ~MinorantFunction() { }

    MinorantFunction(DensityFunction* density);

    virtual Float Min(const Point3f& p) const = 0;

    void setScale(Float param) { scale = param; }
protected:
    Float scale;
};

class ConstBoundedMinorant : public MinorantFunction
{
public:
    ConstBoundedMinorant(DensityFunction* density);

    virtual Float Min(const Point3f& p) const;

    Float minDensity;
};

}
