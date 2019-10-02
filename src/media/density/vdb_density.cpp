#include "vdb_density.h"

#if OPENVDB

#include <openvdb/tools/Interpolation.h>

namespace pbrt
{

VDB_DensityFunction::VDB_DensityFunction(std::string filename)
{
    clampDensities = false;
    retargetDensities = false;
    retainAspectRatio = false;
    worldSpace = true;

    openvdb::io::File file(filename);
    file.open();

    openvdb::GridBase::Ptr baseGrid;

    for (openvdb::io::File::NameIterator nameIter = file.beginName();
         nameIter != file.endName(); ++nameIter)
    {
        if (nameIter.gridName() == "density")
        {
            baseGrid = file.readGrid(nameIter.gridName());
        }
        else
        {
            std::cout << "Ignoring Grid: " << nameIter.gridName() << std::endl;
        }
    }

    grid = openvdb::gridPtrCast<openvdb::FloatGrid>(baseGrid);

    file.close();

    // std::cout << "PRE PROCESSING VDB GRID" << std::endl;
    // preProcess();
}

VDB_DensityFunction::~VDB_DensityFunction()
{
    std::cout << "Deconstructing VDB Density" << std::endl;
    grid->clear();
}

void VDB_DensityFunction::preProcess()
{
    openvdb::CoordBBox bbox = grid->evalActiveVoxelBoundingBox();

    min = bbox.min();
    max = bbox.max();

    openvdb::tools::GridSampler<openvdb::FloatGrid, openvdb::tools::PointSampler> sampler(*grid);

    maxDensity = 0;

    // TODO:: also implement macrogrid majorants into this mess
    for (int k = min.z(); k <= max.z(); ++k)
    {
        for (int i = min.y(); i <= max.y(); ++i)
        {
            for (int j = min.x(); j <= max.x(); ++j)
            {
                Float value = sampler.isSample(openvdb::Vec3R(Float(j), Float(i), Float(k)));
                if (value > maxDensity)
                {
                    maxDensity = value;
                }
            }
        }
    }

    xScaleFactor = max.x() - min.x();
    yScaleFactor = max.y() - min.y();
    zScaleFactor = max.z() - min.z();

    xTransFactor = xScaleFactor;
    yTransFactor = yScaleFactor;
    zTransFactor = zScaleFactor;

    if (retainAspectRatio)
    {
        if (xScaleFactor >= yScaleFactor && xScaleFactor >= zScaleFactor)
        {
            yScaleFactor = xScaleFactor;
            zScaleFactor = xScaleFactor;

            yTransFactor = (yScaleFactor - yTransFactor) / (2.0);
            zTransFactor = (zScaleFactor - zTransFactor) / (2.0);
            xTransFactor = 0.0;
        }
        else if (yScaleFactor >= zScaleFactor && yScaleFactor >= zScaleFactor)
        {
            xScaleFactor = yScaleFactor;
            zScaleFactor = yScaleFactor;

            xTransFactor = (xScaleFactor - xTransFactor) / (2.0);
            zTransFactor = (zScaleFactor - zTransFactor) / (2.0);
            yTransFactor = 0.0;
        }
        else
        {
            xScaleFactor = zScaleFactor;
            yScaleFactor = zScaleFactor;

            xTransFactor = (xScaleFactor - xTransFactor) / (2.0);
            yTransFactor = (yScaleFactor - yTransFactor) / (2.0);
            zTransFactor = 0.0;
        }
    }
    else
    {
        xTransFactor = 0.0;
        yTransFactor = 0.0;
        zTransFactor = 0.0;
    }

    xScaleFactor /= (box_max_x - box_min_x);
    yScaleFactor /= (box_max_z - box_min_z);
    zScaleFactor /= (box_max_y - box_min_y);
}

openvdb::Vec3R VDB_DensityFunction::getMinLocalSpaceCoord() const
{
    return openvdb::Vec3R((box_min_x - box_min_x) * xScaleFactor - xTransFactor + min.x(),
                          (box_min_z - box_min_z) * yScaleFactor - yTransFactor + min.y(),
                          (box_min_y - box_min_y) * zScaleFactor - zTransFactor + min.z());
}

openvdb::Vec3R VDB_DensityFunction::getMaxLocalSpaceCoord() const
{
    return openvdb::Vec3R((box_max_x - box_min_x) * xScaleFactor - xTransFactor + min.x(),
                          (box_max_z - box_min_z) * yScaleFactor - yTransFactor + min.y(),
                          (box_max_y - box_min_y) * zScaleFactor - zTransFactor + min.z());
}

openvdb::Vec3R VDB_DensityFunction::localToIndexSpace(const Point3f& p) const
{
    return openvdb::Vec3R((p[0] - box_min_x) * xScaleFactor - xTransFactor + min.x(),
                          (p[2] - box_min_z) * yScaleFactor - yTransFactor + min.y(),
                          (p[1] - box_min_y) * zScaleFactor - zTransFactor + min.z());
}

Spectrum VDB_DensityFunction::D(const Point3f& p) const
{
    nDensityCalls++;

    openvdb::tools::GridSampler<openvdb::FloatGrid, openvdb::tools::BoxSampler> sampler(*grid);
    // openvdb::tools::GridSampler<openvdb::FloatGrid, openvdb::tools::PointSampler> sampler(*grid);

    // std::cout << openvdb::tools::BoxSampler::radius() << std::endl;

    if (worldSpace)
    {
        // Note: houdini stores the up axis as y while most pbrt scens have z as the up vector
        //       so the indices are swivled.

        // index space sample
        // Float indexValue = (Float)sampler.isSample(openvdb::Vec3R(p[0], p[1], p[2]));

        // world space sample
        Float indexValue = (Float)sampler.wsSample(openvdb::Vec3R(p[0] / 10.0, p[2] / 10.0, p[1] / 10.0));

        if (indexValue > 1.0)
        {
            // std::cout << "Index Value: " << indexValue << std::endl;
            indexValue = 1.0;
        }

        return Spectrum(indexValue);
    }
    else
    {
        Float sampledValue;

        sampledValue = (Float)sampler.isSample(openvdb::Vec3R((p[0] - box_min_x) * xScaleFactor - xTransFactor + min.x(),
                                                              (p[2] - box_min_z) * yScaleFactor - yTransFactor + min.y(),
                                                              (p[1] - box_min_y) * zScaleFactor - zTransFactor + min.z()));

        if (retargetDensities)
        {
            sampledValue /= maxDensity;
        }

        if (clampDensities && sampledValue > 1.0)
        {
            sampledValue = 1.0;
        }

        return Spectrum(sampledValue);
    }
}

Spectrum VDB_DensityFunction::D(const Point3i& p) const
{
    openvdb::tools::GridSampler<openvdb::FloatGrid, openvdb::tools::PointSampler> sampler(*grid);

    Float indexValue = (Float)sampler.isSample(openvdb::Vec3R(p[0], p[1], p[2]));

    return Spectrum(indexValue);
}

Spectrum VDB_DensityFunction::getMaxDensity() const
{
    if (clampDensities || retargetDensities)
    {
        return Spectrum(1.0);
    }

    return Spectrum(maxDensity);
}

Spectrum VDB_DensityFunction::getMinDensity() const
{
    return Spectrum(0.0);
}

Spectrum VDB_DensityFunction::getMaxDensityInRange(const Point3f& a,
                                                   const Point3f& b) const
{
    // TODO
    return Spectrum(1.0);
}

Spectrum VDB_DensityFunction::getMinDensityInRange(const Point3f& a,
                                                   const Point3f& b) const
{
    // TODO
    return Spectrum(1.0);
}

// TODO: Create a spectral form of this method
// NOTE: the points passed in are in vdb space
Spectrum VDB_DensityFunction::getMaxDensityInCube(const Point3i& a,
                                                  const Point3i& b) const
{
    Float max_density = getMinDensity()[0];

    openvdb::tools::GridSampler<openvdb::FloatGrid, openvdb::tools::PointSampler> sampler(*grid);

    for (int k = a[2]; k <= b[2]; k++)
    {
        for (int i = a[1]; i <= b[1]; i++)
        {
            for (int j = a[0]; j <= b[0]; j++)
            {
                Float sampledValue = (Float)sampler.isSample(openvdb::Vec3R(j, i, k));

                if (sampledValue > max_density)
                {
                    max_density = sampledValue;
                }
            }
        }
    }

    if (retargetDensities)
    {
        max_density /= maxDensity;
    }

    if (clampDensities && max_density > 1.0)
    {
        max_density = 1.0;
    }

    return Spectrum(max_density);
}

}

#endif
