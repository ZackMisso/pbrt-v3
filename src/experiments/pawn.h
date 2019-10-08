#pragma once

#include "experiment_base.h"

class Pawn_Scene : public ExperimentBase
{
public:
    Pawn_Scene(pbrt::Options options, ExperimentFlags flags);

    void runTest(pbrt::Options options, std::string transType, Float majScale);

    void runEqualExtRenders(pbrt::Options, std::string transType, Float majScale, long extCalls);
    void runEqualSampleRenders(pbrt::Options, std::string transType, Float majScale);
    void runEqualSampleStratifiedRenders(pbrt::Options, std::string transType, Float majScale);

    void initializePawn(std::string transType, Float majScale);
};
