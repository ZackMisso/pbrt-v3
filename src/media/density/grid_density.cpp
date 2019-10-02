#include "grid_density.h"

namespace pbrt
{

GridDensityFunction::GridDensityFunction()
{
    width = 0;
    height = 0;
    depth = 0;
}

Spectrum GridDensityFunction::D(const Point3f& p) const
{
    nDensityCalls++;

    // Compute voxel coordinates and offsets for _p_
    Point3f pSamples(p.x * width - .5f, p.y * height - .5f, p.z * depth - .5f);
    Point3i pi = (Point3i)Floor(pSamples);
    Vector3f d = pSamples - (Point3f)pi;

    // Trilinearly interpolate density values to compute local density
    Float d00 = Lerp(d.x, D(pi)[0], D(pi + Vector3i(1, 0, 0))[0]);
    Float d10 = Lerp(d.x, D(pi + Vector3i(0, 1, 0))[0], D(pi + Vector3i(1, 1, 0))[0]);
    Float d01 = Lerp(d.x, D(pi + Vector3i(0, 0, 1))[0], D(pi + Vector3i(1, 0, 1))[0]);
    Float d11 = Lerp(d.x, D(pi + Vector3i(0, 1, 1))[0], D(pi + Vector3i(1, 1, 1))[0]);
    Float d0 = Lerp(d.y, d00, d10);
    Float d1 = Lerp(d.y, d01, d11);

    return Spectrum(Lerp(d.z, d0, d1));
}

Spectrum GridDensityFunction::D(const Point3i& p) const
{
    Bounds3i sampleBounds(Point3i(0, 0, 0), Point3i(width, height, depth));
    if (!InsideExclusive(p, sampleBounds)) return 0;

    return Spectrum(density[(p.z * height + p.y) * width + p.x]);
}

Spectrum GridDensityFunction::getMaxDensity() const
{
    Float max = -0.1;

    for (int i = 0; i < depth; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            for (int k = 0; k < width; ++k)
            {
                if (density[(i * height + j) * width + k] > max)
                {
                    max = density[(i * height + j) * width + k];
                }
            }
        }
    }

    return Spectrum(max);
}

Spectrum GridDensityFunction::getMinDensity() const
{
    Float min = 100000000.0;

    for (int i = 0; i < depth; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            for (int k = 0; k < width; ++k)
            {
                if (density[(i * height + j) * width + k] < min)
                {
                    min = density[(i * height + j) * width + k];
                }
            }
        }
    }

    return Spectrum(min);
}

Spectrum GridDensityFunction::getMaxDensityInCube(const Point3i& a,
                                                  const Point3i& b) const
{
    Float maxDense = 0.0;

    for (int i = a.z; i <= b.z; ++i)
    {
        for (int j = a.y; j <= b.y; ++j)
        {
            for (int k = a.x; k <= b.x; ++k)
            {
                Float dense = D(Point3i(k, j, i))[0];
                if (dense > maxDense)
                    maxDense = dense;
            }
        }
    }

   return Spectrum(maxDense);
}

Spectrum GridDensityFunction::getMaxDensityInRange(const Point3f& a,
                                                   const Point3f& b) const
{
    int min_index_x = floor(a.x * Float(width));
    int min_index_y = floor(a.y * Float(height));
    int min_index_z = floor(a.z * Float(depth));

    int max_index_x = ceil(b.x * Float(width));
    int max_index_y = ceil(b.y * Float(height));
    int max_index_z = ceil(b.z * Float(depth));

    if (min_index_x < 0) min_index_x = 0;
    if (min_index_y < 0) min_index_y = 0;
    if (min_index_z < 0) min_index_z = 0;

    if (max_index_x > width) max_index_x = width;
    if (max_index_y > height) max_index_y = height;
    if (max_index_z > depth) max_index_z = depth;

    Float max = 0.0;

    for (int k = min_index_z; k < max_index_z; ++k)
    {
        for (int i = min_index_y; i < max_index_y; ++i)
        {
            for (int j = min_index_x; j < max_index_x; ++j)
            {
                Float dense = D(Point3i(j, i, k))[0];

                if (max < dense)
                {
                    max = dense;
                }
            }
        }
    }

    return max;
}

Spectrum GridDensityFunction::getMinDensityInRange(const Point3f& a,
                                                   const Point3f& b) const
{
    int min_index_x = floor(a.x * Float(width));
    int min_index_y = floor(a.y * Float(height));
    int min_index_z = floor(a.z * Float(depth));

    int max_index_x = ceil(a.x * Float(width));
    int max_index_y = ceil(a.y * Float(height));
    int max_index_z = ceil(a.z * Float(depth));

    Float min = 1000000000.0;

    for (int k = min_index_z; k < max_index_z; ++k)
    {
        for (int i = min_index_y; i < max_index_y; ++i)
        {
            for (int j = min_index_x; j < max_index_x; ++j)
            {
                Float dense = D(Point3i(j, i, k))[0];

                if (min > dense)
                {
                    min = dense;
                }
            }
        }
    }

    return Spectrum(min);
}

}
