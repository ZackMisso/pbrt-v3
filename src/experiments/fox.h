#pragma once

#include "experiment_base.h"

class Fox_Scene : public ExperimentBase
{
public:
    Fox_Scene(pbrt::Options options, ExperimentFlags flags);

    void runTest(pbrt::Options options, std::string transType, bool isGT, double angle, double psi, int iter);
    void runTest(std::string transType, bool isGT);

    void runEqualExtRenders(pbrt::Options options,
                            std::string transType,
                            bool isGT,
                            double angle,
                            double psi,
                            int iter,
                            Float majorant,
                            int samples);

    void runEqualSampleRenders(pbrt::Options options,
                               std::string transType,
                               bool isGT,
                               double angle,
                               double psi,
                               int iter,
                               Float majorant,
                               int samples);

    void runEqualSampleStratifiedRenders(pbrt::Options options,
                                         std::string transType,
                                         bool isGT,
                                         double angle,
                                         double psi,
                                         int iter,
                                         Float majorant,
                                         int samples);

    void initializeWalls();
    void initializeLightSources();
    void initializeProceduralDensity();
    void initializeTest();
};
