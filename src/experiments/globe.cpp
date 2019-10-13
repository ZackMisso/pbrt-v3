#include "globe.h"

#if OPENVDB

Globe_Scene::Globe_Scene(pbrt::Options options, ExperimentFlags flags)
{
    std::string mk_loc = "mkdir globe_figure";
    std::system(mk_loc.c_str());

    if (flags.run_equal_extinctions)
    {
        // equal ext call renders
        for (int j = 0; j < flags.ext_calls.size(); ++j)
        {
            for (int i = 0; i < flags.estimators.size(); ++i)
            {
                std::string mk_loc = "mkdir globe_figure/" + std::to_string(flags.majorants[j]);
                std::system(mk_loc.c_str());

                runEqualExtRenders(options, flags.estimators[i], flags.majorants[j], flags.ext_calls[j]);
            }
        }
    }

    if (flags.run_equal_samples)
    {
        mk_loc = "mkdir globe_figure_strat";
        std::system(mk_loc.c_str());

        for (int j = 0; j < flags.spp.size(); ++j)
        {
            for (int i = 0; i < flags.estimators.size(); ++i)
            {
                std::string mk_loc = "mkdir globe_figure_strat/" + std::to_string(flags.majorants[j]) + "_rand";
                std::system(mk_loc.c_str());

                runEqualSampleRenders(options, flags.estimators[i], flags.majorants[j], 8);
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
                std::string mk_loc = "mkdir globe_figure_strat/" + std::to_string(flags.majorants[j]) + "_strat";
                std::system(mk_loc.c_str());

                runEqualSampleStratifiedRenders(options, flags.estimators[i], flags.majorants[j], 8);
            }
        }
    }
}

void Globe_Scene::initializeSceneMediumBox(std::string transType,
                                               std::string name,
                                               std::string maj,
                                               Float majorant)
{
    pbrtAttributeBegin();

    pbrtScale(60.0, 60.0, 60.0);
    pbrtTranslate(0.0, 0.0, 0.5);

    pbrtTranslate(-0.02, 0.0, 0.0);

    Float min = -0.65;
    Float max = 0.65;

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

    pbrtTranslate(0.02, 0.0, 0.0);

    pbrtMediumInterface("vol", "");
    initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
                    std::vector<Float>{1.0, 1.0, 1.0},
                    1.5);
    initializeSphereShape(0.75);

    pbrtAttributeEnd();
}

void Globe_Scene::runTest(pbrt::Options options, std::string transType, bool isGT, std::string name, int iter)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/sphere_smoke/dragon_10.pbrt"));
    exp_path = TEST_SCENES_PATH "/sphere_smoke/";

    initializeIntegrator(200000000,
                         // 100000000,
                         -1,
                         5,
                         "volpath_recursive",
                         // "vol_sppm",
                         //"bdpt",
                         // "sppm",
                         "stream",
                         "independent",
                         false,
                         isGT);

    initializeSampler("random", 50000);

    initializePixelFilter("box");

    initializeFilm("gt_sphere",
                   800,
                   800);

    pbrtScale(-1.0, 1.0, 1.0);

    pbrtLookAt(90.0, -110.0, 40.5,
               0.0, 0.0, 33.0, // was at .4
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 40); // was at 40

    pbrtWorldBegin();

    initializeLightSources();

    pbrtAttributeBegin();
    initializeMaterial_Matte(std::vector<Float>{0.56, 0.56, 0.56});
    pbrtRotate(135.0, 0.0, 0.0, 1.0);
    pbrtTranslate(0.0, 0.0, -30.0);

    pbrtScale(60.0, 300.0, 300.0);
    initializePlyShape("geometry/photo_backdrop_smooth_2.ply");
    pbrtAttributeEnd();

    initializeSceneMediumBox(transType,
                             "wdas_cloud.vdb",
                             "const",
                             1.0);

    pbrtWorldEnd();

    pbrtCleanup();
}

void Globe_Scene::runEqualExtRenders(pbrt::Options options,
                                     std::string transType,
                                     Float majorant,
                                     long samples)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/sphere_smoke/dragon_10.pbrt"));
    exp_path = TEST_SCENES_PATH "/sphere_smoke/";

    initializeIntegrator(200000000,
                         samples,
                         5,
                         "volpath_recursive",
                         "independent",
                         "independent",
                         false,
                         false);

    initializeSampler("random", 8192);

    initializePixelFilter("box");

    initializeFilm("globe_figure/" + std::to_string(majorant) + "/" + transType,
                   800,
                   800);

    pbrtScale(-1.0, 1.0, 1.0);

    pbrtLookAt(90.0, -110.0, 40.5,
               0.0, 0.0, 33.0, // was at .4
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 40); // was at 30

    pbrtWorldBegin();

    initializeLightSources();

    pbrtAttributeBegin();
    initializeMaterial_Matte(std::vector<Float>{0.56, 0.56, 0.56});
    pbrtRotate(135.0, 0.0, 0.0, 1.0);
    pbrtTranslate(0.0, 0.0, -30.0);

    pbrtScale(60.0, 300.0, 300.0);
    initializePlyShape("geometry/photo_backdrop_smooth_2.ply");
    pbrtAttributeEnd();

    initializeSceneMediumBox(transType,
                             "wdas_cloud.vdb",
                             "const",
                             majorant);

    pbrtWorldEnd();

    pbrtCleanup();
}

void Globe_Scene::runEqualSampleRenders(pbrt::Options options,
                                        std::string transType,
                                        Float majorant,
                                        long samples)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/sphere_smoke/dragon_10.pbrt"));
    exp_path = TEST_SCENES_PATH "/sphere_smoke/";

    initializeIntegrator(200000000,
                         -1,
                         5,
                         "volpath_recursive",
                         "independent",
                         "independent",
                         false,
                         false);

    initializeSampler("random", samples);

    initializePixelFilter("box");

    initializeFilm("globe_figure_strat/" + std::to_string(majorant) + "/_rand" + transType + "_rand",
                   800,
                   800);

    pbrtScale(-1.0, 1.0, 1.0);

    pbrtLookAt(90.0, -110.0, 40.5,
               0.0, 0.0, 33.0, // was at .4
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 40); // was at 30

    pbrtWorldBegin();

    initializeLightSources();

    pbrtAttributeBegin();
    initializeMaterial_Matte(std::vector<Float>{0.56, 0.56, 0.56});
    pbrtRotate(135.0, 0.0, 0.0, 1.0);
    pbrtTranslate(0.0, 0.0, -30.0);

    pbrtScale(60.0, 300.0, 300.0);
    initializePlyShape("geometry/photo_backdrop_smooth_2.ply");
    pbrtAttributeEnd();

    initializeSceneMediumBox(transType,
                             "wdas_cloud.vdb",
                             "const",
                             majorant);

    pbrtWorldEnd();

    pbrtCleanup();
}

void Globe_Scene::runEqualSampleStratifiedRenders(pbrt::Options options,
                                                  std::string transType,
                                                  Float majorant,
                                                  long samples)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/sphere_smoke/dragon_10.pbrt"));
    exp_path = TEST_SCENES_PATH "/sphere_smoke/";

    initializeIntegrator(200000000,
                         -1,
                         5,
                         "volpath_recursive",
                         "independent",
                         "independent",
                         false,
                         false);

    initializeSampler("random", samples);

    initializePixelFilter("box");

    initializeFilm("globe_figure_strat/" + std::to_string(majorant) + "_strat/" + transType + "_strat",
                   800,
                   800);

    pbrtScale(-1.0, 1.0, 1.0);

    pbrtLookAt(90.0, -110.0, 40.5,
               0.0, 0.0, 33.0, // was at .4
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 40); // was at 30

    pbrtWorldBegin();

    initializeLightSources();

    pbrtAttributeBegin();
    initializeMaterial_Matte(std::vector<Float>{0.56, 0.56, 0.56});
    pbrtRotate(135.0, 0.0, 0.0, 1.0);
    pbrtTranslate(0.0, 0.0, -30.0);

    pbrtScale(60.0, 300.0, 300.0);
    initializePlyShape("geometry/photo_backdrop_smooth_2.ply");
    pbrtAttributeEnd();

    initializeSceneMediumBox(transType,
                             "wdas_cloud.vdb",
                             "const",
                             majorant);

    pbrtWorldEnd();

    pbrtCleanup();
}

void Globe_Scene::initializeLightSources()
{
    pbrtAttributeBegin();

    // pbrtTranslate(10.0, -40.0, 40.0);
    //
    // initializePointLightSource(std::vector<Float>{5000.0, 5000.0, 5000.0});

    initializeDistantLightSource(std::vector<Float>{2.0, 2.0, 2.0},
                                 Point3f(1.0, -4.0, 1.5),
                                 Point3f(0.0, 0.0, 0.0));

    pbrtAttributeEnd();

    pbrtAttributeBegin();

    // pbrtTranslate(-50.0, -40.0, 110.0);
    //
    // initializePointLightSource(std::vector<Float>{10000.0, 10000.0, 10000.0});

    initializeDistantLightSource(std::vector<Float>{3.0, 3.0, 3.0},
                                 Point3f(-5.0, -4.0, 11.0),
                                 Point3f(0.0, 0.0, 0.0));

    pbrtAttributeEnd();

    pbrtAttributeBegin();
    //
    // pbrtTranslate(-60.0, 60.0, 30.0);
    //
    // initializePointLightSource(std::vector<Float>{5000.0, 5000.0, 5000.0});

    initializeDistantLightSource(std::vector<Float>{3.0, 3.0, 3.0},
                                 Point3f(1.0, -1.0, 0.1),
                                 Point3f(0.0, 0.0, 0.0));

    pbrtAttributeEnd();
}

#endif
