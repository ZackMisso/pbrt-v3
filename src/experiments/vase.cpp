#include "vase.h"

Vase_Scene::Vase_Scene(pbrt::Options options)
{
    // int max_index = 60;
    // int start_index = 0;
    // int end_index = 1;
    //
    // for (int i = start_index; i < end_index; i++)
    // {
    //     double angle = 6.28 * double(i) / max_index;
    //     runTest("ratio", angle, i, true);
    // }

    // runTest(options, "ratio", 0.0, 0, true);

    std::vector<Float> majorants = std::vector<Float>();
    // // majorants.push_back(0.0);
    // majorants.push_back(0.1);
    // // majorants.push_back(0.2);
    // majorants.push_back(0.3);
    // // majorants.push_back(0.4);
    // // majorants.push_back(0.5);
    // majorants.push_back(0.6);
    // // majorants.push_back(0.7);
    // // majorants.push_back(0.8);
    // // majorants.push_back(0.9);
    // majorants.push_back(1.0);
    // majorants.push_back(1.5);
    // majorants.push_back(2.0);
    // // majorants.push_back(2.5);
    // // majorants.push_back(3.5);
    // majorants.push_back(5.0);
    // // majorants.push_back(7.5);
    // majorants.push_back(10.0);
    // // majorants.push_back(15.0);
    // // majorants.push_back(20.0);

    majorants.push_back(0.1);
    majorants.push_back(0.3);
    majorants.push_back(0.6);
    majorants.push_back(1.0);
    majorants.push_back(1.5);
    majorants.push_back(2.5);
    majorants.push_back(5.0);

    std::vector<long> up_extCalls = std::vector<long>();
    // up_extCalls.push_back(20169511L * 4L);
    // // up_extCalls.push_back(20169511L * 4L);
    // up_extCalls.push_back(20169511L * 4L);
    // // up_extCalls.push_back(20169511L * 4L);
    // // up_extCalls.push_back(20169511L * 4L);
    // up_extCalls.push_back(25186442L * 4L);
    // // up_extCalls.push_back(30301802L * 4L);
    // // up_extCalls.push_back(35480565L * 4L);
    // // up_extCalls.push_back(40695169L * 4L);
    // up_extCalls.push_back(45958204L * 4L);
    // up_extCalls.push_back(72646939L * 4L);
    // up_extCalls.push_back(99717326L * 4L);
    // // up_extCalls.push_back(126986658L * 4L);
    // // up_extCalls.push_back(181883736L * 4L);
    // up_extCalls.push_back(264708923L * 4L);
    // // up_extCalls.push_back(403374176L * 4L);
    // up_extCalls.push_back(542421688L * 4L);
    // // up_extCalls.push_back(821082289L * 4L);
    // // up_extCalls.push_back(1100133592L * 4L);

    up_extCalls.push_back(20169511L * 4L);
    up_extCalls.push_back(20169511L * 4L);
    up_extCalls.push_back(25186442L * 4L);
    up_extCalls.push_back(45958204L * 4L);
    up_extCalls.push_back(72646939L * 4L);
    up_extCalls.push_back(126986658L * 4L);
    up_extCalls.push_back(264708923L * 4L);

    std::vector<long> down_extCalls = std::vector<long>();
    // // down_extCalls.push_back(20169511L * 4L);
    // down_extCalls.push_back(20169511L * 4L);
    // // down_extCalls.push_back(20169511L * 4L);
    // down_extCalls.push_back(20169511L * 4L);
    // // down_extCalls.push_back(20169511L * 4L);
    // // down_extCalls.push_back(20768901L * 4L);
    // down_extCalls.push_back(22177547L * 4L);
    // // down_extCalls.push_back(26654572L * 4L);
    // // down_extCalls.push_back(31193626L * 4L);
    // // down_extCalls.push_back(35764797L * 4L);
    // down_extCalls.push_back(40380364L * 4L);
    // down_extCalls.push_back(63756158L * 4L);
    // down_extCalls.push_back(87445839L * 4L);
    // // down_extCalls.push_back(111316567L * 4L);
    // // down_extCalls.push_back(159359829L * 4L);
    // down_extCalls.push_back(231832704L * 4L);
    // // down_extCalls.push_back(353152192L * 4L);
    // down_extCalls.push_back(474800578L * 4L);
    // // down_extCalls.push_back(718589132L * 4L);
    // // down_extCalls.push_back(962712468L * 4L);

    down_extCalls.push_back(20169511L * 4L);
    down_extCalls.push_back(20169511L * 4L);
    down_extCalls.push_back(22177547L * 4L);
    down_extCalls.push_back(40380364L * 4L);
    down_extCalls.push_back(63756158L * 4L);
    down_extCalls.push_back(111316567L * 4L);
    down_extCalls.push_back(231832704L * 4L);

    std::vector<Float> equalSamples = std::vector<Float>();
    equalSamples.push_back(8);
    equalSamples.push_back(8);
    equalSamples.push_back(8);
    equalSamples.push_back(8);

    equalSamples.push_back(8);
    equalSamples.push_back(8);
    equalSamples.push_back(8);
    // equalSamples.push_back(8);
    // equalSamples.push_back(8);
    // //
    // equalSamples.push_back(8);
    // equalSamples.push_back(8);
    // equalSamples.push_back(8);
    // equalSamples.push_back(8);
    // equalSamples.push_back(8);
    //
    // equalSamples.push_back(8);
    // equalSamples.push_back(8);
    // equalSamples.push_back(8);
    // equalSamples.push_back(8);
    // equalSamples.push_back(8);

    std::vector<std::string> estimators = std::vector<std::string>();
    // estimators.push_back("track_length");
    // estimators.push_back("ratio");
    // estimators.push_back("next_flight_ratio");
    // estimators.push_back("unidirectional");
    // estimators.push_back("pseries_cumulative");
    estimators.push_back("pseries_cdf");
    // estimators.push_back("pseries_rr");
    // estimators.push_back("pseries_ratio");
    // estimators.push_back("pseries_next_flight_ratio");
    // estimators.push_back("pseries_interp");
    // estimators.push_back("bidirectional");

    // up valse - equal ext call renders
    for (int j = 0; j < up_extCalls.size(); ++j)
    {
        for (int i = 0; i < estimators.size(); ++i)
        {
            std::string mk_loc = "mkdir /Users/corneria/Documents/Research/pbrttest/build_final/vase_up_figure/" + std::to_string(majorants[j]);
            std::system(mk_loc.c_str());

            runEqualExtRenders_Up(options, estimators[i], majorants[j], up_extCalls[j]);
        }
    }

    // up valse - equal random pixel samples
    for (int j = 0; j < equalSamples.size(); ++j)
    {
        for (int i = 0; i < estimators.size(); ++i)
        {
            std::string mk_loc = "mkdir /Users/corneria/Documents/Research/pbrttest/build_final/vase_up_figure_strat/" + std::to_string(majorants[j]) + "_rand";
            std::system(mk_loc.c_str());

            runEqualSampleRenders_Up(options, estimators[i], majorants[j], equalSamples[j]);
        }
    }

    // up valse - equal stratified pixel samples
    for (int j = 0; j < equalSamples.size(); ++j)
    {
        for (int i = 0; i < estimators.size(); ++i)
        {
            std::string mk_loc = "mkdir /Users/corneria/Documents/Research/pbrttest/build_final/vase_up_figure_strat/" + std::to_string(majorants[j]) + "_strat";
            std::system(mk_loc.c_str());

            runEqualSampleStratifiedRenders_Up(options, estimators[i], majorants[j], equalSamples[j]);
        }
    }

    // down valse - equal ext call renders
    // for (int j = 0; j < down_extCalls.size(); ++j)
    // {
    //     for (int i = 0; i < estimators.size(); ++i)
    //     {
    //         std::string mk_loc = "mkdir /Users/corneria/Documents/Research/pbrttest/build_final/vase_down_figure/" + std::to_string(majorants[j]);
    //         std::system(mk_loc.c_str());
    //
    //         runEqualExtRenders_Down(options, estimators[i], majorants[j], down_extCalls[j]);
    //     }
    // }
    // // //
    // // // // down valse - equal random pixel samples
    // for (int j = 0; j < equalSamples.size(); ++j)
    // {
    //     for (int i = 0; i < estimators.size(); ++i)
    //     {
    //         std::string mk_loc = "mkdir /Users/corneria/Documents/Research/pbrttest/build_final/vase_down_figure_strat/" + std::to_string(majorants[j]) + "_rand";
    //         std::system(mk_loc.c_str());
    //
    //         runEqualSampleRenders_Down(options, estimators[i], majorants[j], equalSamples[j]);
    //     }
    // }
    // // //
    // // // // down valse - equal stratified pixel samples
    // for (int j = 0; j < equalSamples.size(); ++j)
    // {
    //     for (int i = 0; i < estimators.size(); ++i)
    //     {
    //         std::string mk_loc = "mkdir /Users/corneria/Documents/Research/pbrttest/build_final/vase_down_figure_strat/" + std::to_string(majorants[j]) + "_strat";
    //         std::system(mk_loc.c_str());
    //
    //         runEqualSampleStratifiedRenders_Down(options, estimators[i], majorants[j], equalSamples[j]);
    //     }
    // }
}

void Vase_Scene::initializeLightSources(bool up)
{
    pbrtAttributeBegin();

    if (up)
    {
        pbrtRotate(60.0, 0.0, 1.0, 0.0);

        initializeInfiniteLightSource("textures/skylight-morn_full.exr",
                                      std::vector<Float>{2.015, 2.015, 2.015});
    }
    else
    {
        pbrtRotate(90.0, 0.0, 1.0, 0.0);
        pbrtRotate(46.0, 1.0, 0.0, 0.0);
        pbrtTranslate(0.0, 0.0, -10.0);

        initializeInfiniteLightSource("textures/skylight-morn_full.exr",
                                      std::vector<Float>{1.45, 1.45, 1.45});
    }
    pbrtAttributeEnd();
}

void Vase_Scene::initializeVase_Up(std::string transType,
                                    Float majorant)
{
    initializeVoronoiSpiralTexture("density",
                                   std::vector<Float>{0.4, 0.8, 0.8,
                                                      0.2, 0.2, 0.2,
                                                      0.1, 0.5, 0.95},
                                   std::vector<Float>{0.3, 0.3, 0.3},
                                   std::vector<Float>{0.0, 6.28 / 3.0, 6.28 * 2.0 / 3.0},
                                   std::vector<Float>{2.0, 2.0, 2.0},
                                   std::vector<Float>{0.967742, 0.967742, 0.967742},
                                   std::vector<Float>{0.26, 0.26, 0.26},
                                   std::vector<Float>{-5.0, -5.0, 0.0},
                                   std::vector<Float>{5.0, 5.0, 25.0},
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
                               std::vector<Float>{0.7, 0.7, 0.7},
                               std::vector<Float>{0.0, 0.0, 0.0},
                               std::vector<Float>{-5.0, -5.0, 0.0},
                               std::vector<Float>{5.0, 5.0, 25.0},
                               std::vector<Float>{1.0, 1.0, 1.0},
                               majorant);

    pbrtTransformEnd();

    pbrtAttributeBegin();

    pbrtScale(0.2, 0.2, 0.2);
    pbrtTranslate(0.0, 0.0, 14.7);

    initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
                    std::vector<Float>{1.0, 1.0, 1.0},
                    1.4);

    pbrtMediumInterface("vol", "");

    std::unique_ptr<std::string[]> filename(new std::string[1]);
    filename[0] = "done_2.ply";

    ParamSet plymeshSet;
    plymeshSet.AddString("filename", std::move(filename), 1);

    pbrtShape("plymesh", plymeshSet);

    pbrtAttributeEnd();
}

void Vase_Scene::initializeVase_Down(std::string transType, Float majorant)
{
    initializeVoronoiSpiralTexture("density",
                                   std::vector<Float>{0.4, 0.8, 0.8,
                                                      0.2, 0.2, 0.2,
                                                      0.1, 0.5, 0.95},
                                   std::vector<Float>{0.3, 0.3, 0.3},
                                   std::vector<Float>{0.0, 6.28 / 3.0, 6.28 * 2.0 / 3.0},
                                   std::vector<Float>{2.0, 2.0, 2.0},
                                   std::vector<Float>{0.967742, 0.967742, 0.967742},
                                   std::vector<Float>{0.26, 0.26, 0.26},
                                   std::vector<Float>{-5.0, -5.0, 0.0},
                                   std::vector<Float>{5.0, 5.0, 25.0},
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
                               std::vector<Float>{0.7, 0.7, 0.7},
                               std::vector<Float>{0.0, 0.0, 0.0},
                               std::vector<Float>{-5.0, -5.0, 0.0},
                               std::vector<Float>{5.0, 5.0, 25.0},
                               std::vector<Float>{1.0, 1.0, 1.0},
                               majorant);

    pbrtTransformEnd();

    pbrtAttributeBegin();

    pbrtScale(0.2, 0.2, 0.2);
    pbrtRotate(180, 1.0, 0.0, 0.0);
    pbrtTranslate(0.0, 0.0, -102.0);

    initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
                    std::vector<Float>{1.0, 1.0, 1.0},
                    2.0);

    pbrtMediumInterface("vol", "");

    std::unique_ptr<std::string[]> filename(new std::string[1]);
    filename[0] = "done_2.ply";

    ParamSet plymeshSet;
    plymeshSet.AddString("filename", std::move(filename), 1);

    pbrtShape("plymesh", plymeshSet);

    pbrtAttributeEnd();
}

void Vase_Scene::runTest(pbrt::Options options, std::string transType, double angle, int index, bool isGT)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining("/Users/corneria/Documents/Research/testscenes/vase/teapot.pbrt"));
    exp_path = "/Users/corneria/Documents/Research/testscenes/vase/";

    pbrtLookAt(60, 60, 15.0,
               -1.5, 0.0, 8.0,
               0.0, 0.0, 1.0);

    // initializeCamera("perspective", 33.0);
    // initializeCamera("perspective", 23.0);
    // initializeCamera("perspective", 10.0);
    initializeCamera("perspective", 10.0);

    initializeFilm("gt_vase_down",
                   1080,
                   1920);

    initializeSampler("random", 100000);
    // initializeSampler("random", 8);

    initializeIntegrator(2000000,
                         // 3300000,
                         // 43000000,
                         -1,
                         8,
                         "volpath_recursive",
                         "stream",
                         "independent",
                         false,
                         isGT);

    pbrtWorldBegin();

    initializeLightSources(false);

    pbrtAttributeBegin();

    initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
                    std::vector<Float>{0.0, 0.0, 0.0},
                    1.1);

    initializeTrimesh(std::vector<int>{0, 1, 2, 2, 3, 0},
                      std::vector<Float>{-5000.0, -5000.0, 3.3,
                                         5000.0, -5000.0, 3.3,
                                         5000.0, 5000.0, 3.3,
                                         -5000.0, 5000.0, 3.3});

    pbrtAttributeEnd();

    initializeVase_Down(transType, 1.0);

    pbrtWorldEnd();

    pbrtCleanup();
}

void Vase_Scene::runEqualExtRenders_Up(pbrt::Options options,
                                        std::string transType,
                                        Float majorant,
                                        long samples)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining("/Users/corneria/Documents/Research/testscenes/vase/teapot.pbrt"));
    exp_path = "/Users/corneria/Documents/Research/testscenes/vase/";

    pbrtLookAt(60, 60, 15.0,
               -1.5, 0.0, 8.0,
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 10.0);

    initializeFilm("vase_up_figure/" + std::to_string(majorant) + "/" + transType,
                   1080,
                   1920);

    initializeSampler("random", 4096);

    std::cout << "SAMPLES: " << samples << std::endl;

    initializeIntegrator(2000000,
                         // 43000000,
                         // 70000000,
                         samples,
                         // -1,
                         8,
                         "volpath_recursive",
                         "independent",
                         "independent",
                         false,
                         false);

    pbrtWorldBegin();

    initializeLightSources(true);

    pbrtAttributeBegin();

    initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
                    std::vector<Float>{0.0, 0.0, 0.0},
                    1.1);

    initializeTrimesh(std::vector<int>{0, 1, 2, 2, 3, 0},
                      std::vector<Float>{-5000.0, -5000.0, 3.3,
                                         5000.0, -5000.0, 3.3,
                                         5000.0, 5000.0, 3.3,
                                         -5000.0, 5000.0, 3.3});

    pbrtAttributeEnd();

    initializeVase_Up(transType, majorant);

    pbrtWorldEnd();

    pbrtCleanup();
}

void Vase_Scene::runEqualExtRenders_Down(pbrt::Options options,
                                          std::string transType,
                                          Float majorant,
                                          long samples)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining("/Users/corneria/Documents/Research/testscenes/vase/teapot.pbrt"));
    exp_path = "/Users/corneria/Documents/Research/testscenes/vase/";

    pbrtLookAt(60, 60, 15.0,
               -1.5, 0.0, 8.0,
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 10.0);

    initializeFilm("vase_down_figure/" + std::to_string(majorant) + "/" + transType,
                   1080,
                   1920);

    initializeSampler("random", 4096);

    initializeIntegrator(2000000,
                         // 43000000,
                         // 70000000,
                         samples,
                         // -1,
                         8,
                         "volpath_recursive",
                         "independent",
                         "independent",
                         false,
                         false);

    pbrtWorldBegin();

    initializeLightSources(false);

    pbrtAttributeBegin();

    initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
                    std::vector<Float>{0.0, 0.0, 0.0},
                    1.1);

    initializeTrimesh(std::vector<int>{0, 1, 2, 2, 3, 0},
                      std::vector<Float>{-5000.0, -5000.0, 3.3,
                                         5000.0, -5000.0, 3.3,
                                         5000.0, 5000.0, 3.3,
                                         -5000.0, 5000.0, 3.3});

    pbrtAttributeEnd();

    initializeVase_Down(transType, majorant);

    pbrtWorldEnd();

    pbrtCleanup();
}

void Vase_Scene::runEqualSampleRenders_Up(pbrt::Options options,
                                           std::string transType,
                                           Float majorant,
                                           long samples)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining("/Users/corneria/Documents/Research/testscenes/vase/teapot.pbrt"));
    exp_path = "/Users/corneria/Documents/Research/testscenes/vase/";

    pbrtLookAt(60, 60, 15.0,
               -1.5, 0.0, 8.0,
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 10.0);

    initializeFilm("vase_up_figure_strat/" + std::to_string(majorant) + "_rand/" + transType+"_rand",
                   1080,
                   1920);

    std::cout << "Samples: " << samples << std::endl;
    std::cout << "Majorant: " << majorant << std::endl;

    initializeSampler("random", samples);

    initializeIntegrator(2000000,
                         // 43000000,
                         -1,
                         8,
                         "volpath_recursive",
                         "independent",
                         "independent",
                         false,
                         false);

    pbrtWorldBegin();

    initializeLightSources(true);

    pbrtAttributeBegin();

    initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
                    std::vector<Float>{0.0, 0.0, 0.0},
                    1.1);

    initializeTrimesh(std::vector<int>{0, 1, 2, 2, 3, 0},
                      std::vector<Float>{-5000.0, -5000.0, 3.3,
                                         5000.0, -5000.0, 3.3,
                                         5000.0, 5000.0, 3.3,
                                         -5000.0, 5000.0, 3.3});

    pbrtAttributeEnd();

    initializeVase_Up(transType, majorant);

    pbrtWorldEnd();

    pbrtCleanup();
}

void Vase_Scene::runEqualSampleRenders_Down(pbrt::Options options,
                                             std::string transType,
                                             Float majorant,
                                             long samples)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining("/Users/corneria/Documents/Research/testscenes/vase/teapot.pbrt"));
    exp_path = "/Users/corneria/Documents/Research/testscenes/vase/";

    pbrtLookAt(60, 60, 15.0,
               -1.5, 0.0, 8.0,
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 10.0);

    initializeFilm("vase_down_figure_strat/" + std::to_string(majorant) + "_rand/" + transType+"_rand",
                   //"convergence_test",
                   1080,
                   1920);

    initializeSampler("random", samples);

    initializeIntegrator(2000000,
                         // 43000000,
                         -1,
                         8,
                         "volpath_recursive",
                         "independent",
                         "independent",
                         false,
                         false);

    pbrtWorldBegin();

    initializeLightSources(false);

    pbrtAttributeBegin();

    initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
                    std::vector<Float>{0.0, 0.0, 0.0},
                    1.1);

    initializeTrimesh(std::vector<int>{0, 1, 2, 2, 3, 0},
                      std::vector<Float>{-5000.0, -5000.0, 3.3,
                                         5000.0, -5000.0, 3.3,
                                         5000.0, 5000.0, 3.3,
                                         -5000.0, 5000.0, 3.3});

    pbrtAttributeEnd();

    initializeVase_Down(transType, majorant);

    pbrtWorldEnd();

    pbrtCleanup();
}

void Vase_Scene::runEqualSampleStratifiedRenders_Up(pbrt::Options options,
                                                     std::string transType,
                                                     Float majorant,
                                                     long samples)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining("/Users/corneria/Documents/Research/testscenes/vase/teapot.pbrt"));
    exp_path = "/Users/corneria/Documents/Research/testscenes/vase/";

    pbrtLookAt(60.0, 60.0, 15.0,
               -1.5, 0.0, 8.0,
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 10.0);

    initializeFilm("vase_up_figure_strat/" + std::to_string(majorant) + "_strat/" + transType+"_strat",
                   1080,
                   1920);

    initializeSampler("random", samples);

    initializeIntegrator(2000000,
                         // 43000000,
                         -1,
                         8,
                         "volpath_recursive",
                         "stream",
                         "independent",
                         false,
                         false);

    pbrtWorldBegin();

    initializeLightSources(true);

    pbrtAttributeBegin();

    initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
                    std::vector<Float>{0.0, 0.0, 0.0},
                    1.1);

    initializeTrimesh(std::vector<int>{0, 1, 2, 2, 3, 0},
                      std::vector<Float>{-5000.0, -5000.0, 3.3,
                                         5000.0, -5000.0, 3.3,
                                         5000.0, 5000.0, 3.3,
                                         -5000.0, 5000.0, 3.3});

    pbrtAttributeEnd();

    initializeVase_Up(transType, majorant);

    pbrtWorldEnd();

    pbrtCleanup();
}

void Vase_Scene::runEqualSampleStratifiedRenders_Down(pbrt::Options options,
                                                       std::string transType,
                                                       Float majorant,
                                                       long samples)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining("/Users/corneria/Documents/Research/testscenes/vase/teapot.pbrt"));
    exp_path = "/Users/corneria/Documents/Research/testscenes/vase/";

    pbrtLookAt(60.0, 60.0, 15.0,
               -1.5, 0.0, 8.0,
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 10.0);

    initializeFilm("vase_down_figure_strat/" + std::to_string(majorant) + "_strat/" + transType+"_strat",
                   1080,
                   1920);

    initializeSampler("random", samples);

    initializeIntegrator(2000000,
                         // 43000000,
                         -1,
                         8,
                         "volpath_recursive",
                         "stream",
                         "independent",
                         false,
                         false);

    pbrtWorldBegin();

    initializeLightSources(false);

    pbrtAttributeBegin();

    initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
                    std::vector<Float>{0.0, 0.0, 0.0},
                    1.1);

    initializeTrimesh(std::vector<int>{0, 1, 2, 2, 3, 0},
                      std::vector<Float>{-5000.0, -5000.0, 3.3,
                                         5000.0, -5000.0, 3.3,
                                         5000.0, 5000.0, 3.3,
                                         -5000.0, 5000.0, 3.3});

    pbrtAttributeEnd();

    initializeVase_Down(transType, majorant);

    pbrtWorldEnd();

    pbrtCleanup();
}
