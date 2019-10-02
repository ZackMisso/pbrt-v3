#pragma once

#include "experiment_base.h"

class Vase_Scene : public ExperimentBase
{
public:
    Vase_Scene(pbrt::Options options);

    void runTest(pbrt::Options options, std::string transType, double angle, int index, bool isGT);

    void runEqualExtRenders_Up(pbrt::Options options, std::string transType, Float majorant, long samples);
    void runEqualSampleRenders_Up(pbrt::Options options, std::string transType, Float majorant, long samples);
    void runEqualSampleStratifiedRenders_Up(pbrt::Options options, std::string transType, Float majorant, long samples);

    void runEqualExtRenders_Down(pbrt::Options options, std::string transType, Float majorant, long samples);
    void runEqualSampleRenders_Down(pbrt::Options options, std::string transType, Float majorant, long samples);
    void runEqualSampleStratifiedRenders_Down(pbrt::Options options, std::string transType, Float majorant, long samples);

    void initializeLightSources(bool up);
    void initializeVase_Up(std::string transType, Float majorant);
    void initializeVase_Down(std::string transType, Float majorant);
};
