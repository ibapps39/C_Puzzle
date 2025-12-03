#include "game.h"
#include "blocks.h"
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

    BoundingBox test_cube_bbox;
    BoundingBox camera_bbbox;
    BoundingBox reticle_bbox;

    Color test_cube_color = (Color){0,0,0,0};
    Color test_cube_bbox_color = GREEN;
    Color reticle_bbox_color = BLACK;

    float test_cube_radius = 2;
    float reticle_bbox_radius = DEFAULT_BLOCK_SIZE;

    Vector3 test_cube_pos = (Vector3){3, floor-2, 4.0f};
    Vector3 reticle_bbox_pos = Vector3Zero();
    
    // reticle bbox stuff
    calc_boundingbox_at(&test_cube_bbox, test_cube_pos, test_cube_radius*.505);

    // help center at start
    the_camera.target = test_cube_pos;
    static float r_test = 0;
    static float r_test_co = 1;
    // Main game loop
    while (!WindowShouldClose())
    {
        if (r_test >= test_cube_radius) r_test_co *= -1;
        if (r_test <= test_cube_radius) r_test_co *= -1;
        r_test += 0.001*r_test_co;
        Vector3 reticle_v = get_placement_vector(&the_camera, ADD_BLOCK_DIST_MAX);
        
        // Make a set bbox min/max func
        camera_bbbox.max = Vector3AddValue(the_camera.position, 1);
        camera_bbbox.min = Vector3SubtractValue(the_camera.position, 1);
        
        
        reticle_bbox_color = CheckCollisionBoxes(reticle_bbox, test_cube_bbox) ? RED : GREEN;
        reticle_bbox.max = Vector3AddValue(reticle_bbox_pos, 1);
        reticle_bbox.min = Vector3SubtractValue(reticle_bbox_pos, 1);
        reticle_bbox_pos = reticle_v;
        
        
        
        // Delta time for frame-independent movement
        float delta = GetFrameTime();
        move_based_cam(&the_camera, 5.0f * delta);
        rotate_camera(&the_camera, 0.1f, &yaw, &pitch); // mouse look
        Gravity(&the_camera, &verticalVelocity);
        // Reset player position if Q is pressed
        if (IsKeyDown(KEY_Q)) 
        { 
            the_camera.position = (Vector3){0, floor, 0}; 
        }

        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode3D(the_camera);
// Begin
        test_cube_color = CheckCollisionBoxes(camera_bbbox, test_cube_bbox) ? RED : GREEN;
        DrawCube(test_cube_pos, test_cube_radius, test_cube_radius, test_cube_radius, test_cube_color);

        DrawBoundingBox(test_cube_bbox, test_cube_color);
        DrawBoundingBox(reticle_bbox, reticle_bbox_color);
        //draw_reticle(&reticle_v);

        rl_draw_list(render_list.positions_array, render_list_limit);
        DrawCube(floor_pos, floor_width, floor_height, floor_length, floor_color);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            add_block_to_list(&render_list, &reticle_v);
        }
        apply_rl_collisions(&render_list, &the_camera);
// End
        EndMode3D();
        EndDrawing();
    }

    // Clean up
    CloseWindow();
    return 0;
}
