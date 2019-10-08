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
    // std::vector<Float> majToTest = std::vector<Float>{
    //     1.0, 1.1, 1.2, 1.3, 10.0,
    //     2.0, 3.0, 5.0, 1.4, 1.5,
    // };

    std::vector<Float> majToTest = std::vector<Float>();
    // majToTest.push_back(0.1);
    // // majToTest.push_back(0.2);
    // majToTest.push_back(0.3);
    // // majToTest.push_back(0.4);
    //
    // // majToTest.push_back(0.5);
    // majToTest.push_back(0.6);
    // // majToTest.push_back(0.7);
    // // majToTest.push_back(0.8);
    // // majToTest.push_back(0.9);
    // //
    // majToTest.push_back(1.0);
    // majToTest.push_back(1.5);
    // majToTest.push_back(2.0);
    // // majToTest.push_back(2.5);
    // // majToTest.push_back(3.5);
    // //
    // majToTest.push_back(5.0);
    // // majToTest.push_back(7.5);
    // majToTest.push_back(10.0);
    // // majToTest.push_back(15.0);
    // // majToTest.push_back(20.0);

    // majToTest.push_back(0.1);
    // majToTest.push_back(0.3);
    // majToTest.push_back(0.6);
    majToTest.push_back(1.0);
    // majToTest.push_back(1.5);
    // majToTest.push_back(2.5);
    // majToTest.push_back(5.0);


    std::vector<int> extCalls = std::vector<int>();
    // extCalls.push_back(1999450L * 8L);
    // // extCalls.push_back(2399450L * 8L);
    // extCalls.push_back(2899450L * 8L);
    // // extCalls.push_back(3399450L * 8L);
    //
    // // extCalls.push_back(3899450L * 8L);
    // extCalls.push_back(4852991L * 8L);
    // // extCalls.push_back(5948720L * 8L);
    // // extCalls.push_back(7080102L * 8L);
    // // extCalls.push_back(8228887L * 8L);
    //
    // extCalls.push_back(9397973L * 6L);
    // extCalls.push_back(15423376L * 6L);
    // extCalls.push_back(21637564L * 6L);
    // // extCalls.push_back(27956510L * 6L);
    // // extCalls.push_back(40789545L * 6L);
    //
    // extCalls.push_back(60295235L * 6L);
    // // extCalls.push_back(93140421L * 6L);
    // extCalls.push_back(126199406L * 6L);
    // // extCalls.push_back(192630815L * 6L);
    // // extCalls.push_back(259284596L * 6L);

    // extCalls.push_back(1999450L * 8L);
    // extCalls.push_back(2899450L * 8L);
    // extCalls.push_back(4852991L * 8L);
    // extCalls.push_back(9397973L * 6L);
    extCalls.push_back(15423376L * 6L);
    // extCalls.push_back(27956510L * 6L);
    // extCalls.push_back(60295235L * 6L);

    std::vector<std::string> estimators = std::vector<std::string>();
    estimators.push_back("track_length");
    estimators.push_back("ratio");
    estimators.push_back("next_flight_ratio");
    estimators.push_back("unidirectional");
    estimators.push_back("pseries_cumulative");
    estimators.push_back("pseries_cdf");
    // estimators.push_back("pseries_rr");
    estimators.push_back("pseries_ratio");
    estimators.push_back("pseries_next_flight_ratio");
    // estimators.push_back("pseries_interp");
    estimators.push_back("bidirectional");

    // for (double val = 1.0; val > 0.03; val -= 0.05)
    // {
    //     majToTest.push_back(1.0 / val);
    // }

    // for (int i = 0; i < majToTest.size(); ++i)
    // {
    //     // std::string rm_loc = "rm -rf /Users/corneria/Documents/Research/pbrttest/build_final/pawn_figure/" + std::to_string(majToTest[i]);
    //     std::string mk_loc = "mkdir /Users/corneria/Documents/Research/pbrttest/build_final/pawn_figure/" + std::to_string(majToTest[i]);
    //
    //     // std::system(rm_loc.c_str());
    //     std::system(mk_loc.c_str());
    //
    //     for (int j = 0; j < estimators.size(); ++j)
    //     {
    //         runEqualExtRenders(options, estimators[j], majToTest[i], extCalls[i]);
    //     }
    // }

    // for (int i = 0; i < majToTest.size(); ++i)
    // {
    //     // std::string rm_loc_rand = "rm -rf /Users/corneria/Documents/Research/pbrttest/build_final/pawn_figure_rand/" + std::to_string(majToTest[i]);
    //     std::string mk_loc_rand = "mkdir /Users/corneria/Documents/Research/pbrttest/build_final/pawn_figure_strat/" + std::to_string(majToTest[i]) + "_rand";
    //
    //     // std::system(rm_loc_rand.c_str());
    //     std::system(mk_loc_rand.c_str());
    //
    //     for (int j = 0; j < estimators.size(); ++j)
    //     {
    //         runEqualSampleRenders(options, estimators[j], majToTest[i]);
    //     }
    // }
    //
    // for (int i = 0; i < majToTest.size(); ++i)
    // {
    //     // std::string rm_loc_strat = "rm -rf /Users/corneria/Documents/Research/pbrttest/build_final/pawn_figure_strat/" + std::to_string(majToTest[i]);
    //     std::string mk_loc_strat = "mkdir /Users/corneria/Documents/Research/pbrttest/build_final/pawn_figure_strat/" + std::to_string(majToTest[i]) + "_strat";
    //
    //     // std::system(rm_loc_strat.c_str());
    //     std::system(mk_loc_strat.c_str());
    //
    //     for (int j = 0; j < estimators.size(); ++j)
    //     {
    //         runEqualSampleStratifiedRenders(options, estimators[j], majToTest[i]);
    //     }
    // }

    // for (int i = 0; i < majToTest.size(); ++i)
    // {
    //     std::cout << "Tested for: " << 1.0 / majToTest[i] << std::endl;
    // }

    // runEqualExtRenders("bidirectional_mis", 20.0);
    // runTest("track_length", 2.0);
    // runTest(options, "ratio", 2.0);
    // runTest("nf_ratio", 2.0);
    // runTest("pseries_ratio", 2.0);
    runTest(options, "next_flight_ratio", 1.0);
    // runTest("pseries_cumulative", 2.0);
    // runTest("pseries_cdf", 2.0);
    // runTest("unidirectional_mis", 2.0);
    // runTest("bidirectional_mis", 2.0);
    // runTest("pseries_nf_ratio", 2.0);
    // runTest("pseries_interp", 2.0);
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

    SetSearchDirectory(DirectoryContaining("/Users/corneria/Documents/Research/testscenes/chess/dragon_10.pbrt"));
    exp_path = "/Users/corneria/Documents/Research/testscenes/chess/";

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

void Pawn_Scene::runEqualSampleRenders(pbrt::Options options, std::string transType, Float majScale)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining("/Users/corneria/Documents/Research/testscenes/chess/dragon_10.pbrt"));
    exp_path = "/Users/corneria/Documents/Research/testscenes/chess/";

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
    initializeSampler("random", 8);
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

void Pawn_Scene::runEqualSampleStratifiedRenders(pbrt::Options options, std::string transType, Float majScale)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining("/Users/corneria/Documents/Research/testscenes/chess/dragon_10.pbrt"));
    exp_path = "/Users/corneria/Documents/Research/testscenes/chess/";

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

    initializeSampler("random", 8);

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
