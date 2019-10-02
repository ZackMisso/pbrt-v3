#include "teaser.h"

Teaser::Teaser(pbrt::Options options)
{
    // runTest(options, "ratio", true);
    runTest(options, "ratio", false);
    runTest(options, "next_flight_ratio", false);
    runTest(options, "pseries_cumulative", false);
    runTest(options, "pseries_cdf", false);
}

void Teaser::runTest(pbrt::Options options, std::string transType, bool is_gt)
{
    pbrtInit(options);

    SetSearchDirectory(DirectoryContaining("/Users/corneria/Documents/Research/testscenes/chess/dragon_10.pbrt"));
    exp_path = "/Users/corneria/Documents/Research/testscenes/chess/";

    initializeIntegrator(200000000,
                         3400000000,
                         // -1,
                         8,
                         "volpath_recursive",
                         // "bdpt",
                         "independent",
                         "independent",
                         false,
                         is_gt);

    initializeSampler("random", 1000);

    initializePixelFilter("box");

    std::string name = transType;
    if (is_gt) name = "gt_" + name;

    initializeFilm(name,
                   2400,
                   1200);

    pbrtLookAt(-40.0, -40.0, 80.0,
               52.0, 52.0, 6.0,
               0.0, 0.0, 1.0);

    initializeCamera("perspective", 16.3);

    pbrtWorldBegin();

    initializeWorld(transType, 1.5);
    initializePawn_One(transType, 1.5);
    initializePawn_Two(transType, 1.5);
    initializePawn_Four(transType, 1.5);
    initializePawn_Five(transType, 1.5);
    initializeKnight_Two(transType, 1.5);
    initializeBishop_One(transType, 1.5);
    initializeBishop_Two(transType, 1.5);
    initializeQueen(transType, 1.5);
    initializeKing(transType, 1.5);

    pbrtWorldEnd();

    pbrtCleanup();
}

void Teaser::initializeWorld(std::string transType, Float majScale)
{
    pbrtAttributeBegin();
    // pbrtRotate(60.0, 0.0, 1.0, 0.0);
    // pbrtRotate(180.0, 0.0, 0.0, 1.0);
    initializeInfiniteLightSource(//"textures/skylight-morn_full.exr",
                                  //"textures/noon_grass_2k.exr",
                                  // "textures/white.png",
                                  "textures/horizon.png",
                                  //std::vector<Float>{2.3, 2.3, 2.3});
                                  std::vector<Float>{2.0, 2.0, 2.0});
    pbrtAttributeEnd();

    // base board
    pbrtAttributeBegin();

    initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
                    std::vector<Float>{0.5, 0.5, 0.5},
                    1.5);

    initializeTrimesh(std::vector<int>{0, 1, 2, 2, 3, 0},
                      std::vector<Float>{-1000.0, -1000.0, -1.1,
                                         1000.0, -1000.0, -1.1,
                                         1000.0, 1000.0, -1.1,
                                         -1000.0, 1000.0, -1.1});
    pbrtAttributeEnd();

    double startX = 0.0;
    double startY = 0.0;
    double sizeX = 15.0;
    double sizeY = 15.0;

    Float min_z = -1.0;
    Float max_z = 0.0;

    std::string base_path = "/Users/corneria/Documents/Research/testscenes/chess/textures/generated_2/";

    for (int i = 0; i < 12; ++i)
    {
        Float min_x = startX;
        Float max_x = startX + 11.0 * sizeX;

        Float min_y = startY + Float(i) * sizeY - 0.1;
        Float max_y = startY + Float(i) * sizeY + 0.1;

        pbrtAttributeBegin();

        initializeGlass(std::vector<Float>{0.1, 0.1, 0.1},
                        std::vector<Float>{0.0, 0.0, 0.0},
                        1.5);

        initializeBoxShape(min_x, max_x,
                           min_y, max_y,
                           min_z, max_z + 0.1);

        pbrtAttributeEnd();
    }

    for (int i = 0; i < 12; ++i)
    {
        Float min_y = startY;
        Float max_y = startY + 11.0 * sizeY;

        Float min_x = startX + Float(i) * sizeX - 0.1;
        Float max_x = startX + Float(i) * sizeX + 0.1;

        pbrtAttributeBegin();

        initializeGlass(std::vector<Float>{0.1, 0.1, 0.1},
                        std::vector<Float>{0.0, 0.0, 0.0},
                        1.5);

        initializeBoxShape(min_x, max_x,
                           min_y, max_y,
                           min_z, max_z + 0.1);

        pbrtAttributeEnd();
    }

    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; ++j)
        {
            Float min_x = (startX)+(j*sizeX);
            Float min_y = (startY)+(i*sizeY);
            Float max_x = (startX)+sizeX*(j+1);
            Float max_y = (startY)+sizeY*(i+1);

            std::string name = "board_"+std::to_string(j)+"_"+std::to_string(i);

            pbrtAttributeBegin();

            initializeDeintegratedTextureMedium(name,
                                                base_path + name + ".hdr",
                                                std::vector<Float>{min_x, min_y, min_z},
                                                std::vector<Float>{max_x, max_y, max_z},
                                                true);

            Float sigma_a_light = 2.0;
            Float sigma_a_dark = 4.0;

            Float sigma_a = 0.0;

            if ((i+j)%2 == 0)
            {
                sigma_a = sigma_a_dark;
            }
            else
            {
                sigma_a = sigma_a_light;
            }

            initializeProceduralMedium(name + "_vol",
                                       "heterogeneous",
                                       name,
                                       transType,
                                       "const",
                                       "const",
                                       "absorptive",
                                       std::vector<Float>{sigma_a, sigma_a, sigma_a},
                                       std::vector<Float>{0.0, 0.0, 0.0},
                                       std::vector<Float>{min_x, min_y, min_z},
                                       std::vector<Float>{max_x, max_y, max_z},
                                       std::vector<Float>{1.0, 1.0, 1.0},
                                       majScale);

            initializeGlass(name,
                            1.5);

            pbrtMediumInterface(name + "_vol", "");

            initializeBoxShape(min_x, max_x,
                               min_y, max_y,
                               min_z, max_z);

            pbrtAttributeEnd();
        }
    }
}

void Teaser::initializePawn_One(std::string transType, Float majScale)
{
    Float i = 2.0;
    Float j = 4.0;
    double startX = 0.0;
    double startY = 0.0;
    double sizeX = 15.0;
    double sizeY = 15.0;
    std::string base_path = "/Users/corneria/Documents/Research/testscenes/chess/textures/generated_2/";

    // initializeDeintegratedTextureMedium("density",
    //                                     base_path + "mesh_1.hdr",
    //                                     std::vector<Float>{63.0, 33.0, 0.0},
    //                                     std::vector<Float>{72.0, 42.0, 16.0});

    initializeChessTextureMedium("density",
                                 base_path + "mesh_1.hdr",
                                 std::vector<Float>{63.0, 33.0, 0.0},
                                 std::vector<Float>{72.0, 42.0, 16.0},
                                 // 0.316556 + 0.33, // hue
                                 0.385,
                                 // 0.689743 - 0.2, // sat
                                 1.0,
                                 4096.0 / 5.0, // turb_period
                                 5.0, // xtrans
                                 5.0, // ytrans
                                 1.0, // ztrans
                                 1.0, // g_const,
                                 6.5, // x_const,
                                 4.0, // t_const
                                 0.0, // phase
                                 6.5); // power

    pbrtTransformBegin();

    initializeProceduralMedium("pawn_one_vol",
                               "heterogeneous",
                               "density",
                               transType,
                               "const",
                               "const",
                               "absorptive",
                               std::vector<Float>{1.0, 1.0, 1.0},
                               std::vector<Float>{0.0, 0.0, 0.0},
                               std::vector<Float>{63.0, 33.0, 0.0},
                               std::vector<Float>{72.0, 42.0, 16.0},
                               std::vector<Float>{1.0, 1.0, 1.0},
                               majScale);
    pbrtTransformEnd();

    pbrtAttributeBegin();
    pbrtTranslate((j+0.5) * sizeX, (i+0.5) * sizeY, 0.0);
    pbrtScale(0.2, 0.2, 0.2);

    initializeGlass("density",
                    1.5);

    pbrtMediumInterface("pawn_one_vol", "");
    initializePlyShape("pawn_centered_final.ply");

    pbrtAttributeEnd();
}

void Teaser::initializePawn_Two(std::string transType, Float majScale)
{
    std::string base_path = "/Users/corneria/Documents/Research/testscenes/chess/textures/generated_2/";

    Float i = 3.0;
    Float j = 6.0;
    double startX = 0.0;
    double startY = 0.0;
    double sizeX = 15.0;
    double sizeY = 15.0;

    // Float i = 5.0;
    // Float j = 6.0;
    // double startX = 0.0;
    // double startY = 0.0;
    // double sizeX = 15.0;
    // double sizeY = 15.0;

    // initializeDeintegratedTextureMedium("pawn_two",
    //                                     base_path + "mesh_2.hdr",
    //                                     std::vector<Float>{93.0, 48.0, 0.0},
    //                                     std::vector<Float>{102.0, 57.0, 16.0});

    initializeChessTextureMedium("pawn_two",
                                 base_path + "mesh_2.hdr",
                                 std::vector<Float>{91.5, 46.5, 0.0},
                                 std::vector<Float>{100.5, 55.5, 16.0},
                                 // 0.363102 + 0.33, // hue
                                 0.385,
                                 // 0.713461 - 0.2, // sat
                                 1.0,
                                 4096.0 / 6.5, // turb_period
                                 100.0, // xtrans
                                 150.0, // ytrans
                                 100.0, // ztrans
                                 1.0, // g_const,
                                 4.5, // x_const,
                                 4.0, // t_const
                                 1.0, // phase
                                 4.0); // power

    pbrtTransformBegin();

    initializeProceduralMedium("pawn_two_vol",
                               "heterogeneous",
                               "pawn_two",
                               transType,
                               "const",
                               "const",
                               "absorptive",
                               std::vector<Float>{1.0, 1.0, 1.0},
                               std::vector<Float>{0.0, 0.0, 0.0},
                               std::vector<Float>{91.5, 46.5, 0.0},
                               std::vector<Float>{100.5, 55.5, 16.0},
                               std::vector<Float>{1.0, 1.0, 1.0},
                               majScale);
    pbrtTransformEnd();

    pbrtAttributeBegin();
    pbrtTranslate((j+0.5) * sizeX - 1.5, (i+0.5) * sizeY - 1.5, 0.0);
    pbrtScale(0.2, 0.2, 0.2);

    initializeGlass("pawn_two",
                    1.5);

    pbrtMediumInterface("pawn_two_vol", "");
    initializePlyShape("pawn_centered_final.ply");

    pbrtAttributeEnd();
}

void Teaser::initializePawn_Four(std::string transType, Float majScale)
{
    std::string base_path = "/Users/corneria/Documents/Research/testscenes/chess/textures/generated_2/";

    Float i = 4.0;
    Float j = 2.0;
    double startX = 0.0;
    double startY = 0.0;
    double sizeX = 15.0;
    double sizeY = 15.0;

    // initializeDeintegratedTextureMedium("pawn_four",
    //                                     base_path + "mesh_4.hdr",
    //                                     std::vector<Float>{33.0, 63.0, 0.0},
    //                                     std::vector<Float>{42.0, 72.0, 16.0});

    initializeChessTextureMedium("pawn_four",
                                 base_path + "mesh_4.hdr",
                                 std::vector<Float>{33.0, 63.0, 0.0},
                                 std::vector<Float>{42.0, 72.0, 16.0},
                                 // 0.310295 + 0.33, // hue
                                 0.385,
                                 // 0.672591 - 0.2, // sat
                                 1.0,
                                 4096.0 / 5.0, // turb_period
                                 0.0, // xtrans
                                 0.0, // ytrans
                                 0.0, // ztrans
                                 1.0, // g_const,
                                 4.5, // x_const,
                                 7.0, // t_const
                                 1.0, // phase
                                 4.0); // power

    pbrtTransformBegin();

    initializeProceduralMedium("pawn_four_vol",
                               "heterogeneous",
                               "pawn_four",
                               transType,
                               "const",
                               "const",
                               "absorptive",
                               std::vector<Float>{1.0, 1.0, 1.0},
                               std::vector<Float>{0.0, 0.0, 0.0},
                               std::vector<Float>{33.0, 63.0, 0.0},
                               std::vector<Float>{42.0, 72.0, 16.0},
                               std::vector<Float>{1.0, 1.0, 1.0},
                               majScale);
    pbrtTransformEnd();

    pbrtAttributeBegin();
    pbrtTranslate((j+0.5) * sizeX, (i+0.5) * sizeY, 0.0);
    pbrtScale(0.2, 0.2, 0.2);

    initializeGlass("pawn_four",
                    1.5);

    // initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
    //                 std::vector<Float>{1.0, 1.0, 1.0},
    //                 1.5);

    pbrtMediumInterface("pawn_four_vol", "");
    initializePlyShape("pawn_centered_final.ply");

    pbrtAttributeEnd();
}

void Teaser::initializePawn_Five(std::string transType, Float majScale)
{
    std::string base_path = "/Users/corneria/Documents/Research/testscenes/chess/textures/generated_2/";

    Float i = 6.0;
    Float j = 3.0;
    double startX = 0.0;
    double startY = 0.0;
    double sizeX = 15.0;
    double sizeY = 15.0;

    // initializeDeintegratedTextureMedium("pawn_five",
    //                                     base_path + "mesh_5.hdr",
    //                                     std::vector<Float>{48.0, 93.0, 0.0},
    //                                     std::vector<Float>{57.0, 102.0, 16.0});

    initializeChessTextureMedium("pawn_five",
                                 base_path + "mesh_5.hdr",
                                 std::vector<Float>{46.5, 91.5, 0.0},
                                 std::vector<Float>{55.5, 100.5, 16.0},
                                 // 0.314673 + 0.33, // hue
                                 0.385,
                                 // 0.73849 - 0.2, // sat
                                 1.0,
                                 4096.0 / 5.0, // turb_period
                                 0.0, // xtrans
                                 0.0, // ytrans
                                 0.0, // ztrans
                                 1.0, // g_const,
                                 4.5, // x_const,
                                 7.0, // t_const
                                 1.0, // phase
                                 4.0); // power

    pbrtTransformBegin();

    initializeProceduralMedium("pawn_five_vol",
                               "heterogeneous",
                               "pawn_five",
                               transType,
                               "const",
                               "const",
                               "absorptive",
                               std::vector<Float>{1.0, 1.0, 1.0},
                               std::vector<Float>{0.0, 0.0, 0.0},
                               std::vector<Float>{46.5, 91.5, 0.0},
                               std::vector<Float>{55.5, 100.5, 16.0},
                               std::vector<Float>{1.0, 1.0, 1.0},
                               majScale);
    pbrtTransformEnd();

    pbrtAttributeBegin();
    pbrtTranslate((j+0.5) * sizeX - 1.5, (i+0.5) * sizeY - 1.5, 0.0);
    pbrtScale(0.2, 0.2, 0.2);

    initializeGlass("pawn_five",
                    1.5);

    // initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
    //                 std::vector<Float>{1.0, 1.0, 1.0},
    //                 1.5);

    pbrtMediumInterface("pawn_five_vol", "");
    initializePlyShape("pawn_centered_final.ply");

    pbrtAttributeEnd();
}

void Teaser::initializeKnight_Two(std::string transType, Float majScale)
{
    std::string base_path = "/Users/corneria/Documents/Research/testscenes/chess/textures/generated_2/";

    Float i = 1.0;
    Float j = 5.0;
    double startX = 0.0;
    double startY = 0.0;
    double sizeX = 15.0;
    double sizeY = 15.0;

    // initializeDeintegratedTextureMedium("knight_two",
    //                                     base_path + "mesh_12.hdr",
    //                                     std::vector<Float>{77.0, 18.0, 0.0},
    //                                     std::vector<Float>{89.0, 27.0, 22.0});

    initializeChessTextureMedium("knight_two",
                                 base_path + "mesh_12.hdr",
                                 std::vector<Float>{77.0, 18.0, 0.0},
                                 std::vector<Float>{89.0, 27.0, 22.0},
                                 // 0.386486 + 0.33, // hue
                                 0.385,
                                 // 0.835403 - 0.2, // sat
                                 1.0,
                                 4096.0 / 5.0, // turb_period
                                 0.0, // xtrans
                                 0.0, // ytrans
                                 0.0, // ztrans
                                 1.0, // g_const,
                                 4.5, // x_const,
                                 7.0, // t_const
                                 1.0, // phase
                                 4.0); // power

    pbrtTransformBegin();

    initializeProceduralMedium("knight_two_vol",
                               "heterogeneous",
                               "knight_two",
                               transType,
                               "const",
                               "const",
                               "absorptive",
                               std::vector<Float>{1.0, 1.0, 1.0},
                               std::vector<Float>{0.0, 0.0, 0.0},
                               std::vector<Float>{77.0, 18.0, 0.0},
                               std::vector<Float>{89.0, 27.0, 22.0},
                               std::vector<Float>{1.0, 1.0, 1.0},
                               majScale);
    pbrtTransformEnd();

    pbrtAttributeBegin();
    pbrtTranslate((j+0.5) * sizeX, (i+0.5) * sizeY, 0.0);
    pbrtScale(0.2, 0.2, 0.2);


    initializeGlass("knight_two",
                    1.5);

    // initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
    //                 std::vector<Float>{1.0, 1.0, 1.0},
    //                 1.5);

    pbrtMediumInterface("knight_two_vol", "");
    initializePlyShape("knight_centered_final.ply");

    pbrtAttributeEnd();
}

void Teaser::initializeBishop_One(std::string transType, Float majScale)
{
    std::string base_path = "/Users/corneria/Documents/Research/testscenes/chess/textures/generated_2/";

    Float i = 4.0;
    Float j = 3.0;
    double startX = 0.0;
    double startY = 0.0;
    double sizeX = 15.0;
    double sizeY = 15.0;

    // initializeDeintegratedTextureMedium("bishop_one",
    //                                     base_path + "mesh_8.hdr",
    //                                     std::vector<Float>{47.0, 62.0, 0.0},
    //                                     std::vector<Float>{58.0, 73.0, 23.0});

    initializeChessTextureMedium("bishop_one",
                                 base_path + "mesh_8.hdr",
                                 std::vector<Float>{47.0, 62.0, 0.0},
                                 std::vector<Float>{58.0, 73.0, 23.0},
                                 // 0.338547 + 0.33, // hue
                                 0.385,
                                 // 0.767942 - 0.2, // sat
                                 1.0,
                                 4096.0 / 8.0, // turb_period
                                 0.0, // xtrans
                                 0.0, // ytrans
                                 0.0, // ztrans
                                 1.0, // g_const,
                                 4.5, // x_const,
                                 3.7, // t_const
                                 1.0, // phase
                                 5.0); // power

    pbrtTransformBegin();

    initializeProceduralMedium("bishop_one_vol",
                               "heterogeneous",
                               "bishop_one",
                               transType,
                               "const",
                               "const",
                               "absorptive",
                               std::vector<Float>{1.0, 1.0, 1.0},
                               std::vector<Float>{0.0, 0.0, 0.0},
                               std::vector<Float>{47.0, 62.0, 0.0},
                               std::vector<Float>{58.0, 73.0, 23.0},
                               std::vector<Float>{1.0, 1.0, 1.0},
                               majScale);
    pbrtTransformEnd();

    pbrtAttributeBegin();
    pbrtTranslate((j+0.5) * sizeX, (i+0.5) * sizeY, 0.0);
    pbrtScale(0.2, 0.2, 0.2);


    initializeGlass("bishop_one",
                    1.5);

    // initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
    //                 std::vector<Float>{1.0, 1.0, 1.0},
    //                 1.5);

    pbrtMediumInterface("bishop_one_vol", "");
    initializePlyShape("bishop_centered_final.ply");

    pbrtAttributeEnd();
}

void Teaser::initializeBishop_Two(std::string transType, Float majScale)
{
    std::string base_path = "/Users/corneria/Documents/Research/testscenes/chess/textures/generated_2/";

    Float i = 5.0;
    Float j = 1.0;
    double startX = 0.0;
    double startY = 0.0;
    double sizeX = 15.0;
    double sizeY = 15.0;

    // initializeDeintegratedTextureMedium("bishop_two",
    //                                     base_path + "mesh_9.hdr",
    //                                     std::vector<Float>{17.0, 77.0, 0.0},
    //                                     std::vector<Float>{28.0, 88.0, 23.0});

    initializeChessTextureMedium("bishop_two",
                                 base_path + "mesh_9.hdr",
                                 std::vector<Float>{17.0, 77.0, 0.0},
                                 std::vector<Float>{28.0, 88.0, 23.0},
                                 // 0.280653 + 0.33, // hue
                                 0.385,
                                 // 0.77861 - 0.2, // sat
                                 1.0,
                                 4096.0 / 10.0, // turb_period
                                 0.0, // xtrans
                                 0.0, // ytrans
                                 0.0, // ztrans
                                 1.0, // g_const,
                                 4.5, // x_const,
                                 3.3, // t_const
                                 1.4, // phase
                                 7.5); // power

    pbrtTransformBegin();

    initializeProceduralMedium("bishop_two_vol",
                               "heterogeneous",
                               "bishop_two",
                               transType,
                               "const",
                               "const",
                               "absorptive",
                               std::vector<Float>{1.0, 1.0, 1.0},
                               std::vector<Float>{0.0, 0.0, 0.0},
                               std::vector<Float>{17.0, 77.0, 0.0},
                               std::vector<Float>{28.0, 88.0, 23.0},
                               std::vector<Float>{1.0, 1.0, 1.0},
                               majScale);
    pbrtTransformEnd();

    pbrtAttributeBegin();
    pbrtTranslate((j+0.5) * sizeX, (i+0.5) * sizeY, 0.0);
    pbrtScale(0.2, 0.2, 0.2);
    pbrtRotate(-90.0, 0.0, 0.0, 1.0);


    initializeGlass("bishop_two",
                    1.5);

    // initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
    //                 std::vector<Float>{1.0, 1.0, 1.0},
    //                 1.5);

    pbrtMediumInterface("bishop_two_vol", "");
    initializePlyShape("bishop_centered_final.ply");

    pbrtAttributeEnd();
}

void Teaser::initializeKing(std::string transType, Float majScale)
{
    std::string base_path = "/Users/corneria/Documents/Research/testscenes/chess/textures/generated_2/";

    // Float i = 2.0;
    // Float j = 2.0;
    // double startX = 0.0;
    // double startY = 0.0;
    // double sizeX = 15.0;
    // double sizeY = 15.0;

    Float i = 2.0;
    Float j = 3.0;
    double startX = 0.0;
    double startY = 0.0;
    double sizeX = 15.0;
    double sizeY = 15.0;

    // initializeDeintegratedTextureMedium("king",
    //                                     base_path + "mesh_10.hdr",
    //                                     std::vector<Float>{32.0, 32.0, 0.0},
    //                                     std::vector<Float>{43.0, 43.0, 30.0});

    // initializeChessTextureMedium("king",
    //                              base_path + "mesh_10.hdr",
    //                              std::vector<Float>{32.0, 32.0, 0.0},
    //                              std::vector<Float>{43.0, 43.0, 30.0});

    initializeChessTextureMedium("king",
                                 base_path + "mesh_10.hdr",
                                 std::vector<Float>{47.0, 32.0, 0.0},
                                 std::vector<Float>{58.0, 43.0, 30.0},
                                 // .385, // hue
                                 0.80,
                                 1.0, // sat
                                 4096.0 / 5.0, // turb_period
                                 15.0, // xtrans
                                 0.0, // ytrans
                                 0.0, // ztrans
                                 1.0, // g_const,
                                 4.5, // x_const,
                                 7.0, // t_const
                                 1.0, // phase
                                 4.0); // power

    pbrtTransformBegin();

    initializeProceduralMedium("king_vol",
                               "heterogeneous",
                               "king",
                               transType,
                               "const",
                               "const",
                               "absorptive",
                               std::vector<Float>{1.0, 1.0, 1.0},
                               std::vector<Float>{0.0, 0.0, 0.0},
                               std::vector<Float>{47.0, 32.0, 0.0},
                               std::vector<Float>{58.0, 43.0, 30.0},
                               std::vector<Float>{1.0, 1.0, 1.0},
                               majScale);
    pbrtTransformEnd();

    pbrtAttributeBegin();
    pbrtTranslate((j+0.5) * sizeX, (i+0.5) * sizeY, 0.0);
    pbrtScale(0.2, 0.2, 0.2);
    pbrtRotate(135.0, 0.0, 0.0, 1.0);


    initializeGlass("king",
                    1.5);

    // initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
    //                 std::vector<Float>{1.0, 1.0, 1.0},
    //                 1.5);

    pbrtMediumInterface("king_vol", "");
    initializePlyShape("king_centered_final_7.ply");

    pbrtAttributeEnd();
}

void Teaser::initializeQueen(std::string transType, Float majScale)
{
    std::string base_path = "/Users/corneria/Documents/Research/testscenes/chess/textures/generated_2/";

    // Float i = 2.0;
    // Float j = 3.0;
    // double startX = 0.0;
    // double startY = 0.0;
    // double sizeX = 15.0;
    // double sizeY = 15.0;

    Float i = 2.0;
    Float j = 2.0;
    double startX = 0.0;
    double startY = 0.0;
    double sizeX = 15.0;
    double sizeY = 15.0;

    // initializeDeintegratedTextureMedium("queen",
    //                                     base_path + "mesh_11.hdr",
    //                                     std::vector<Float>{47.0, 32.0, 0.0},
    //                                     std::vector<Float>{58.0, 43.0, 26.0});

    initializeChessTextureMedium("queen",
                                 base_path + "mesh_11.hdr",
                                 std::vector<Float>{32.0, 32.0, 0.0},
                                 std::vector<Float>{43.0, 43.0, 26.0},
                                 // std::vector<Float>{58.0, 43.0, 26.0},
                                 // 0.351486 + 0.33, // hue
                                 0.385,
                                 // 0.798191 - 0.2, // sat
                                 1.0,
                                 4096.0 / 5.5, // turb_period
                                 -15.0, // xtrans
                                 0.0, // ytrans
                                 0.0, // ztrans
                                 1.0, // g_const,
                                 4.5, // x_const,
                                 4.5, // t_const
                                 1.2, // phase
                                 4.0); // power

    pbrtTransformBegin();

    initializeProceduralMedium("queen_vol",
                               "heterogeneous",
                               "queen",
                               transType,
                               "const",
                               "const",
                               "absorptive",
                               std::vector<Float>{1.0, 1.0, 1.0},
                               std::vector<Float>{0.0, 0.0, 0.0},
                               std::vector<Float>{32.0, 32.0, 0.0},
                               std::vector<Float>{43.0, 43.0, 26.0},
                               std::vector<Float>{1.0, 1.0, 1.0},
                               majScale);
    pbrtTransformEnd();

    pbrtAttributeBegin();
    pbrtTranslate((j+0.5) * sizeX, (i+0.5) * sizeY, 0.0);
    pbrtScale(0.2, 0.2, 0.2);


    initializeGlass("queen",
                    1.5);

    // initializeGlass(std::vector<Float>{1.0, 1.0, 1.0},
    //                 std::vector<Float>{1.0, 1.0, 1.0},
    //                 1.5);

    pbrtMediumInterface("queen_vol", "");
    initializePlyShape("queen_centered_final.ply");

    pbrtAttributeEnd();
}
