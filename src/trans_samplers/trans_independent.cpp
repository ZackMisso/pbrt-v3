#include "trans_sampler.h"
#include "camera.h"

namespace pbrt
{

Trans_Independent::Trans_Independent(int ns, unsigned int seed) : TSampler(ns, seed) { }

Float Trans_Independent::Get1D()
{
    return rng.nextDouble();
}

std::unique_ptr<Sampler> Trans_Independent::Clone(int seed)
{
    Trans_Independent* sampler = new Trans_Independent(*this);
    sampler->sampSeed = sampSeed;
    sampler->jitSeed = jitSeed;
    sampler->reseedJitter();
    sampler->reseedSampler();

    return std::unique_ptr<Sampler>(sampler);
}

void Trans_Independent::StartPixel(const Point2i &p,
                                   int max_x_res,
                                   int max_y_res,
                                   int multiplier)
{
    sampSeed = baseSeed + p[1] * max_x_res + p[0] + max_x_res * max_y_res * multiplier;

    rng.seed(142, hash(sampSeed, currentPixelSampleIndex));
}

CameraSample Trans_Independent::GetCameraSample(const Point2i &pRaster)
{
    CameraSample cs;
    cs.pFilm = (Point2f)(pRaster) + Point2f(0.5, 0.5);
    cs.time = Get1D();
    cs.pLens = Get2D();
    return cs;
}

}
