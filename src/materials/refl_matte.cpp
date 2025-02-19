#include "materials/refl_matte.h"
#include "paramset.h"
#include "reflection.h"
#include "interaction.h"
#include "texture.h"

namespace pbrt
{

void ReflectiveMatteMaterial::ComputeScatteringFunctions(SurfaceInteraction* si,
                                                         MemoryArena& arena,
                                                         TransportMode mode,
                                                         bool allowMultipleLobes) const
{
    Spectrum D = Kd->Evaluate(*si).Clamp();
    Spectrum R = Kr->Evaluate(*si).Clamp();

    si->bsdf = ARENA_ALLOC(arena, BSDF)(*si);

    if (D.IsBlack() && R.IsBlack())
    {
        return;
    }

    si->bsdf->Add(ARENA_ALLOC(arena, DiffuseReflective)(D, R, mode));
}

ReflectiveMatteMaterial* CreateReflectiveMatteMaterial(const TextureParams& mp)
{
    std::shared_ptr<Texture<Spectrum>> Kd =
        mp.GetSpectrumTexture("Kd", Spectrum(1.0f));
    std::shared_ptr<Texture<Spectrum>> Kr =
        mp.GetSpectrumTexture("Kr", Spectrum(1.0f));
    return new ReflectiveMatteMaterial(Kd, Kr);
}

}
