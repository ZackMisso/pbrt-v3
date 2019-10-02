#include "majorant.h"

namespace pbrt
{

ConstBoundedMajorant::ConstBoundedMajorant(const DensityFunction* density) : MajorantFunction(density)
{
    maxDensity = ThreeWiseMax(density->getMaxDensity()[0],
                              density->getMaxDensity()[1],
                              density->getMaxDensity()[2]);

    maxDensity = 1.0;
}

Float ConstBoundedMajorant::Maj(const Point3f& pa, const Point3f& pb) const
{
    return maxDensity * scale;
}

}
