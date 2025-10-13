#include "game.h"

int main()
{
    // Get screen size and initialize window
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    // Basic scene setup
    Vector3 cube_pos = {0.0f, 1.0f, 0.0f};
    Vector3 cubeSize = {2.0f, 2.0f, 2.0f};
    Vector3 floor = {0.0f, -2.0f, 0.0f};

    // Properly allocate Vector3s
    Vector3 playerPosition = {0};
    Vector3 playerVelocity = {0};

    // Player Camera
    Camera3D player_cam = {
    .position = playerPosition,
    .target = {0, 0, 10},
    .up = {0, 1, 0},
    .fovy = 45.0f,
    .projection = CAMERA_FIRST_PERSON
};

    Player player = {
        .playerName = "p1",
        .currentPOS = &player_cam.position,
        .velocity = &playerVelocity,
        .playerCamera = NULL,  // Set below
        .playerScore = 0
    };

    player.playerCamera = &player_cam;

    // Main game loop
    while (!WindowShouldClose())
    {
        
        if (player.currentPOS->y <= 0) player.currentPOS->y = 1;
        // Delta time for frame-independent movement
        float delta = GetFrameTime();

        // Move the player based on input and camera orientation
        MovePlayer(&player, player.playerCamera, 5.0f * delta);

        // Reset player position if Q is pressed
        if (IsKeyDown(KEY_Q))
        {
            SetPlayerPoint(&player, 0, 0, 0);
        }

        // Update camera mode (first-person controls)
        UpdateCamera(player.playerCamera, player.playerCamera->projection);

        // Begin 3D drawing
        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode3D(*player.playerCamera);

        // Draw the scene
        DrawCube(floor, 100, floor.y+2, 100, ORANGE);
        DrawCube(cube_pos, cubeSize.x, cubeSize.y, cubeSize.z, BLUE);
        drawDirections();
        // DrawCube(*player.currentPOS, 2, 2, 2, YELLOW); // Optional: show player

        EndMode3D();

        // HUD or debug info
        DrawText(
            TextFormat("player.currentPOS->x:%.2f\nplayer.currentPOS->y:%.2f\nplayer.currentPOS->z:%.2f\nplayer.playerCamera->position:%.2f\nplayer.playerCamera->position.y:%.2f\nplayer.playerCamera->position.z:%.2f\nplayer.playerCamera->target.x:%.2f\nplayer.playerCamera->target.y:%.2f\nplayer.playerCamera->target.z:%.2f\n",
            player.currentPOS->x,
            player.currentPOS->y,
            player.currentPOS->z,
            player.playerCamera->position.x,
            player.playerCamera->position.y,
            player.playerCamera->position.z,
            player.playerCamera->target.x,
            player.playerCamera->target.y,
            player.playerCamera->target.z
        ),
        10,
        100,
        10,
        BLACK
        );
        EndDrawing();
    }

    // Clean up
    CloseWindow();
    return 0;
}
