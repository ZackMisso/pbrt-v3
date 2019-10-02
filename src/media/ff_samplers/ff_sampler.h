#pragma once

// this file contains the definitions of all of the different
// free flight sampling techniques. Currently only delta tracking is supported,
// but more maybe implemented soon.

#include "pbrt.h"
#include "../majorant/majorant.h"
#include "../density/density_func.h"
#include "../trans_ests/trans_est.h"
#include "sampler.h"
#include "spectrum.h"
#include "medium.h"

namespace pbrt
{

class FF_Sampler
{
public:
    virtual ~FF_Sampler() { };

    virtual Spectrum Sample(const Ray& ray,
                            const Ray& rWorld,
                            Sampler& sampler,
                            MemoryArena& arena,
                            MediumInteraction* mi,
                            Float tMin,
                            Float tMax) const = 0;

    virtual bool RequiresTr() const = 0;
    // TODO: these were apart of my MIS and EquiAngular sampling implementations.
    // Maybe reincorporate them later
    // virtual bool RequiresLightFirst() const = 0;

    Medium* mediumRef;
    MajorantFunction* majorant;
    DensityFunction* density;
    Float sigma_s;
    Float sigma_t;
    Float g;
};

// importance samples according to transmittance (delta tracking)
class FF_Trans_Sampler : public FF_Sampler
{
public:
    virtual Spectrum Sample (const Ray& ray,
                             const Ray& rWorld,
                             Sampler& sampler,
                             MemoryArena& arena,
                             MediumInteraction* mi,
                             Float tMin,
                             Float tMax) const;

    virtual bool RequiresTr() const { return false; }
    // virtual bool RequiresLightFirst() const { return false; }
};

// sampler which does nothing
class FF_Absorptive_Sampler : public FF_Sampler
{
public:
    virtual Spectrum Sample (const Ray& ray,
                             const Ray& rWorld,
                             Sampler& sampler,
                             MemoryArena& arena,
                             MediumInteraction* mi,
                             Float tMin,
                             Float tMax) const;

    virtual bool RequiresTr() const { return true; }
    // virtual bool RequiresLightFirst() const { return false; }
};

}
