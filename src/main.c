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

    // Reference Cube
    Vector3 refCube_pos;
    int refCube_width, refCube_height, refCube_length;
    Color refCube_color;
    refCube_pos = (Vector3){0.0f, 2.0f, 4.0f};
    refCube_width = 2;
    refCube_height = 2;
    refCube_length = 2;
    refCube_color = BLUE;

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
    the_camera.target = refCube_pos;
    the_camera.up = (Vector3){0.0f, 2.0f, 0.0f};

    // XVA
    Vector3 currentPOS = (Vector3){0};
    Vector3 previousPOS = currentPOS;
    float V = Vector3Length(Vector3Subtract(*&currentPOS, *&previousPOS));
    float *Vc = &V;
    float A = (*Vc - V);

    SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
    DisableCursor(); // Locks the mouse and hides the cursor
    float yaw = 0.0f;
    float pitch = 0.0f;

    float verticalVelocity = 0.0f;

    RenderList render_list;
    int render_list_limit = (int)MAX_RENDER_LIST_ELEMENTS;
    rl_init(&render_list, render_list_limit);

    // Main game loop
    while (!WindowShouldClose())
    {

        currentPOS = *&the_camera.position;
        previousPOS = currentPOS;

        // Delta time for frame-independent movement
        float delta = GetFrameTime();

        V = Vector3Length(Vector3Subtract(*&currentPOS, *&previousPOS));
        Vc = &V;
        A = (*Vc - V);

        moveBasedCam(&the_camera, 5.0f * delta);
        RotateCamera(&the_camera, 0.1f, &yaw, &pitch); // mouse look
        Gravity(&the_camera, &verticalVelocity);

        // Reset player position if Q is pressed
        if (IsKeyDown(KEY_Q))
            the_camera.position = (Vector3){0, floor, 0};

        // Begin 3D drawing
        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode3D(the_camera);

        // Draw reticle
        Vector3 reticle_v = get_placement_vector(&the_camera, ADD_BLOCK_DIST_MAX);
        draw_reticle(&reticle_v);
        // Draw the scene
        ClickArrayRender(render_list.positions_array, render_list_limit);
        DrawCube(floor_pos, floor_width, floor_height, floor_length, floor_color);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector3 v = get_placement_vector(&the_camera, ADD_BLOCK_DIST_MAX);
            addBlock(&render_list, &v);
        }
        apply_rl_collisions(&render_list, &the_camera);

        EndMode3D();

        // HUD or debug info
        DrawText(
            TextFormat("the_camera.position.x:%.2f\nthe_camera.position.y:%.2f\nthe_camera.position.z:%.2f\nthe_camera.target.x:%.2f\nthe_camera.target.y:%.2f\nthe_camera.target.z:%.2f\n",
                       the_camera.position.x,
                       the_camera.position.y,
                       the_camera.position.z,
                       the_camera.target.x,
                       the_camera.target.y,
                       the_camera.target.z),
            10,
            100,
            20,
            BLACK);

        DrawText(
            TextFormat("curposition.x:%.2f\ncurposition.y:%.2f\ncurposition.z:%.2f\n,prevposition.x:%.2f\nprevposition.y:%.2f\nprevposition.z:%.2f\nv:%.2f\na:%.2f\n",
                       currentPOS.x,
                       currentPOS.y,
                       currentPOS.z,
                       previousPOS.x,
                       previousPOS.y,
                       previousPOS.z,
                       Vc,
                       A),
            10,
            230,
            20,
            PINK);
        drawlist(&render_list);

        EndDrawing();
    }

    // Clean up
    CloseWindow();
    return 0;
}
