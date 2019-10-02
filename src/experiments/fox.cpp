#include "fox.h"

Fox_Scene::Fox_Scene(pbrt::Options options)
{
    int maxi = 30 * 30;
    int index = 605 % 30;
    int psi_index = 605 / 30;
    double angle = 6.28 * double(index) / 30.0;
    double psi = double(psi_index) / 30.0;

    // runTest("track_length", false, angle, psi, 605);
    // runTest(options, "ratio", true, angle, psi, 605);

    // int maxi = 30 * 30;
    // for (int i = 605; i < 606; ++i)
    // {
    //     int index = i % 30;
    //     int psi_index = i / 30;
    //     double angle = 6.28 * double(index) / 30.0;
    //     double psi = double(psi_index) / 30.0;
    //     runTest("ratio", true, angle, psi, i);
    // }

    std::vector<Float> majorants = std::vector<Float>();

//     majorants.push_back(0.1);
//     // majorants.push_back(0.2);
//     majorants.push_back(0.3);
//     // majorants.push_back(0.4);
//
//     // majorants.push_back(0.5);
//     majorants.push_back(0.6);
//     // majorants.push_back(0.7);
//     // majorants.push_back(0.8);
//     // majorants.push_back(0.9);
// //
//     majorants.push_back(1.0);
//     majorants.push_back(1.5);
//     majorants.push_back(2.0);
//     // majorants.push_back(2.5);
//     // majorants.push_back(3.5);
//
//     majorants.push_back(5.0);
//     // majorants.push_back(7.5);
//     majorants.push_back(10.0);
//     // majorants.push_back(15.0);
//     // majorants.push_back(20.0);

    // majorants.push_back(0.1);
    // majorants.push_back(0.3);
    // majorants.push_back(0.6);
    majorants.push_back(1.0);
    // majorants.push_back(1.5);
    // majorants.push_back(2.5);
    // majorants.push_back(5.0);

    std::vector<Float> extCalls = std::vector<Float>();
    // extCalls.push_back(5965499 * 8);
    // // extCalls.push_back(7265499 * 8);
    // extCalls.push_back(8965499 * 8);
    // // extCalls.push_back(10065499 * 8);
    // // extCalls.push_back(12965499 * 3);
    // extCalls.push_back(16055417 * 3);
    // // extCalls.push_back(19192619 * 3);
    // // extCalls.push_back(22354414 * 3);
    // // extCalls.push_back(25543645 * 3);
    // extCalls.push_back(28745021 * 3);
    // extCalls.push_back(44924520 * 2);
    // extCalls.push_back(61275672 * 2);
    // // extCalls.push_back(77719541 * 2);
    // // extCalls.push_back(110752636 * 2);
    // extCalls.push_back(160525061 * 2);
    // // extCalls.push_back(243756923 * 2);
    // extCalls.push_back(327155702 * 2);
    // // extCalls.push_back(494208588 * 2);
    // // extCalls.push_back(661431711 * 2);

    // use these
    // extCalls.push_back(5965499 * 8);
    // extCalls.push_back(8965499 * 8);
    // extCalls.push_back(16055417 * 3);
    extCalls.push_back(28745021 * 3);
    // extCalls.push_back(44924520 * 2);
    // extCalls.push_back(77719541 * 2);
    // extCalls.push_back(160525061 * 2);

    std::vector<Float> equalSamples = std::vector<Float>();
    equalSamples.push_back(8);
    // equalSamples.push_back(8);
    // equalSamples.push_back(8);
    // equalSamples.push_back(8);

    // equalSamples.push_back(8);
    // equalSamples.push_back(8);
    // equalSamples.push_back(8);
    // equalSamples.push_back(8);
    // equalSamples.push_back(8);

    // equalSamples.push_back(8);
    // equalSamples.push_back(8);
    // equalSamples.push_back(8);
    // equalSamples.push_back(8);
    // equalSamples.push_back(8);

    // equalSamples.push_back(8);
    // equalSamples.push_back(8);
    // equalSamples.push_back(8);
    // equalSamples.push_back(8);
    // equalSamples.push_back(8);

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

    // // equal ext call renders
    for (int j = 0; j < extCalls.size(); ++j)
    {
        for (int i = 0; i < estimators.size(); ++i)
        {
            std::string mk_loc = "mkdir fox_figure/" + std::to_string(majorants[j]);
            std::system(mk_loc.c_str());

            runEqualExtRenders(options, estimators[i], false, angle, psi, 605, majorants[j], extCalls[j]);
        }
    }
    //
    // // equal random pixel samples
    // for (int j = 0; j < equalSamples.size(); ++j)
    // {
    //     for (int i = 0; i < estimators.size(); ++i)
    //     {
    //         std::string mk_loc = "mkdir /Users/corneria/Documents/Research/pbrttest/build_final/fox_figure_strat/" + std::to_string(majorants[j]) + "_rand";
    //         std::system(mk_loc.c_str());
    //
    //         runEqualSampleRenders(options, estimators[i], false, angle, psi, 605, majorants[j], equalSamples[j]);
    //     }
    // }
    //
    // // equal stratified pixel samples
    // for (int j = 0; j < equalSamples.size(); ++j)
    // {
    //     for (int i = 0; i < estimators.size(); ++i)
    //     {
    //         std::string mk_loc = "mkdir /Users/corneria/Documents/Research/pbrttest/build_final/fox_figure_strat/" + std::to_string(majorants[j]) + "_strat";
    //         std::system(mk_loc.c_str());
    //
    //         runEqualSampleStratifiedRenders(options, estimators[i], false, angle, psi, 605, majorants[j], equalSamples[j]);
    //     }
    // }
}

void Fox_Scene::runTest(pbrt::Options options, std::string transType, bool isGT, double angle, double psi, int iter)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining("/Users/corneria/Documents/Research/testscenes/fennec_fox/teapot.pbrt"));
    exp_path = "/Users/corneria/Documents/Research/testscenes/fennec_fox/";

    double xpos = 65.0 / cos(3.141569 / 4.0) * cos(angle) + 8.0;
    double ypos = 65.0 / cos(3.141569 / 4.0) * sin(angle) + 12.0;
    double zpos = psi * (25.0 + 16.0) - 16.0;

    pbrtLookAt(xpos, ypos, zpos,
               5.5,   12.0, -15.5, // was at -16.0
               0.0,   0.0,  1.0);

    // pbrtLookAt(65.0, 65.0, 15.0,
    //            8.3,   12.6, -16.0,
    //            0.0,   0.0,  1.0);

    // initializeCamera("perspective", 16.0);
    initializeCamera("perspective", 13.5);
    initializeFilm("gt_fox_" + transType,
                   // "fox_cylinder/gt_" + transType+ "_" + std::to_string(iter),
                   //"fox_rework/take_90_" + transType,
                   //"fox_take_77_rec_hyp",
                   1600,
                   900);

    initializeSampler("random", 25000);
    // initializeSampler("random", 4);
    initializeIntegrator(400000000,
                         // 40000000,
                         -1,
                         8,
                         "volpath_recursive",
                         // "vol_sppm",
                         "stream",
                         "independent",
                         false,
                         isGT);
    pbrtWorldBegin();

    initializeProceduralDensity();

    pbrtTransformBegin();

    initializeProceduralMedium("vol",
                               "heterogeneous",
                               "density",
                               transType,
                               "const",
                               "const",
                               "absorptive",
                               std::vector<Float>{1.0, 1.0, 1.0},
                               std::vector<Float>{0.0, 0.0, 0.0},
                               std::vector<Float>{-10.0, 4.0, -25.0},
                               std::vector<Float>{21.0, 21.0, -2.8},
                               std::vector<Float>{1.0, 1.0, 1.0},
                               1.1);
    pbrtTransformEnd();

    initializeWalls();
    initializeLightSources();

    pbrtAttributeBegin();

    pbrtScale(0.3, 0.3, 0.3);
    pbrtRotate(70.0, 0.0, 0.0, 1.0);
    pbrtTranslate(50.0, 0.0, -80.0);

    initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
                    std::vector<Float>{1.0, 1.0, 1.0},
                    1.5);

    // pbrtMaterial("glass", ParamSet());

    pbrtMediumInterface("vol", "");

    std::unique_ptr<std::string[]> filename(new std::string[1]);
    filename[0] = "fennec_fox_final.ply";

    ParamSet plymeshSet;
    plymeshSet.AddString("filename", std::move(filename), 1);

    pbrtShape("plymesh", plymeshSet);

    pbrtAttributeEnd();

    pbrtWorldEnd();

    pbrtCleanup();
}

void Fox_Scene::runEqualExtRenders(pbrt::Options options,
                                          std::string transType,
                                          bool isGT,
                                          double angle,
                                          double psi,
                                          int iter,
                                          Float majorant,
                                          int samples)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/fennec_fox/teapot.pbrt"));
    exp_path = TEST_SCENES_PATH "/fennec_fox/";

    double xpos = 65.0 / cos(3.141569 / 4.0) * cos(angle) + 8.0;
    double ypos = 65.0 / cos(3.141569 / 4.0) * sin(angle) + 12.0;
    double zpos = psi * (25.0 + 16.0) - 16.0;

    pbrtLookAt(xpos, ypos, zpos,
               5.5,   12.0, -15.5,
               0.0,   0.0,  1.0);

    initializeCamera("perspective", 13.5);
    initializeFilm("fox_figure/" + std::to_string(majorant) + "/" + transType,
                   1600,
                   900);

    initializeSampler("random", 10000);

    initializeIntegrator(400000000,
                         samples,
                         8,
                         "volpath_recursive",
                         "independent",
                         "independent",
                         false,
                         false);
    pbrtWorldBegin();

    initializeProceduralDensity();

    pbrtTransformBegin();

    initializeProceduralMedium("vol",
                               "heterogeneous",
                               "density",
                               transType,
                               "const",
                               "const",
                               "absorptive",
                               std::vector<Float>{1.0, 1.0, 1.0},
                               std::vector<Float>{0.0, 0.0, 0.0},
                               std::vector<Float>{-10.0, 4.0, -25.0},
                               std::vector<Float>{21.0, 21.0, -2.8},
                               std::vector<Float>{1.0, 1.0, 1.0},
                               majorant);
    pbrtTransformEnd();

    initializeWalls();
    initializeLightSources();

    pbrtAttributeBegin();

    pbrtScale(0.3, 0.3, 0.3);
    pbrtRotate(70.0, 0.0, 0.0, 1.0);
    pbrtTranslate(50.0, 0.0, -80.0);

    initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
                    std::vector<Float>{1.0, 1.0, 1.0},
                    1.5);

    pbrtMediumInterface("vol", "");

    std::unique_ptr<std::string[]> filename(new std::string[1]);
    filename[0] = "fennec_fox_final.ply";

    ParamSet plymeshSet;
    plymeshSet.AddString("filename", std::move(filename), 1);

    pbrtShape("plymesh", plymeshSet);

    pbrtAttributeEnd();

    pbrtWorldEnd();

    pbrtCleanup();
}

void Fox_Scene::runEqualSampleRenders(pbrt::Options options,
                                             std::string transType,
                                             bool isGT,
                                             double angle,
                                             double psi,
                                             int iter,
                                             Float majorant,
                                             int samples)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining("/Users/corneria/Documents/Research/testscenes/fennec_fox/teapot.pbrt"));
    exp_path = "/Users/corneria/Documents/Research/testscenes/fennec_fox/";

    double xpos = 65.0 / cos(3.141569 / 4.0) * cos(angle) + 8.0;
    double ypos = 65.0 / cos(3.141569 / 4.0) * sin(angle) + 12.0;
    double zpos = psi * (25.0 + 16.0) - 16.0;

    pbrtLookAt(xpos, ypos, zpos,
               5.5,   12.0, -15.5,
               0.0,   0.0,  1.0);

    initializeCamera("perspective", 13.5);
    initializeFilm("fox_figure_strat/" + std::to_string(majorant) + "_rand/" + transType+"_rand",
                   1600,
                   900);

    initializeSampler("random", samples);

    initializeIntegrator(400000000,
                         // 40000000,
                         -1,
                         8,
                         "volpath_recursive",
                         "independent",
                         "independent",
                         false,
                         false);
    pbrtWorldBegin();

    initializeProceduralDensity();

    pbrtTransformBegin();

    initializeProceduralMedium("vol",
                               "heterogeneous",
                               "density",
                               transType,
                               "const",
                               "const",
                               "absorptive",
                               std::vector<Float>{1.0, 1.0, 1.0},
                               std::vector<Float>{0.0, 0.0, 0.0},
                               std::vector<Float>{-10.0, 4.0, -25.0},
                               std::vector<Float>{21.0, 21.0, -2.8},
                               std::vector<Float>{1.0, 1.0, 1.0},
                               majorant);
    pbrtTransformEnd();

    initializeWalls();
    initializeLightSources();

    pbrtAttributeBegin();

    pbrtScale(0.3, 0.3, 0.3);
    pbrtRotate(70.0, 0.0, 0.0, 1.0);
    pbrtTranslate(50.0, 0.0, -80.0);

    initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
                    std::vector<Float>{1.0, 1.0, 1.0},
                    1.5);

    pbrtMediumInterface("vol", "");

    std::unique_ptr<std::string[]> filename(new std::string[1]);
    filename[0] = "fennec_fox_final.ply";

    ParamSet plymeshSet;
    plymeshSet.AddString("filename", std::move(filename), 1);

    pbrtShape("plymesh", plymeshSet);

    pbrtAttributeEnd();

    pbrtWorldEnd();

    pbrtCleanup();
}

void Fox_Scene::runEqualSampleStratifiedRenders(pbrt::Options options,
                                                       std::string transType,
                                                       bool isGT,
                                                       double angle,
                                                       double psi,
                                                       int iter,
                                                       Float majorant,
                                                       int samples)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining("/Users/corneria/Documents/Research/testscenes/fennec_fox/teapot.pbrt"));
    exp_path = "/Users/corneria/Documents/Research/testscenes/fennec_fox/";

    double xpos = 65.0 / cos(3.141569 / 4.0) * cos(angle) + 8.0;
    double ypos = 65.0 / cos(3.141569 / 4.0) * sin(angle) + 12.0;
    double zpos = psi * (25.0 + 16.0) - 16.0;

    pbrtLookAt(xpos, ypos, zpos,
               5.5,   12.0, -15.5,
               0.0,   0.0,  1.0);

    initializeCamera("perspective", 13.5);
    initializeFilm("fox_figure_strat/" + std::to_string(majorant) + "_strat/" + transType+"_strat",
                   1600,
                   900);

    initializeSampler("random", samples);

    initializeIntegrator(400000000,
                         // 40000000,
                         -1,
                         8,
                         "volpath_recursive",
                         "stream",
                         "independent",
                         false,
                         isGT);
    pbrtWorldBegin();

    initializeProceduralDensity();

    pbrtTransformBegin();

    initializeProceduralMedium("vol",
                               "heterogeneous",
                               "density",
                               transType,
                               "const",
                               "const",
                               "absorptive",
                               std::vector<Float>{1.0, 1.0, 1.0},
                               std::vector<Float>{0.0, 0.0, 0.0},
                               std::vector<Float>{-10.0, 4.0, -25.0},
                               std::vector<Float>{21.0, 21.0, -2.8},
                               std::vector<Float>{1.0, 1.0, 1.0},
                               majorant);
    pbrtTransformEnd();

    initializeWalls();
    initializeLightSources();

    pbrtAttributeBegin();

    pbrtScale(0.3, 0.3, 0.3);
    pbrtRotate(70.0, 0.0, 0.0, 1.0);
    pbrtTranslate(50.0, 0.0, -80.0);

    initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
                    std::vector<Float>{1.0, 1.0, 1.0},
                    1.5);

    pbrtMediumInterface("vol", "");

    std::unique_ptr<std::string[]> filename(new std::string[1]);
    filename[0] = "fennec_fox_final.ply";

    ParamSet plymeshSet;
    plymeshSet.AddString("filename", std::move(filename), 1);

    pbrtShape("plymesh", plymeshSet);

    pbrtAttributeEnd();

    pbrtWorldEnd();

    pbrtCleanup();
}

void Fox_Scene::runTest(std::string transType, bool isGT)
{
    SetSearchDirectory(DirectoryContaining(TEST_SCENES_PATH "/fennec_fox/teapot.pbrt"));
    exp_path = TEST_SCENES_PATH "/fennec_fox/";

    pbrtLookAt(65.0, 65.0, 15.0,
               8.3,   12.6, -16.0,
               0.0,   0.0,  1.0);

    initializeCamera("perspective", 13.5);
    initializeFilm("fox_figure/" + transType,
                   //"fox_figure_rotate/" + transType + "_" + std::to_string(iter),
                   //"fox_rework/take_90_" + transType,
                   //"fox_take_77_rec_hyp",
                   1600,
                   900);

    initializeSampler("random", 5000);
    // initializeSampler("random", 16);
    initializeIntegrator(400000000,
                         // 30000000,
                         50000000,
                         // -1,
                         8,
                         "volpath_recursive",
                         // "vol_sppm",
                         "independent",
                         "independent",
                         false,
                         isGT);
    pbrtWorldBegin();

    initializeProceduralDensity();

    pbrtTransformBegin();

    initializeProceduralMedium("vol",
                               "heterogeneous",
                               "density",
                               transType,
                               "const",
                               "const",
                               "absorptive",
                               std::vector<Float>{0.8, 0.8, 0.8},
                               std::vector<Float>{0.0, 0.0, 0.0},
                               std::vector<Float>{-10.0, 4.0, -25.0},
                               std::vector<Float>{21.0, 21.0, -2.8},
                               std::vector<Float>{1.0, 1.0, 1.0},
                               1.1);
    pbrtTransformEnd();

    initializeWalls();

    // pbrtAttributeBegin();

    // pbrtAttributeBegin();
    // initializeDiffuseAreaLightSource(std::vector<Float>{40.0, 40.0, 40.0});
    // // pbrtAreaLightSource("diffuse");
    // // AreaLightSource "diffuse" "rgb L" [ .5 .5 .5 ]
    // pbrtTranslate(0, 10, 5.0);
    // initializeSphereShape(4.0);
    // // pbrtShape("sphere", ParamSet())
    // pbrtAttributeEnd();

    // pbrtTranslate(200.0, 100.0, 4.0);
    // initializePointLightSource(std::vector<Float>{80000.0, 80000.0, 80000.0});
    //
    // // pbrtTranslate(0.0, 10.0, 100.0);
    // // initializePointLightSource(std::vector<Float>{20000.0, 20000.0, 20000.0});
    //
    // // pbrtTranslate(0.0, 10.0, 5.0);
    // // initializePointLightSource(std::vector<Float>{5000.0, 5000.0, 5000.0});
    //
    // // initializeInfiniteLightSource("textures/white.png", std::vector<Float>{0.05, 0.05, 0.05});
    //
    // pbrtAttributeEnd();
    //
    // pbrtAttributeBegin();
    //
    // pbrtTranslate(0.0, 100.0, 4.0);
    // initializePointLightSource(std::vector<Float>{17000.0, 17000.0, 17000.0});
    //
    // pbrtAttributeEnd();
    //
    // pbrtAttributeBegin();
    //
    // pbrtTranslate(0.0, -100.0, 4.0);
    // initializePointLightSource(std::vector<Float>{20000.0, 20000.0, 20000.0});
    //
    // pbrtAttributeEnd();
    //
    // pbrtAttributeBegin();
    //
    // pbrtTranslate(-100.0, -100.0, 4.0);
    // initializePointLightSource(std::vector<Float>{60000.0, 60000.0, 60000.0});
    //
    // pbrtAttributeEnd();
    //
    // pbrtAttributeBegin();
    //
    // pbrtTranslate(100.0, 100.0, 4.0);
    // initializePointLightSource(std::vector<Float>{40000.0, 40000.0, 40000.0});
    //
    // pbrtAttributeEnd();

    pbrtAttributeBegin();

    pbrtTranslate(60.0, 60.0, -15.0);
    initializePointLightSource(std::vector<Float>{60000.0, 60000.0, 60000.0});
    // initializePointLightSource(std::vector<Float>{50000.0, 50000.0, 50000.0});

    pbrtAttributeEnd();

    pbrtAttributeBegin();

    pbrtTranslate(0.0, -130.0, -15.0);
    // initializePointLightSource(std::vector<Float>{84000.0, 84000.0, 84000.0});
    initializePointLightSource(std::vector<Float>{84000.0 * 20.0 / 8.0, 42000.0 * 20.0 / 8.0, 0.0});

    pbrtAttributeEnd();

    pbrtAttributeBegin();

    pbrtTranslate(-130.0, 0.0, -15.0);
    // initializePointLightSource(std::vector<Float>{84000.0, 84000.0, 84000.0});
    initializePointLightSource(std::vector<Float>{0.0, 42000.0 * 20.0 / 8.0, 84000.0 * 20.0 / 8.0});

    pbrtAttributeEnd();

    pbrtAttributeBegin();

    pbrtScale(0.3, 0.3, 0.3);
    pbrtRotate(70.0, 0.0, 0.0, 1.0);
    pbrtTranslate(50.0, 0.0, -80.0);

    initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
                    std::vector<Float>{1.0, 1.0, 1.0},
                    1.5);

    // pbrtMaterial("glass", ParamSet());

    pbrtMediumInterface("vol", "");

    std::unique_ptr<std::string[]> filename(new std::string[1]);
    filename[0] = "fennec_fox_final.ply";

    ParamSet plymeshSet;
    plymeshSet.AddString("filename", std::move(filename), 1);

    pbrtShape("plymesh", plymeshSet);

    pbrtAttributeEnd();

    pbrtWorldEnd();
}

void Fox_Scene::initializeLightSources()
{
    double dist = 150.0;
    double power = 10000.0 * 1.08; // white balenced
    // double power = 10000.0; // reg
    double height = 50.0;
    double phase = 0.0;
    double index = 0.0;
    double max = 10.0;

    double x_one = dist * cos(6.28 * index / max + phase);
    double y_one = dist * sin(6.28 * index / max + phase);
    index += 1.0;

    double x_two = dist * cos(6.28 * index / max + phase);
    double y_two = dist * sin(6.28 * index / max + phase);
    index += 1.0;

    double x_three = dist * cos(6.28 * index / max + phase);
    double y_three = dist * sin(6.28 * index / max + phase);
    index += 1.0;

    double x_four = dist * cos(6.28 * index / max + phase);
    double y_four = dist * sin(6.28 * index / max + phase);
    index += 1.0;

    double x_five = dist * cos(6.28 * index / max + phase);
    double y_five = dist * sin(6.28 * index / max + phase);
    index += 1.0;

    double x_six = dist * cos(6.28 * index / max + phase);
    double y_six = dist * sin(6.28 * index / max + phase);
    index += 1.0;

    double x_seven = dist * cos(6.28 * index / max + phase);
    double y_seven = dist * sin(6.28 * index / max + phase);
    index += 1.0;

    double x_eight = dist * cos(6.28 * index / max + phase);
    double y_eight = dist * sin(6.28 * index / max + phase);
    index += 1.0;

    double x_nine = dist * cos(6.28 * index / max + phase);
    double y_nine = dist * sin(6.28 * index / max + phase);
    index += 1.0;

    double x_ten = dist * cos(6.28 * index / max + phase);
    double y_ten = dist * sin(6.28 * index / max + phase);
    index += 1.0;

    pbrtAttributeBegin();
    pbrtTranslate(x_one, y_one, height + 0.0 * cos(x_one));
    initializePointLightSource(std::vector<Float>{power, power, power});
    pbrtAttributeEnd();

    pbrtAttributeBegin();
    pbrtTranslate(x_two, y_two, height + 0.0 * cos(x_two));
    initializePointLightSource(std::vector<Float>{power, power, power});
    pbrtAttributeEnd();

    pbrtAttributeBegin();
    pbrtTranslate(x_three, y_three, height + 0.0 * cos(x_three));
    initializePointLightSource(std::vector<Float>{power, power, power});
    pbrtAttributeEnd();

    pbrtAttributeBegin();
    pbrtTranslate(x_four, y_four, height + 0.0 * cos(x_four));
    initializePointLightSource(std::vector<Float>{power, power, power});
    pbrtAttributeEnd();

    pbrtAttributeBegin();
    pbrtTranslate(x_five, y_five, height + 0.0 * cos(x_five));
    initializePointLightSource(std::vector<Float>{power, power, power});
    pbrtAttributeEnd();

    pbrtAttributeBegin();
    pbrtTranslate(x_six, y_six, height + 0.0 * cos(x_six));
    initializePointLightSource(std::vector<Float>{power, power, power});
    pbrtAttributeEnd();

    pbrtAttributeBegin();
    pbrtTranslate(x_seven, y_seven, height + 0.0 * cos(x_seven));
    initializePointLightSource(std::vector<Float>{power, power, power});
    pbrtAttributeEnd();

    pbrtAttributeBegin();
    pbrtTranslate(x_eight, y_eight, height + 0.0 * cos(x_eight));
    initializePointLightSource(std::vector<Float>{power, power, power});
    pbrtAttributeEnd();

    pbrtAttributeBegin();
    pbrtTranslate(x_nine, y_nine, height + 0.0 * cos(x_nine));
    initializePointLightSource(std::vector<Float>{power, power, power});
    pbrtAttributeEnd();

    pbrtAttributeBegin();
    pbrtTranslate(x_ten, y_ten, height + 0.0 * cos(x_ten));
    initializePointLightSource(std::vector<Float>{power, power, power});
    pbrtAttributeEnd();
}


void Fox_Scene::initializeProceduralDensity()
{
    // initializeVoronoiSpiralTexture("density",
    //                                std::vector<Float>{0.4, 0.8, 0.8,
    //                                                   0.2, 0.2, 0.2,
    //                                                   0.1, 0.5, 0.95},
    //                                std::vector<Float>{0.3, 0.3, 0.3},
    //                                std::vector<Float>{0.0, 6.28 / 3.0, 6.28 * 2.0 / 3.0},
    //                                std::vector<Float>{2.0, 2.0, 2.0},
    //                                std::vector<Float>{0.967742, 0.967742, 0.967742},
    //                                std::vector<Float>{0.26, 0.26, 0.26},
    //                                std::vector<Float>{-10.0, 4.0, -25.0},
    //                                std::vector<Float>{21.0, 21.0, -2.8},
    //                                0.25,
    //                                36);

    // initializeVoronoiSpiralTexture("density",
    //                                std::vector<Float>{0.5, 0.95, 0.95,
    //                                                   // 0.3, 0.3, 0.3,
    //                                                   0.1, 0.8, 0.9,
    //                                                   0.3, 1.0, 1.0,
    //                                                   0.05, 0.4, 0.4,
    //                                                   0.2, 0.6, 1.0},
    //                                std::vector<Float>{0.4, 0.1, 0.1, 0.1, 0.3},
    //                                // std::vector<Float>{0.0, 6.28 / 3.0, 6.28 * 2.0 / 3.0},
    //                                std::vector<Float>{0.0,
    //                                                   6.28 / 5.0,
    //                                                   2.0 * 6.28 / 5.0,
    //                                                   3.0 * 6.28 / 5.0,
    //                                                   4.0 * 6.28 / 5.0},
    //                                std::vector<Float>{2.0, 2.0, 2.0, 2.0, 2.0},
    //                                std::vector<Float>{0.967742, 0.967742, 0.967742},
    //                                std::vector<Float>{0.05, 0.05, 0.05},
    //                                std::vector<Float>{-10.0, 4.0, -25.0},
    //                                std::vector<Float>{21.0, 21.0, -2.8},
    //                                0.25,
    //                                36);


    // initializeVoronoiSpiralTexture("density",
    //                                std::vector<Float>{0.5, 0.95, 0.95,
    //                                                   // 0.3, 0.3, 0.3,
    //                                                   0.1, 0.3, 0.9,
    //                                                   0.3, 0.95, 0.95,
    //                                                   0.05, 0.4, 0.4,
    //                                                   0.2, 0.6, 1.0},
    //                                std::vector<Float>{0.4, 0.1, 0.1, 0.1, 0.3},
    //                                // std::vector<Float>{0.0, 6.28 / 3.0, 6.28 * 2.0 / 3.0},
    //                                std::vector<Float>{0.67,
    //                                                   6.28 / 5.0,
    //                                                   2.5 * 6.28 / 5.0,
    //                                                   3.7 * 6.28 / 5.0,
    //                                                   4.2 * 6.28 / 5.0},
    //                                std::vector<Float>{2.0, 2.0, 1.0, 3.0, 2.0},
    //                                std::vector<Float>{0.254, 4.967742, 2.63501},
    //                                std::vector<Float>{0.35, 0.05, 0.15},
    //                                std::vector<Float>{-10.0, 4.0, -25.0},
    //                                std::vector<Float>{21.0, 21.0, -2.8},
    //                                0.25,
    //                                36);

    initializeVoronoiSpiralTexture("density",
                                   std::vector<Float>{0.5, 0.95, 0.95,
                                                      // 0.3, 0.3, 0.3,
                                                      0.1, 0.3, 0.9,
                                                      0.3, 0.3, 0.3,
                                                      // 0.3, 0.95, 0.95,
                                                      0.7, 0.7, 0.1,
                                                      0.05, 0.4, 0.4,
                                                      0.2, 0.6, 1.0},
                                   std::vector<Float>{0.5, 0.1, 0.13, 0.18, 0.1, 0.5},
                                   // std::vector<Float>{0.0, 6.28 / 3.0, 6.28 * 2.0 / 3.0},
                                   std::vector<Float>{0.67,
                                                      6.28 / 5.0,
                                                      2.5 * 6.28 / 5.0,
                                                      4.98,
                                                      3.7 * 6.28 / 5.0,
                                                      4.2 * 6.28 / 5.0},
                                   // std::vector<Float>{2.0, 2.0, 1.0, 1.0, 1.0, 2.0},
                                   std::vector<Float>{0.97, 3.0, 1.96, 4.0, 2.1, 0.35},
                                   std::vector<Float>{0.254, 4.967742, 2.63501},
                                   std::vector<Float>{0.35, 0.05, 0.15},
                                   std::vector<Float>{-10.0, 4.0, -25.0},
                                   std::vector<Float>{21.0, 21.0, -2.8},
                                   0.25,
                                   36);
}

void Fox_Scene::initializeTest()
{
    pbrtAttributeBegin();

    initializeMaterial_Matte(std::vector<Float>{0.8, 0.3, 0.2});

    pbrtTranslate(8.0, 12.0, 5.0);

    std::unique_ptr<std::string[]> filename(new std::string[1]);
    filename[0] = "square.ply";

    ParamSet mediumShapeSet;
    mediumShapeSet.AddString("filename", std::move(filename), 1);

    pbrtShape("plymesh", mediumShapeSet);

    pbrtAttributeEnd();
}

void Fox_Scene::initializeWalls()
{
    pbrtAttributeBegin();

    initializeMaterial_Matte(std::vector<Float>{1.0, 1.0, 1.0});

    // pbrtMaterial("matte", ParamSet());

    // initializeMaterial_ReflectiveMatte(std::vector<Float>{0.9, 0.9, 0.9},
    //                                    std::vector<Float>{1.0, 1.0, 1.0});

    // initializeTextureImg("grid",
    //                      "color",
    //                      "imagemap",
    //                      "textures/lines.png");
    //
    // initializeScaleTexture("sgrid",
    //                        "color",
    //                        "scale",
    //                        "grid",
    //                        std::vector<Float>{0.80, 0.80, 0.80});
    //
    // initializeMaterial_Matte("sgrid");
    // pbrtMaterial("matte", ParamSet());

    Float wf = 260;
    Float top = 500;
    Float bot = -23.8;

    // floor
    initializeTrimesh(std::vector<int>{0, 1, 2, 2, 3, 0},
                      std::vector<Float>{0, 0, 5, 0, 5, 5, 0, 5},
                      std::vector<Float>{-wf, -wf, bot,
                                         wf, -wf, bot,
                                         wf, wf, bot,
                                         -wf, wf, bot});

    pbrtAttributeEnd();
    pbrtAttributeBegin();

    // pbrtMaterial("matte", ParamSet());
    initializeMaterial_Matte(std::vector<Float>{1.0, 1.0, 1.0});

    // ceiling
    initializeTrimesh(std::vector<int>{0, 1, 2, 2, 3, 0},
                     std::vector<Float>{0, 0, 5, 0, 5, 5, 0, 5},
                     std::vector<Float>{-wf, -wf, top,
                                        wf, -wf, top,
                                        wf, wf, top,
                                        -wf, wf, top});

    // --. +-. ++, -+

    // left wall
    initializeTrimesh(std::vector<int>{0, 1, 2, 2, 3, 0},
                     std::vector<Float>{0, 0, 5, 0, 5, 5, 0, 5},
                     std::vector<Float>{-wf, -wf, bot,
                                        -wf, wf, bot,
                                        -wf, wf, top,
                                        -wf, -wf, top});

    // right wall
    initializeTrimesh(std::vector<int>{0, 1, 2, 2, 3, 0},
                     std::vector<Float>{0, 0, 5, 0, 5, 5, 0, 5},
                     std::vector<Float>{wf, -wf, bot,
                                        wf, wf, bot,
                                        wf, wf, top,
                                        wf, -wf, top});

    // back wall
    initializeTrimesh(std::vector<int>{0, 1, 2, 2, 3, 0},
                     std::vector<Float>{0, 0, 5, 0, 5, 5, 0, 5},
                     std::vector<Float>{-wf, -wf, bot,
                                        wf, -wf, bot,
                                        wf, -wf, top,
                                        -wf, -wf, top});

    // forward wall
    initializeTrimesh(std::vector<int>{0, 1, 2, 2, 3, 0},
                     std::vector<Float>{0, 0, 5, 0, 5, 5, 0, 5},
                     std::vector<Float>{-wf, wf, bot,
                                        wf, wf, bot,
                                        wf, wf, top,
                                        -wf, wf, top});

    pbrtAttributeEnd();

    // pbrtAttributeBegin();
    //
    // initializeGlass(std::vector<Float>{0.0, 0.0, 0.0},
    //                 std::vector<Float>{1.0, 1.0, 1.0},
    //                 1.0);
    //
    // initializeTrimesh(std::vector<int>{0, 1, 2, 2, 3, 0},
    //                   std::vector<Float>{0, 0, 5, 0, 5, 5, 0, 5},
    //                   // std::vector<Float>{-400, -400, -24, 400, -400, -24, 400, 400, -24, -400, 400, -24});
    //                   std::vector<Float>{-1500, -1500, -24, 1500, -1500, -24, 1500, 1500, -24, -1500, 1500, -24});
    //
    // pbrtAttributeEnd();
}
