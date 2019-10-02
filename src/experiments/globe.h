#pragma once

#include "experiment_base.h"
#include "pbrt.h"

#if OPENVDB

class Globe_Scene : public ExperimentBase
{
public:
    Globe_Scene(pbrt::Options options);

    void runTest(pbrt::Options options,
                 std::string transType,
                 bool isGT,
                 std::string name,
                 int iter);

    void runEqualExtRenders(pbrt::Options options,
                            std::string transType,
                            Float majorant,
                            long samples);

    void initializeSceneMediumBox(std::string transType,
                                  std::string name,
                                  std::string maj,
                                  Float majorant);

    void initializeLightSources();
};

#endif
