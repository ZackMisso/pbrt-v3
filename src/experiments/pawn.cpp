#include "pawn.h"

// Generate 1.00 Pawn Renders - 17756986
// Generate 0.95 Pawn Renders - 18279968
// Generate 0.90 Pawn Renders - 18859103
// Generate 0.85 Pawn Renders - 19505647
// Generate 0.80 Pawn Renders - 20234113
// Generate 0.75 Pawn Renders - 21057899
// Generate 0.70 Pawn Renders - 21998933
// Generate 0.65 Pawn Renders - 23084081
// Generate 0.60 Pawn Renders - 24354932
// Generate 0.55 Pawn Renders - 25854621
// Generate 0.50 Pawn Renders - 27651590
// Generate 0.45 Pawn Renders - 29851971
// Generate 0.40 Pawn Renders - 32595663
// Generate 0.35 Pawn Renders - 36125740
// Generate 0.30 Pawn Renders - 40835952
// Generate 0.25 Pawn Renders - 47427270
// Generate 0.20 Pawn Renders - 57323218
// Generate 0.15 Pawn Renders - 73801445
// Generate 0.10 Pawn Renders - 106761653
// Generate 0.05 Pawn Renders - 205660437

Pawn_Scene::Pawn_Scene(pbrt::Options options, ExperimentFlags flags)
{
    std::string mk_loc = "mkdir pawn_figure";
    std::system(mk_loc.c_str());

    if (flags.run_equal_extinctions)
    {
        // equal ext call renders
        for (int j = 0; j < flags.ext_calls.size(); ++j)
        {
            for (int i = 0; i < flags.estimators.size(); ++i)
            {
                std::string mk_loc = "mkdir pawn_figure/" + std::to_string(flags.majorants[j]);
                std::system(mk_loc.c_str());

                runEqualExtRenders(options, flags.estimators[i], flags.majorants[j], flags.ext_calls[j]);
            }
        }
    }

    if (flags.run_equal_samples)
    {
        mk_loc = "mkdir pawn_figure_strat";
        std::system(mk_loc.c_str());

        for (int j = 0; j < flags.spp.size(); ++j)
        {
            for (int i = 0; i < flags.estimators.size(); ++i)
            {
                std::string mk_loc = "mkdir pawn_figure_strat/" + std::to_string(flags.majorants[j]) + "_rand";
                std::system(mk_loc.c_str());

                runEqualSampleRenders(options, flags.estimators[i], flags.majorants[j], flags.ext_calls[j]);
            }
        }
    }

    if (flags.run_stratified_samples)
    {
        mk_loc = "mkdir globe_figure_strat";
        std::system(mk_loc.c_str());

        for (int j = 0; j < flags.spp.size(); ++j)
        {
            for (int i = 0; i < flags.estimators.size(); ++i)
            {
                std::string mk_loc = "mkdir pawn_figure_strat/" + std::to_string(flags.majorants[j]) + "_strat";
                std::system(mk_loc.c_str());

                runEqualSampleStratifiedRenders(options, flags.estimators[i], flags.majorants[j], flags.ext_calls[j]);
            }
        }
    }
}

void Pawn_Scene::runTest(pbrt::Options options, std::string transType, Float majScale)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining("/Users/corneria/Documents/Research/testscenes/chess/dragon_10.pbrt"));
    exp_path = "/Users/corneria/Documents/Research/testscenes/chess/";

    initializeIntegrator(200000000,
                         //240,
                         // 1000000000,
                         -1,
                         8,
                         "volpath_recursive",
                         "stream",
                         "independent",
                         false,
                         true);

    initializeSampler("random", 1000);

    initializePixelFilter("box");

    initializeFilm(//"pawn_figure/" + std::to_string(1.0 / majScale) + "/" + transType + "_strat",
                   "gt_pawn_test",
                   //"pawn_figure/" + transType,
                   720,
                   1280);

    pbrtScale(-1.0, 1.0, 1.0);

    pbrtLookAt(0.0, 10.0, 4.0,
               1.66, 0.0, 4.0,
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 30.0);
    // initializeCamera("perspective", 50.0);

    pbrtWorldBegin();

    pbrtAttributeBegin();
    pbrtRotate(60.0, 0.0, 1.0, 0.0);
    // pbrtRotate(40.0, 0.0, 0.0, 1.0);
    initializeInfiniteLightSource("textures/skylight-morn_full.exr",
                                  //"textures/noon_grass_2k.exr",
                                  // "white.png",
                                  std::vector<Float>{1.46, 1.46, 1.46});
    pbrtAttributeEnd();

    pbrtAttributeBegin();
    // initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
    //                 std::vector<Float>{0.0, 0.0, 0.0},
    //                 2.5);

    initializeMaterial_ReflectiveMatte(std::vector<Float>{0.0, 0.0, 0.0},
                                       std::vector<Float>{1.0, 1.0, 1.0});

    initializeTrimesh(std::vector<int>{0, 1, 2, 2, 3, 0},
                      std::vector<Float>{-1000.0, -1000.0, 0.0,
                                         1000.0, -1000.0, 0.0,
                                         1000.0, 1000.0, 0.0,
                                         -1000.0, 1000.0, 0.0});
    pbrtAttributeEnd();

    initializePawn(transType, majScale);
    // initializeRook();
    // initializeKnight();
    // initializeBishop();
    // initializeKing();
    // initializeQueen();

    pbrtWorldEnd();

    pbrtCleanup();
}

void Pawn_Scene::runEqualExtRenders(pbrt::Options options, std::string transType, Float majScale, long extCalls)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/chess/dragon_10.pbrt"));
    exp_path = TEST_SCENES_PATH "/chess/";

    initializeIntegrator(200000000,
                         //240,
                         extCalls,
                         // -1,
                         8,
                         "volpath_recursive",
                         "independent",
                         "independent",
                         false,
                         false);

    initializeSampler("random", 8000);

    initializePixelFilter("box");

    initializeFilm("pawn_figure/" + std::to_string(majScale) + "/" + transType,
                   //"pawn_figure/test",
                   720,
                   1280);

    pbrtScale(-1.0, 1.0, 1.0);

    pbrtLookAt(0.0, 10.0, 4.0,
               1.66, 0.0, 4.0,
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 30.0);

    pbrtWorldBegin();

    pbrtAttributeBegin();
    pbrtRotate(60.0, 0.0, 1.0, 0.0);
    initializeInfiniteLightSource("textures/skylight-morn_full.exr",
                                  std::vector<Float>{1.46, 1.46, 1.46});
    pbrtAttributeEnd();

    pbrtAttributeBegin();

    initializeMaterial_ReflectiveMatte(std::vector<Float>{0.0, 0.0, 0.0},
                                       std::vector<Float>{1.0, 1.0, 1.0});

    initializeTrimesh(std::vector<int>{0, 1, 2, 2, 3, 0},
                      std::vector<Float>{-1000.0, -1000.0, 0.0,
                                         1000.0, -1000.0, 0.0,
                                         1000.0, 1000.0, 0.0,
                                         -1000.0, 1000.0, 0.0});
    pbrtAttributeEnd();

    initializePawn(transType, majScale);

    pbrtWorldEnd();

    pbrtCleanup();
}

void Pawn_Scene::runEqualSampleRenders(pbrt::Options options, std::string transType, Float majScale, long samples)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/chess/dragon_10.pbrt"));
    exp_path = TEST_SCENES_PATH "/chess/";

    initializeIntegrator(200000000,
                         //240,
                         // 100000000,
                         -1,
                         8,
                         "volpath_recursive",
                         "independent",
                         "independent",
                         false,
                         false);

    // initializeSampler("random", 4);
    initializeSampler("random", samples);
    // initializeSampler("random", 64);

    initializePixelFilter("box");

    initializeFilm("pawn_figure_strat/" + std::to_string(majScale) + "_rand/" + transType+"_rand",
                   //"pawn_convergence_not_"+transType,
                   720,
                   1280);

    pbrtScale(-1.0, 1.0, 1.0);

    pbrtLookAt(0.0, 10.0, 4.0,
               1.66, 0.0, 4.0,
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 30.0);

    pbrtWorldBegin();

    pbrtAttributeBegin();
    pbrtRotate(60.0, 0.0, 1.0, 0.0);
    initializeInfiniteLightSource("textures/skylight-morn_full.exr",
                                  std::vector<Float>{1.46, 1.46, 1.46});
    pbrtAttributeEnd();

    pbrtAttributeBegin();

    initializeMaterial_ReflectiveMatte(std::vector<Float>{0.0, 0.0, 0.0},
                                       std::vector<Float>{1.0, 1.0, 1.0});

    initializeTrimesh(std::vector<int>{0, 1, 2, 2, 3, 0},
                      std::vector<Float>{-1000.0, -1000.0, 0.0,
                                         1000.0, -1000.0, 0.0,
                                         1000.0, 1000.0, 0.0,
                                         -1000.0, 1000.0, 0.0});
    pbrtAttributeEnd();

    initializePawn(transType, majScale);

    pbrtWorldEnd();

    pbrtCleanup();
}

void Pawn_Scene::runEqualSampleStratifiedRenders(pbrt::Options options, std::string transType, Float majScale, long samples)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/chess/dragon_10.pbrt"));
    exp_path = TEST_SCENES_PATH "/chess/";

    initializeIntegrator(200000000,
                         //240,
                         // 100000000,
                         -1,
                         8,
                         "volpath_recursive",
                         "stream",
                         "independent",
                         false,
                         false);

    initializeSampler("random", samples);

    initializePixelFilter("box");

    initializeFilm("pawn_figure_strat/" + std::to_string(majScale) + "_strat/" + transType+"_strat",
                   720,
                   1280);

    pbrtScale(-1.0, 1.0, 1.0);

    pbrtLookAt(0.0, 10.0, 4.0,
               1.66, 0.0, 4.0,
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 30.0);

    pbrtWorldBegin();

    pbrtAttributeBegin();
    pbrtRotate(60.0, 0.0, 1.0, 0.0);
    initializeInfiniteLightSource("textures/skylight-morn_full.exr",
                                  std::vector<Float>{1.46, 1.46, 1.46});
    pbrtAttributeEnd();

    pbrtAttributeBegin();

    initializeMaterial_ReflectiveMatte(std::vector<Float>{0.0, 0.0, 0.0},
                                       std::vector<Float>{1.0, 1.0, 1.0});

    initializeTrimesh(std::vector<int>{0, 1, 2, 2, 3, 0},
                      std::vector<Float>{-1000.0, -1000.0, 0.0,
                                         1000.0, -1000.0, 0.0,
                                         1000.0, 1000.0, 0.0,
                                         -1000.0, 1000.0, 0.0});
    pbrtAttributeEnd();

    initializePawn(transType, majScale);

    pbrtWorldEnd();

    pbrtCleanup();
}

void Pawn_Scene::initializePawn(std::string transType, Float majScale)
{
    // initializeVoronoiSpiralTexture("density",
    //                                std::vector<Float>{0.4, 0.8, 0.8,
    //                                                   0.2, 0.2, 0.2,
    //                                                   0.1, 0.5, 0.95},
    //                                std::vector<Float>{0.3, 0.3, 0.3},
    //                                std::vector<Float>{0.0, 6.28 / 3.0, 6.28 * 2.0 / 3.0},
    //                                std::vector<Float>{2.0, 2.0, 2.0},
    //                                std::vector<Float>{0.967742, 0.967742, 0.967742},
    //                                // std::vector<Float>{0.26, 0.26, 0.26},
    //                                std::vector<Float>{0.0, 0.0, 0.0},
    //                                std::vector<Float>{0.0, -10.0, 0.0},
    //                                std::vector<Float>{9.0, -20.0, 16.0},
    //                                0.25,
    //                                36);

    initializeVoronoiSpiralTexture("density",
                                   std::vector<Float>{1.0, 1.0, 1.0,
                                                      1.0, 1.0, 1.0,
                                                      1.0, 1.0, 1.0},
                                   std::vector<Float>{0.3, 0.3, 0.3},
                                   std::vector<Float>{0.0, 6.28 / 3.0, 6.28 * 2.0 / 3.0},
                                   std::vector<Float>{2.0, 2.0, 2.0},
                                   std::vector<Float>{0.967742, 0.967742, 0.967742},
                                   // std::vector<Float>{0.26, 0.26, 0.26},
                                   std::vector<Float>{0.0, 0.0, 0.0},
                                   std::vector<Float>{0.0, -10.0, 0.0},
                                   std::vector<Float>{9.0, -20.0, 16.0},
                                   0.25,
                                   36);

    pbrtTransformBegin();

    initializeProceduralMedium("vol",
                               "heterogeneous",
                               "density",
                               transType,
                               "const",
                               "const",
                               "absorptive",
                               std::vector<Float>{0.3, 0.3, 0.3},
                               std::vector<Float>{0.0, 0.0, 0.0},
                               std::vector<Float>{0.0, -10.0, 0.0},
                               std::vector<Float>{9.0, -20.0, 16.0},
                               std::vector<Float>{1.0, 1.0, 1.0},
                               majScale);
    pbrtTransformEnd();

    pbrtAttributeBegin();
    pbrtScale(0.2, 0.2, 0.2);
    pbrtTranslate(-17.2292 * 5.0, 0.0, -2.52734 * 5.0);
    // pbrtTranslate(-1.0, 0.0, -1.2);
    // pbrtRotate(90.0, 1.0, 0.0, 0.0);
    initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
                        std::vector<Float>{1.0, 1.0, 1.0},
                        1.5);
    pbrtMediumInterface("vol", "");
    initializePlyShape("pawn.ply");
    pbrtAttributeEnd();
}
