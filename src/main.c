#include "game.h"
int main()
{
    int screenWidth, screenHeight;
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Vector3 cube_pos = {0.0f, 1.0f, 0.0f};
    Vector3 cubeSize = { 2.0f, 2.0f, 2.0f };

    Camera3D main_cam = {0};
    main_cam.fovy = 45.0f;
    main_cam.position = (Vector3){10, 10, 10};
    main_cam.projection = CAMERA_ORTHOGRAPHIC;
    main_cam.target = cube_pos;
    main_cam.up = (Vector3) {0, 1, 0};
    //InitCamera(camera->main_cam, &settings);

    

    Player player;
    Vector3 pos = {0};
    player.currentPOS = &pos;

    Vector3 floor = {.x = 0, .y = 0, .z = 0};

    while (!WindowShouldClose())
    {
        if (IsCursorHidden()) UpdateCamera(&main_cam, CAMERA_FIRST_PERSON);
        BeginDrawing();

        ClearBackground(WHITE);
        DrawCube(cube_pos, 2, 2, 2, RED);
        // DrawCube(floor, 100, 2, 100, RED);

        EndDrawing();
    }
    
    return 0;
}