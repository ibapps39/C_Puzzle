```c
#include "raylib.h"
#include <math.h>
#include <stdio.h>

#define PLAYER_HEIGHT 2.0f
#define PLAYER_RADIUS 0.5f
#define GRAVITY -9.8f
#define MOVE_SPEED 5.0f
#define JUMP_FORCE 6.0f

// Player entity
typedef struct Player {
    Vector3 position;
    Vector3 velocity;
    bool onGround;
} Player;

// Axis-aligned bounding box for collisions
typedef struct AABB {
    Vector3 min;
    Vector3 max;
} AABB;

// Simple ground + block world
#define WORLD_BLOCKS 2
AABB world[WORLD_BLOCKS];

// Collision check (sphere vs AABB)
bool CheckCollisionSphereAABB(Vector3 center, float radius, AABB box, Vector3 *correction) {
    Vector3 closest = {
        fmaxf(box.min.x, fminf(center.x, box.max.x)),
        fmaxf(box.min.y, fminf(center.y, box.max.y)),
        fmaxf(box.min.z, fminf(center.z, box.max.z))
    };

    Vector3 diff = Vector3Subtract(center, closest);
    float distSq = Vector3DotProduct(diff, diff);

    if (distSq < radius * radius) {
        if (correction) *correction = diff;
        return true;
    }
    return false;
}

int main2(void) {
    InitWindow(1280, 720, "Raylib FPS Platformer");
    SetTargetFPS(60);
    DisableCursor(); // lock cursor for FPS look

    // Init player
    Player player = {0};
    player.position = (Vector3){0, PLAYER_HEIGHT, 0};
    player.velocity = (Vector3){0};
    player.onGround = false;

    // Init camera
    Camera3D camera = {0};
    camera.position = (Vector3){0, PLAYER_HEIGHT, -5};
    camera.target = Vector3Add(player.position, (Vector3){0, PLAYER_HEIGHT * 0.5f, 1});
    camera.up = (Vector3){0, 1, 0};
    camera.fovy = 75.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    float camYaw = 0.0f;
    float camPitch = 0.0f;

    // Build world
    world[0].min = (Vector3){-20, -1, -20};
    world[0].max = (Vector3){20, 0, 20};

    world[1].min = (Vector3){2, 0, 2};
    world[1].max = (Vector3){4, 3, 4};

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // --- Mouse look ---
        Vector2 mouseDelta = GetMouseDelta();
        camYaw += mouseDelta.x * 0.003f;
        camPitch += mouseDelta.y * 0.003f;
        if (camPitch > PI/2.0f) camPitch = PI/2.0f;
        if (camPitch < -PI/2.0f) camPitch = -PI/2.0f;

        Vector3 forward = {
            cosf(camPitch) * sinf(camYaw),
            sinf(camPitch),
            cosf(camPitch) * cosf(camYaw)
        };
        Vector3 right = (Vector3){sinf(camYaw - PI/2.0f), 0, cosf(camYaw - PI/2.0f)};

        // --- Player movement ---
        Vector3 move = {0};
        if (IsKeyDown(KEY_W)) move = Vector3Add(move, forward);
        if (IsKeyDown(KEY_S)) move = Vector3Subtract(move, forward);
        if (IsKeyDown(KEY_A)) move = Vector3Subtract(move, right);
        if (IsKeyDown(KEY_D)) move = Vector3Add(move, right);

        if (Vector3Length(move) > 0.1f) move = Vector3Normalize(move);
        move = Vector3Scale(move, MOVE_SPEED);

        player.velocity.x = move.x;
        player.velocity.z = move.z;

        // Gravity
        player.velocity.y += GRAVITY * dt;
        if (IsKeyPressed(KEY_SPACE) && player.onGround) {
            player.velocity.y = JUMP_FORCE;
            player.onGround = false;
        }

        // Apply movement
        player.position = Vector3Add(player.position, Vector3Scale(player.velocity, dt));

        // --- Collision resolution ---
        player.onGround = false;
        for (int i = 0; i < WORLD_BLOCKS; i++) {
            Vector3 correction;
            if (CheckCollisionSphereAABB(player.position, PLAYER_RADIUS, world[i], &correction)) {
                // Push player out
                player.position = Vector3Add(player.position, Vector3Normalize(correction));
                if (correction.y > 0.1f) {
                    player.velocity.y = 0;
                    player.onGround = true;
                }
            }
        }

        // --- Camera follows player ---
        camera.position = Vector3Lerp(camera.position,
            Vector3Add(player.position, (Vector3){0, PLAYER_HEIGHT * 0.8f, 0}),
            0.2f);
        camera.target = Vector3Add(camera.position, forward);

        // --- Draw ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        // Draw world
        DrawCubeV(Vector3Lerp(world[0].min, world[0].max, 0.5f),
                  Vector3Subtract(world[0].max, world[0].min), GRAY);

        DrawCubeV(Vector3Lerp(world[1].min, world[1].max, 0.5f),
                  Vector3Subtract(world[1].max, world[1].min), RED);

        // Draw player
        DrawSphere(player.position, PLAYER_RADIUS, BLUE);

        EndMode3D();

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
```