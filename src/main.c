#include "game.h"
#include "room.h"
#include "render.h"
#include "collision.h"
int main()
{
    // Get screen size and initialize window
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    // Floor
    Vector3 floor_pos;
    int floor_width, floor_height, floor_length;
    Color floor_color = RED;
    floor_pos = (Vector3){0.0f, (float)GROUND - 2, 0.0f};
    floor_width = 1000;
    floor_height = 2;
    floor_length = 1000;
    float floor = 2.0f; // y

    // Camera
    Camera3D the_camera;
    the_camera.fovy = 120;
    the_camera.position = (Vector3){0.0f, 2.0f, 0.0f};
    the_camera.projection = CAMERA_PERSPECTIVE;
    the_camera.target = (Vector3){0, 1, 3};
    the_camera.up = (Vector3){0.0f, 2.0f, 0.0f};

    SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
    DisableCursor(); // Locks the mouse and hides the cursor
    float yaw = 0.0f;
    float pitch = 0.0f;

    float verticalVelocity = 0.0f;

    RenderList render_list;
    int render_list_limit = (int)MAX_RENDER_LIST_ELEMENTS;
    rl_init(&render_list, render_list_limit);

    //basic_room_init(room_lvl, )

    // Main game loop
    while (!WindowShouldClose())
    {

        // Delta time for frame-independent movement
        float delta = GetFrameTime();
        moveBasedCam(&the_camera, 5.0f * delta);
        RotateCamera(&the_camera, 0.1f, &yaw, &pitch); // mouse look
        Gravity(&the_camera, &verticalVelocity);

        // Reset player position if Q is pressed
        if (IsKeyDown(KEY_Q)) 
        { 
            the_camera.position = (Vector3){0, floor, 0}; 
        }

        // Begin Imaging
        BeginDrawing();
        ClearBackground(WHITE);
        // BEGIN 3D BEGIN 3D BEGIN 3D BEGIN 3D BEGIN 3D BEGIN 3D BEGIN 3D BEGIN 3D BEGIN 3D BEGIN 3D BEGIN 3D BEGIN 3D
        BeginMode3D(the_camera);
        // Draw reticle
        Vector3 reticle_v = get_placement_vector(&the_camera, ADD_BLOCK_DIST_MAX);
        draw_reticle(&reticle_v);
        // Draw the scene
        click_add_to_list(render_list.positions_array, render_list_limit);
        DrawCube(floor_pos, floor_width, floor_height, floor_length, floor_color);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            addBlock(&render_list, &reticle_v);
        }
        apply_rl_collisions(&render_list, &the_camera);
        // END 3D END 3D END 3D END 3D END 3D END 3D END 3D END 3D END 3D END 3D END 3D END 3D END 3D END 3D END 3D END 3D
        EndMode3D();

        draw_render_list(&render_list);

        EndDrawing();
    }

    // Clean up
    CloseWindow();
    return 0;
}
