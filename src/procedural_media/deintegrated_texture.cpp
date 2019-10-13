#include "deintegrated_texture.h"
#include "interaction.h"

#if OPENVDB

#include <openvdb/tools/Interpolation.h>

namespace pbrt
{

Deintegrated_Texture_Media::Deintegrated_Texture_Media(const Bounds3f& medBounds,
                                                       std::string image_name,
                                                       bool along_z)
    : medBounds(medBounds), along_z(along_z)
{
    imedit::Image<double> image = imedit::Image<double>(image_name);

    r_grid = openvdb::FloatGrid::create(0.5);
    g_grid = openvdb::FloatGrid::create(0.5);
    b_grid = openvdb::FloatGrid::create(0.5);

    r_dist_min = 1.0;
    g_dist_min = 1.0;
    b_dist_min = 1.0;

    r_dist_total = 1.0;
    g_dist_total = 1.0;
    b_dist_total = 1.0;

    openvdb::FloatGrid::Accessor r_accessor = r_grid->getAccessor();
    openvdb::FloatGrid::Accessor g_accessor = g_grid->getAccessor();
    openvdb::FloatGrid::Accessor b_accessor = b_grid->getAccessor();

    width = image.width();
    height = image.height();
    depth = 1;

    max = image(0, 0, 0);
    min = image(0, 0, 0);

    for (int k = 0; k < depth; ++k)
    {
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                openvdb::Coord xyz(j, i, k);

                if (1.0 - image(j, i, 0) > max) max = 1.0 - image(j, i, 0);
                if (1.0 - image(j, i, 1) > max) max = 1.0 - image(j, i, 1);
                if (1.0 - image(j, i, 2) > max) max = 1.0 - image(j, i, 2);
                if (1.0 - image(j, i, 0) < min) min = 1.0 - image(j, i, 0);
                if (1.0 - image(j, i, 1) < min) min = 1.0 - image(j, i, 1);
                if (1.0 - image(j, i, 2) < min) min = 1.0 - image(j, i, 2);

                double t_k = std::abs(double(k)-double(depth)/2.0) / (double(depth)/2.0);

                double r_dist = (1.0 * t_k + r_dist_min * (1.0 - t_k)) / r_dist_total;
                double g_dist = (1.0 * t_k + g_dist_min * (1.0 - t_k)) / g_dist_total;
                double b_dist = (1.0 * t_k + b_dist_min * (1.0 - t_k)) / b_dist_total;

                // figure out why accessor does not work
                r_accessor.setValue(xyz, r_dist * (1.0 - image(j, i, 0)));
                g_accessor.setValue(xyz, g_dist * (1.0 - image(j, i, 1)));
                b_accessor.setValue(xyz, b_dist * (1.0 - image(j, i, 2)));
            }
        }
    }
}

Deintegrated_Texture_Media::~Deintegrated_Texture_Media()
{
    r_grid->clear();
    b_grid->clear();
    g_grid->clear();
}

Spectrum Deintegrated_Texture_Media::Evaluate(const SurfaceInteraction& si) const
{
    openvdb::tools::GridSampler<openvdb::FloatGrid, openvdb::tools::BoxSampler> r_sampler(*r_grid);
    openvdb::tools::GridSampler<openvdb::FloatGrid, openvdb::tools::BoxSampler> g_sampler(*g_grid);
    openvdb::tools::GridSampler<openvdb::FloatGrid, openvdb::tools::BoxSampler> b_sampler(*b_grid);

    Float x = 0.0;
    Float y = 0.0;
    Float z = 0.0;

    if (along_z)
    {
        x = (si.p.x - medBounds.pMin.x) / (medBounds.pMax.x - medBounds.pMin.x) * width;
        y = (si.p.y - medBounds.pMin.y) / (medBounds.pMax.y - medBounds.pMin.y) * height;
        z = (si.p.z - medBounds.pMin.z) / (medBounds.pMax.z - medBounds.pMin.z) * depth;
    }
    else
    {
        x = (si.p.x - medBounds.pMin.x) / (medBounds.pMax.x - medBounds.pMin.x) * width;
        y = (si.p.z - medBounds.pMin.z) / (medBounds.pMax.z - medBounds.pMin.z) * height;
        z = (si.p.y - medBounds.pMin.y) / (medBounds.pMax.y - medBounds.pMin.y) * depth;
    }

    Float rgb[3];

    rgb[0] = (Float)r_sampler.isSample(openvdb::Vec3R(x, y, z));
    rgb[1] = (Float)g_sampler.isSample(openvdb::Vec3R(x, y, z));
    rgb[2] = (Float)b_sampler.isSample(openvdb::Vec3R(x, y, z));

    if (rgb[0] > 1.0) rgb[0] = 1.0;
    if (rgb[1] > 1.0) rgb[1] = 1.0;
    if (rgb[2] > 1.0) rgb[2] = 1.0;

    return (Spectrum(1.0) - Spectrum::FromRGB(rgb));
}

Spectrum Deintegrated_Texture_Media::Evaluate(const Point3f& p) const
{
    openvdb::tools::GridSampler<openvdb::FloatGrid, openvdb::tools::BoxSampler> r_sampler(*r_grid);
    openvdb::tools::GridSampler<openvdb::FloatGrid, openvdb::tools::BoxSampler> g_sampler(*g_grid);
    openvdb::tools::GridSampler<openvdb::FloatGrid, openvdb::tools::BoxSampler> b_sampler(*b_grid);

    Float x = 0.0;
    Float y = 0.0;
    Float z = 0.0;

    if (along_z)
    {
        x = (p.x - medBounds.pMin.x) / (medBounds.pMax.x - medBounds.pMin.x) * width;
        y = (p.y - medBounds.pMin.y) / (medBounds.pMax.y - medBounds.pMin.y) * height;
        z = (p.z - medBounds.pMin.z) / (medBounds.pMax.z - medBounds.pMin.z) * depth;
    }
    else
    {
        x = (p.x - medBounds.pMin.x) / (medBounds.pMax.x - medBounds.pMin.x) * width;
        y = (p.z - medBounds.pMin.z) / (medBounds.pMax.z - medBounds.pMin.z) * height;
        z = (p.y - medBounds.pMin.y) / (medBounds.pMax.y - medBounds.pMin.y) * depth;
    }

    Float rgb[3];

    rgb[0] = (Float)r_sampler.isSample(openvdb::Vec3R(x, y, z));
    rgb[1] = (Float)g_sampler.isSample(openvdb::Vec3R(x, y, z));
    rgb[2] = (Float)b_sampler.isSample(openvdb::Vec3R(x, y, z));

    if (rgb[0] > 1.0) rgb[0] = 1.0;
    if (rgb[1] > 1.0) rgb[1] = 1.0;
    if (rgb[2] > 1.0) rgb[2] = 1.0;

    return Spectrum::FromRGB(rgb);
}

Deintegrated_Texture_Media* CreateDeintegratedTextureMedia(const TextureParams& tp)
{
    ParamSet params = tp.GetMaterialParams();

    Bounds3f medBounds = Bounds3f(params.FindOnePoint3f("minBounds", Point3f(0.0, 0.0, 0.0)),
                                  params.FindOnePoint3f("maxBounds", Point3f(1.0, 1.0, 1.0)));

    std::string texture = params.FindOneString("filename", "/Users/corneria/Documents/Projects/ImageEditLib/build/noise.hdr");

    bool along_z = params.FindOneBool("along_z", false);

    Deintegrated_Texture_Media* media = new Deintegrated_Texture_Media(medBounds, texture, along_z);

    return media;
}

}

#endif
