#pragma once

#include "experiment_base.h"
#include "pbrt.h"

class Teaser : public ExperimentBase
{
public:
    Teaser(pbrt::Options options, ExperimentFlags flags);

    void runTest(pbrt::Options options,
                 std::string transType,
                 bool is_gt);

    void initializeWorld(std::string transType, Float majScale);

    void initializePawn_One(std::string transType, Float majScale);
    void initializePawn_Two(std::string transType, Float majScale);
    void initializePawn_Four(std::string transType, Float majScale);
    void initializePawn_Five(std::string transType, Float majScale);

    void initializeKnight_Two(std::string transType, Float majScale);

    void initializeBishop_One(std::string transType, Float majScale);
    void initializeBishop_Two(std::string transType, Float majScale);

    void initializeKing(std::string transType, Float majScale);
    void initializeQueen(std::string transType, Float majScale);
};
