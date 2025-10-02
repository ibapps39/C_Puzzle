#include "game.h"
int main()
{
    int screenWidth, screenHeight;
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Vector3 cube_pos = {0.0f, 1.0f, 0.0f};
    Vector3 cubeSize = { 2.0f, 2.0f, 2.0f };

    Camera3D main_cam = (Camera3D){0};
    main_cam.fovy = 45.0f;
    main_cam.position = (Vector3){0, 0, -10};
    main_cam.projection = CAMERA_PERSPECTIVE;
    main_cam.target = cube_pos;
    main_cam.up = (Vector3) {0, 1, 0};

    //InitCamera(camera->main_cam, &settings);
    Camera3D player_cam = {0};
    player_cam.fovy = 45.0f;
    player_cam.position = (Vector3){10, 10, 10};
    player_cam.projection = CAMERA_ORTHOGRAPHIC;
    player_cam.target = cube_pos;
    player_cam.up = (Vector3) {0, 1, 0};

    Camera3D viewport_cam = (Camera3D){0};
    viewport_cam.fovy = 45.0f;
    viewport_cam.position = (Vector3){0, 0, 0};
    viewport_cam.projection = CAMERA_PERSPECTIVE;
    viewport_cam.target = cube_pos;
    viewport_cam.up = (Vector3) {0, 1, 0};


    Player player;
    player.playerName = "p1";
    player.currentPOS = &(Vector3){0};
    player.playerScore = 0;
    player.velocity = &(Vector3){0};
    player.playerCamera = &(Camera3D){0};

    Vector3 floor = {.x = 0, .y = -2, .z = 0};

    // struct GUI_SETTINGS
    // {
    //     int screen_x;
    //     int screen_y;
    // };
    //MoveCamera(&main_cam, 5.0f);

    while (!WindowShouldClose())
    {
        //if (IsCursorHidden()) UpdateCamera(&main_cam, CAMERA_FIRST_PERSON);
        
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText(
                    TextFormat(
                        "CAMERA POS \n\tx:\t%.2f\n\ty:\t%.2f\n\tz:\t%.2f\n", 
                        viewport_cam.position.x, 
                        viewport_cam.position.y, 
                        viewport_cam.position.z
                    ), 
                    10, 
                    20, 
                    25, 
                    RED
                );
        DrawText(
                TextFormat(
                        "Player POS \n\tx:\t%.2f\n\ty:\t%.2f\n\tz:\t%.2f\n", 
                        player.currentPOS->x, 
                        player.currentPOS->y, 
                        player.currentPOS->z
                    ), 
                    10, 
                    130, 
                    25, 
                    RED
                );
        DrawText(
            TextFormat(
                "CAMERA \n\tviewport_cam.fovy :\t % .2f\n\tviewport_cam.position :\t % .2f\n\tviewport_cam.projection :\t % .2f\n\tviewport_cam.target :\t % .2f % .2f % .2f\n\tviewport_cam.up :\t % .2f\n ",
                viewport_cam.fovy,
                viewport_cam.position,
                viewport_cam.projection,
                viewport_cam.target.x,
                viewport_cam.target.y,
                viewport_cam.target.z,
                viewport_cam.up),
            10, 280, 25, BLACK);

        BeginMode3D(viewport_cam);
        viewport_cam.target = *player.currentPOS;
        viewport_cam.position.y = player.currentPOS->y;
        viewport_cam.position.z = player.currentPOS->z - 15;
        viewport_cam.position.x = player.currentPOS->x;

        DrawCube(floor, 100, 2, 100, RED);
        //USE DELTA TIME
        MovePlayer(&player, (5.0)/60);
        DrawCube(cube_pos, 2, 2, 2, BLUE);
        //PLAYER
        DrawCube(*player.currentPOS, 2, 2, 2, YELLOW);

        EndMode3D();
        EndDrawing();
    }
    return 0;
}