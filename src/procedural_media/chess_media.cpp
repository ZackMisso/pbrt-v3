#include "chess_media.h"
#include "interaction.h"
#include "ext/imedit/filter.h"
#include "ext/imedit/noise.h"
#include "ext/imedit/procedural.h"
#include "ext/imedit/im_util.h"

namespace pbrt
{

Chess_Media::Chess_Media(const Bounds3f& medBounds,
                         Float hue,
                         Float sat,
                         Float turb_period,
                         Float xtrans,
                         Float ytrans,
                         Float ztrans,
                         Float g_const,
                         Float x_const,
                         Float t_const,
                         Float phase,
                         Float power)
    : medBounds(medBounds),
      hue(hue),
      sat(sat),
      turb_period(turb_period),
      xtrans(xtrans),
      ytrans(ytrans),
      ztrans(ztrans),
      g_const(g_const),
      x_const(x_const),
      t_const(t_const),
      phase(phase),
      power(power)
{
    // does nothing
}

Chess_Media::~Chess_Media() { }

Spectrum Chess_Media::Evaluate(const SurfaceInteraction& si) const
{
    Float dist = 0.05;
    // add some artificial aliasing for appearances
    Spectrum ret = Spectrum(1.0) - (Evaluate(si.p) +
                                    Evaluate(si.p + Point3f(dist, 0.0, 0.0)) +
                                    Evaluate(si.p + Point3f(-dist, 0.0, 0.0)) +
                                    Evaluate(si.p + Point3f(0.0, dist, 0.0)) +
                                    Evaluate(si.p + Point3f(0.0, -dist, 0.0)) +
                                    Evaluate(si.p + Point3f(0.0, 0.0, dist)) +
                                    Evaluate(si.p + Point3f(0.0, 0.0, -dist))) / 7.0;

    if (ret[0] > 1.0) ret[0] = 1.0;
    if (ret[1] > 1.0) ret[1] = 1.0;
    if (ret[2] > 1.0) ret[2] = 1.0;

    if (ret[0] < 0.0) ret[0] = 0.0;
    if (ret[1] < 0.0) ret[1] = 0.0;
    if (ret[2] < 0.0) ret[2] = 0.0;

    return ret;
}

Spectrum Chess_Media::Evaluate(const Point3f& p) const
{
    Float t = imedit::turbulence(p.x / (medBounds.pMax.x - medBounds.pMin.x) * 4096.0 + xtrans,
                                 p.y / (medBounds.pMax.x - medBounds.pMin.x) * 4096.0 + ytrans,
                                 p.z / (medBounds.pMax.x - medBounds.pMin.x) * 4096.0 + ztrans,
                                 turb_period);

    Float x_val = (p.x - medBounds.pMin.x) / (medBounds.pMax.x - medBounds.pMin.x);

    t = pow(std::fabs(
                std::sin(
                    g_const * (x_const * x_val + t_const * t) - phase
                )
            ), power);

    imedit::Pixel final_color;
    final_color.r = hue;
    final_color.g = sat;
    if (sat == 1.0)
    {
        final_color.b = 0.1 * t + 0.75 * (1.0 - t);
    }
    else
    {
        final_color.b = 0.1 * t + 0.46 * (1.0 - t);
    }

    imedit::hsl_to_rgb(final_color);

    Float rgb[3];
    rgb[0] = 1.0 - final_color.r;
    rgb[1] = 1.0 - final_color.g;
    rgb[2] = 1.0 - final_color.b;

    return Spectrum::FromRGB(rgb);
}

Chess_Media* CreateChessTextureMedia(const TextureParams& tp)
{
    ParamSet params = tp.GetMaterialParams();

    Bounds3f medBounds = Bounds3f(params.FindOnePoint3f("minBounds", Point3f(0.0, 0.0, 0.0)),
                                  params.FindOnePoint3f("maxBounds", Point3f(1.0, 1.0, 1.0)));

    Float hue = params.FindOneFloat("hue", 140.0 / 360.0) - 0.28;
    if (hue < 0.0) hue = 1.0 - hue;
    Float sat = params.FindOneFloat("sat", 1.0);
    Float xtrans = params.FindOneFloat("xtrans", 0.0);
    Float ytrans = params.FindOneFloat("ytrans", 0.0);
    Float ztrans = params.FindOneFloat("ztrans", 0.0);
    Float turb_p = params.FindOneFloat("turb_period", 4096.0 / 5.0);
    Float g_const = params.FindOneFloat("g_const", 1.0);
    Float x_const = params.FindOneFloat("x_const", 4.5);
    Float t_const = params.FindOneFloat("t_const", 7.0);
    Float phase = params.FindOneFloat("phase", 1.0);
    Float power = params.FindOneFloat("power", 4.0);

    Chess_Media* media = new Chess_Media(medBounds,
                                         hue,
                                         sat,
                                         turb_p,
                                         xtrans,
                                         ytrans,
                                         ztrans,
                                         g_const,
                                         x_const,
                                         t_const,
                                         phase,
                                         power);

    return media;
}

}
