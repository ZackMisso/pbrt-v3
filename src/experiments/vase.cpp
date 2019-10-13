#include "vase.h"

Vase_Scene::Vase_Scene(pbrt::Options options, ExperimentFlags flags)
{
    std::string mk_loc = "mkdir vase_down_figure";
    std::system(mk_loc.c_str());

    mk_loc = "mkdir vase_up_figure";
    std::system(mk_loc.c_str());

    if (flags.run_equal_extinctions)
    {
        // equal ext call renders
        for (int j = 0; j < flags.ext_calls.size(); ++j)
        {
            for (int i = 0; i < flags.estimators.size(); ++i)
            {
                mk_loc = "mkdir vase_down_figure/" + std::to_string(flags.majorants[j]);
                std::system(mk_loc.c_str());

                runEqualExtRenders_Down(options, flags.estimators[i], flags.majorants[j], flags.ext_calls[j]);

                mk_loc = "mkdir vase_up_figure/" + std::to_string(flags.majorants[j]);
                std::system(mk_loc.c_str());

                runEqualExtRenders_Up(options, flags.estimators[i], flags.majorants[j], flags.ext_calls[j]);
            }
        }
    }

    if (flags.run_equal_samples)
    {
        mk_loc = "mkdir vase_down_figure_strat";
        std::system(mk_loc.c_str());

        mk_loc = "mkdir vase_up_figure_strat";
        std::system(mk_loc.c_str());

        for (int j = 0; j < flags.spp.size(); ++j)
        {
            for (int i = 0; i < flags.estimators.size(); ++i)
            {
                mk_loc = "mkdir vase_down_figure_strat/" + std::to_string(flags.majorants[j]) + "_rand";
                std::system(mk_loc.c_str());

                runEqualSampleRenders_Down(options, flags.estimators[i], flags.majorants[j], 8);

                mk_loc = "mkdir vase_up_figure_strat/" + std::to_string(flags.majorants[j]) + "_rand";
                std::system(mk_loc.c_str());

                runEqualSampleRenders_Up(options, flags.estimators[i], flags.majorants[j], 8);
            }
        }
    }

    if (flags.run_stratified_samples)
    {
        mk_loc = "mkdir vase_down_figure_strat";
        std::system(mk_loc.c_str());

        mk_loc = "mkdir vase_up_figure_strat";
        std::system(mk_loc.c_str());

        for (int j = 0; j < flags.spp.size(); ++j)
        {
            for (int i = 0; i < flags.estimators.size(); ++i)
            {
                mk_loc = "mkdir vase_down_figure_strat/" + std::to_string(flags.majorants[j]) + "_strat";
                std::system(mk_loc.c_str());

                runEqualSampleStratifiedRenders_Down(options, flags.estimators[i], flags.majorants[j], 8);

                mk_loc = "mkdir vase_up_figure_strat/" + std::to_string(flags.majorants[j]) + "_strat";
                std::system(mk_loc.c_str());

                runEqualSampleStratifiedRenders_Up(options, flags.estimators[i], flags.majorants[j], 8);
            }
        }
    }
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

    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/vase/teapot.pbrt"));
    exp_path = TEST_SCENES_PATH "/vase/";

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

    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/vase/teapot.pbrt"));
    exp_path = TEST_SCENES_PATH "/vase/";

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

    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/vase/teapot.pbrt"));
    exp_path = TEST_SCENES_PATH "/vase/";

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

    std::cout << "HUH" << std::endl;

    pbrtWorldEnd();

    pbrtCleanup();
}

void Vase_Scene::runEqualSampleRenders_Up(pbrt::Options options,
                                           std::string transType,
                                           Float majorant,
                                           long samples)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/vase/teapot.pbrt"));
    exp_path = TEST_SCENES_PATH "/vase/";

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

    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/vase/teapot.pbrt"));
    exp_path = TEST_SCENES_PATH "/vase/";

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

    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/vase/teapot.pbrt"));
    exp_path = TEST_SCENES_PATH "/vase/";

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

    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/vase/teapot.pbrt"));
    exp_path = TEST_SCENES_PATH "/vase/";

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
