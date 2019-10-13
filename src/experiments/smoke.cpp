#include "smoke.h"

#if OPENVDB

Smoke_Scene::Smoke_Scene(pbrt::Options options, ExperimentFlags flags)
{
    std::string mk_loc = "mkdir vdb_figure";
    std::system(mk_loc.c_str());

    if (flags.run_equal_extinctions)
    {
        // equal ext call renders
        for (int j = 0; j < flags.ext_calls.size(); ++j)
        {
            for (int i = 0; i < flags.estimators.size(); ++i)
            {
                std::string mk_loc = "mkdir vdb_figure/" + std::to_string(flags.majorants[j]);
                std::system(mk_loc.c_str());

                runEqualExtRenders(options, flags.estimators[i], flags.majorants[j], flags.ext_calls[j]);
            }
        }
    }

    if (flags.run_equal_samples)
    {
        mk_loc = "mkdir vdb_figure_strat";
        std::system(mk_loc.c_str());

        for (int j = 0; j < flags.spp.size(); ++j)
        {
            for (int i = 0; i < flags.estimators.size(); ++i)
            {
                std::string mk_loc = "mkdir vdb_figure_strat/" + std::to_string(flags.majorants[j]) + "_rand";
                std::system(mk_loc.c_str());

                runEqualSampleRenders(options, flags.estimators[i], flags.majorants[j], 8);
            }
        }
    }

    if (flags.run_stratified_samples)
    {
        mk_loc = "mkdir vdb_figure_strat";
        std::system(mk_loc.c_str());

        for (int j = 0; j < flags.spp.size(); ++j)
        {
            for (int i = 0; i < flags.estimators.size(); ++i)
            {
                std::string mk_loc = "mkdir vdb_figure_strat/" + std::to_string(flags.majorants[j]) + "_strat";
                std::system(mk_loc.c_str());

                runEqualSampleStratifiedRenders(options, flags.estimators[i], flags.majorants[j], 8);
            }
        }
    }
}

void Smoke_Scene::initializeSceneMediumBox(std::string transType,
                                               std::string name,
                                               std::string maj,
                                               Float majorant)
{
    pbrtAttributeBegin();

    // I hope this works
    pbrtScale(60.0, 60.0, 60.0);
    pbrtTranslate(0.0, 0.0, 0.5);

    Float min = -0.5;
    Float max = 0.5;

    initializeVDBMedium("vol",
                        "heterogeneous",
                        transType,
                        maj,
                        "const",
                        "absorptive",
                        std::vector<Float>{0.3, 0.3, 0.3},
                        std::vector<Float>{0.0, 0.0, 0.0},
                        std::vector<Float>{min, min, min},
                        std::vector<Float>{max, max, max},
                        false,
                        true,
                        false,
                        true,
                        majorant,
                        name);

    pbrtMaterial("", ParamSet());
    pbrtMediumInterface("vol", "");

    // debugging logic
    // initializeMaterial_Matte(std::vector<Float>{1.0, 0.0, 0.0});

    // NOTE: These have to be the same as the min bounds
    initializeBoxShape(min, max, min, max, min, max);

    pbrtAttributeEnd();
}

void Smoke_Scene::runTest(std::string transType, bool isGT, std::string name, int iter)
{
    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/vdb_smoke/dragon_10.pbrt"));
    exp_path = TEST_SCENES_PATH "/vdb_smoke/";

    initializeIntegrator(200000000,
                         // 100000000,
                         -1,
                         5,
                         "volpath_recursive",
                         //"volpath",
                         "stream",
                         "independent",
                         false,
                         isGT);

    initializeSampler("random", 24000);

    initializePixelFilter("box");

    initializeFilm(//"Smoke_Scene/take_5_" + std::to_string(iter) + "_" + transType,
                   "gt_vdb",
                   900,
                   1100);

    pbrtScale(-1.0, 1.0, 1.0);

    // pbrtLookAt(2.8 + 24.0, -2.8 - 24.0, 15.5,
             // -1.8 - 15.0, 1.8 + 15.0, 13.5, // was at .4
             // 0.0, 0.0, 15.5, // was at .4
             // 0.0, 0.0, 1.0);

    pbrtLookAt(50.0, -60.0, 40.5,
               0.0, 0.0, 33.0, // was at .4
               // 0.0, 0.0, 15.5, // was at .4
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 35); // was at 30

    pbrtWorldBegin();

    initializeLightSources();

    pbrtAttributeBegin();
    initializeMaterial_Matte(std::vector<Float>{0.56, 0.56, 0.56});
    pbrtRotate(135.0, 0.0, 0.0, 1.0);
    pbrtTranslate(0.0, 0.0, -1.0);

    pbrtScale(20.0, 100.0, 100.0);
    // pbrtTranslate(0.0, 0.0, -30.0);
    initializePlyShape("geometry/photo_backdrop_smooth_2.ply");
    pbrtAttributeEnd();

    // for alignment purposes only
    // pbrtAttributeBegin();
    // initializeMaterial_Matte(std::vector<Float>{1.0, 0.0, 0.0});
    // initializeSphereShape(1.0);
    // pbrtAttributeEnd();

    // initializeSceneMedium(transType, name);
    initializeSceneMediumBox(transType,
                             name,
                             "const",
                             1.0);

    pbrtWorldEnd();
}

void Smoke_Scene::runEqualExtRenders(pbrt::Options options,
                                         std::string transType,
                                         Float majorant,
                                         int samples)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/vdb_smoke/dragon_10.pbrt"));
    exp_path = TEST_SCENES_PATH "/vdb_smoke/";

    initializeIntegrator(200000000,
                         samples,
                         // -1,
                         5,
                         "volpath_recursive",
                         //"volpath",
                         "independent",
                         "independent",
                         false,
                         false);

    initializeSampler("random", 8192);

    initializePixelFilter("box");

    initializeFilm("vdb_figure/" + std::to_string(majorant) + "/" + transType,
                   //"better_smoke_test_60",
                   900,
                   1100);

    pbrtScale(-1.0, 1.0, 1.0);

    pbrtLookAt(50.0, -60.0, 40.5,
               0.0, 0.0, 33.0, // was at .4
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 35); // was at 30

    pbrtWorldBegin();

    initializeLightSources();

    pbrtAttributeBegin();
    initializeMaterial_Matte(std::vector<Float>{0.56, 0.56, 0.56});
    pbrtRotate(135.0, 0.0, 0.0, 1.0);
    pbrtTranslate(0.0, 0.0, -1.0);

    pbrtScale(20.0, 100.0, 100.0);
    initializePlyShape("geometry/photo_backdrop_smooth_2.ply");
    pbrtAttributeEnd();

    initializeSceneMediumBox(transType,
                             "simple_smoke_66.vdb",
                             "const",
                             majorant);

    pbrtWorldEnd();

    pbrtCleanup();
}

void Smoke_Scene::runEqualSampleRenders(pbrt::Options options,
                                            std::string transType,
                                            Float majorant,
                                            int samples)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/vdb_smoke/dragon_10.pbrt"));
    exp_path = TEST_SCENES_PATH "/vdb_smoke/";

    initializeIntegrator(200000000,
                         //400000000,
                         -1,
                         5,
                         "volpath_recursive",
                         //"volpath",
                         "independent",
                         "independent",
                         false,
                         false);

    initializeSampler("random", samples);

    initializePixelFilter("box");

    initializeFilm("vdb_figure_strat/" + std::to_string(majorant) + "_rand/" + transType + "_rand",
                   //"better_smoke_test_60",
                   900,
                   1100);

    pbrtScale(-1.0, 1.0, 1.0);

    pbrtLookAt(50.0, -60.0, 40.5,
               0.0, 0.0, 33.0, // was at .4
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 35); // was at 30

    pbrtWorldBegin();

    initializeLightSources();

    pbrtAttributeBegin();
    initializeMaterial_Matte(std::vector<Float>{0.56, 0.56, 0.56});
    pbrtRotate(135.0, 0.0, 0.0, 1.0);
    pbrtTranslate(0.0, 0.0, -1.0);

    pbrtScale(20.0, 100.0, 100.0);
    initializePlyShape("geometry/photo_backdrop_smooth_2.ply");
    pbrtAttributeEnd();

    initializeSceneMediumBox(transType,
                             "simple_smoke_66.vdb",
                             "const",
                             majorant);

    pbrtWorldEnd();

    pbrtCleanup();
}

void Smoke_Scene::runEqualExtRenders_Macrogrid(std::string transType,
                                                   Float majorant,
                                                   int samples)
{
    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/vdb_smoke/dragon_10.pbrt"));
    exp_path = TEST_SCENES_PATH "/vdb_smoke/";

    initializeIntegrator(200000000,
                         samples,
                         // -1,
                         5,
                         "volpath_recursive",
                         //"volpath",
                         "independent",
                         "independent",
                         false,
                         false);

    initializeSampler("random", 8192);

    initializePixelFilter("box");

    initializeFilm("vdb_macro_figure/" + std::to_string(majorant) + "/" + transType,
                   //"better_smoke_test_60",
                   900,
                   1100);

    pbrtScale(-1.0, 1.0, 1.0);

    pbrtLookAt(50.0, -60.0, 40.5,
               0.0, 0.0, 33.0, // was at .4
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 35); // was at 30

    pbrtWorldBegin();

    initializeLightSources();

    pbrtAttributeBegin();
    initializeMaterial_Matte(std::vector<Float>{0.56, 0.56, 0.56});
    pbrtRotate(135.0, 0.0, 0.0, 1.0);
    pbrtTranslate(0.0, 0.0, -1.0);

    pbrtScale(20.0, 100.0, 100.0);
    initializePlyShape("geometry/photo_backdrop_smooth_2.ply");
    pbrtAttributeEnd();

    initializeSceneMediumBox(transType,
                             "simple_smoke_66.vdb",
                             "vdb",
                             majorant);

    pbrtWorldEnd();
}

void Smoke_Scene::runEqualSampleRenders_Macrogrid(std::string transType,
                                                      Float majorant,
                                                      int samples)
{
    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/vdb_smoke/dragon_10.pbrt"));
    exp_path = TEST_SCENES_PATH "/vdb_smoke/";

    initializeIntegrator(200000000,
                         //400000000,
                         -1,
                         5,
                         "volpath_recursive",
                         //"volpath",
                         "independent",
                         "independent",
                         false,
                         false);

    initializeSampler("random", samples);

    initializePixelFilter("box");

    initializeFilm("vdb_macro_figure_rand/" + std::to_string(majorant) + "/" + transType + "_rand",
                   //"better_smoke_test_60",
                   900,
                   1100);

    pbrtScale(-1.0, 1.0, 1.0);

    pbrtLookAt(50.0, -60.0, 40.5,
               0.0, 0.0, 33.0, // was at .4
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 35); // was at 30

    pbrtWorldBegin();

    initializeLightSources();

    pbrtAttributeBegin();
    initializeMaterial_Matte(std::vector<Float>{0.56, 0.56, 0.56});
    pbrtRotate(135.0, 0.0, 0.0, 1.0);
    pbrtTranslate(0.0, 0.0, -1.0);

    pbrtScale(20.0, 100.0, 100.0);
    initializePlyShape("geometry/photo_backdrop_smooth_2.ply");
    pbrtAttributeEnd();

    initializeSceneMediumBox(transType,
                             "simple_smoke_66.vdb",
                             "vdb",
                             majorant);

    pbrtWorldEnd();
}

void Smoke_Scene::runEqualSampleStratifiedRenders_Macrogrid(std::string transType,
                                                                Float majorant,
                                                                int samples)
{
    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/vdb_smoke/dragon_10.pbrt"));
    exp_path = TEST_SCENES_PATH "/vdb_smoke/";

    initializeIntegrator(200000000,
                         //400000000,
                         -1,
                         5,
                         "volpath_recursive",
                         //"volpath",
                         "stream",
                         "independent",
                         false,
                         false);

    initializeSampler("random", samples);

    initializePixelFilter("box");

    initializeFilm("vdb_macro_figure_strat/" + std::to_string(majorant) + "/" + transType + "_strat",
                   //"better_smoke_test_60",
                   900,
                   1100);

    pbrtScale(-1.0, 1.0, 1.0);

    pbrtLookAt(50.0, -60.0, 40.5,
               0.0, 0.0, 33.0, // was at .4
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 35); // was at 30

    pbrtWorldBegin();

    initializeLightSources();

    pbrtAttributeBegin();
    initializeMaterial_Matte(std::vector<Float>{0.56, 0.56, 0.56});
    pbrtRotate(135.0, 0.0, 0.0, 1.0);
    pbrtTranslate(0.0, 0.0, -1.0);

    pbrtScale(20.0, 100.0, 100.0);
    initializePlyShape("geometry/photo_backdrop_smooth_2.ply");
    pbrtAttributeEnd();

    initializeSceneMediumBox(transType,
                             "simple_smoke_66.vdb",
                             "vdb",
                             majorant);

    pbrtWorldEnd();
}

void Smoke_Scene::runEqualSampleStratifiedRenders(pbrt::Options options,
                                                      std::string transType,
                                                      Float majorant,
                                                      int samples)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/vdb_smoke/dragon_10.pbrt"));
    exp_path = TEST_SCENES_PATH "/vdb_smoke/";

    initializeIntegrator(200000000,
                         //400000000,
                         -1,
                         5,
                         "volpath_recursive",
                         //"volpath",
                         "stream",
                         "independent",
                         false,
                         false);

    initializeSampler("random", samples);

    initializePixelFilter("box");

    initializeFilm("vdb_figure_strat/" + std::to_string(majorant) + "_strat/" + transType + "_strat",
                   //"better_smoke_test_60",
                   900,
                   1100);

    pbrtScale(-1.0, 1.0, 1.0);

    pbrtLookAt(50.0, -60.0, 40.5,
               0.0, 0.0, 33.0, // was at .4
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 35); // was at 30

    pbrtWorldBegin();

    initializeLightSources();

    pbrtAttributeBegin();
    initializeMaterial_Matte(std::vector<Float>{0.56, 0.56, 0.56});
    pbrtRotate(135.0, 0.0, 0.0, 1.0);
    pbrtTranslate(0.0, 0.0, -1.0);

    pbrtScale(20.0, 100.0, 100.0);
    initializePlyShape("geometry/photo_backdrop_smooth_2.ply");
    pbrtAttributeEnd();

    initializeSceneMediumBox(transType,
                             "simple_smoke_66.vdb",
                             "const",
                             majorant);

    pbrtWorldEnd();

    pbrtCleanup();
}

void Smoke_Scene::initializeLightSources()
{
    pbrtAttributeBegin();

    initializeDistantLightSource(std::vector<Float>{2.0, 2.0, 2.0},
                                 Point3f(1.0, -4.0, 1.5),
                                 Point3f(0.0, 0.0, 0.0));

    pbrtAttributeEnd();

    pbrtAttributeBegin();

    initializeDistantLightSource(std::vector<Float>{3.0, 3.0, 3.0},
                                 Point3f(-5.0, -4.0, 11.0),
                                 Point3f(0.0, 0.0, 0.0));

    pbrtAttributeEnd();

    pbrtAttributeBegin();

    initializeDistantLightSource(std::vector<Float>{3.0, 3.0, 3.0},
                                 Point3f(1.0, -1.0, 0.1),
                                 Point3f(0.0, 0.0, 0.0));

    pbrtAttributeEnd();
}

#endif
