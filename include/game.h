#pragma once

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"


// Constants
#define FRAME_RATE 60
#define PLAYER_HEIGHT 2.0f
#define PLAYER_RADIUS 0.5f
#define GRAVITY 9.8f
#define MOVE_SPEED 5.0f
#define JUMP_FORCE 6.0f
#define SPRINT_MODIFIER 10.0f
#define GROUND 0

#define TURQUOISE CLITERAL(Color){64, 224, 208, 255}

// Camera struct to store camera settings and label
typedef struct
{
    Camera3D camera;
    const char *cameraLabel;
} CameraName;

// Player data, including shape and score
typedef struct
{
    double *playerScore;
    const char *playerName;
    Camera3D *playerCamera;
    Vector3 *currentPOS;
    Vector3 *velocity; // Store velocity vector
    float angle;
    float dx, dy, dz;
} Player;

// Player data, including shape and score
typedef struct
{
    Vector3 *POS;
    double *Score;
    const char *Name;
    Camera3D *Camera;
    Vector3 *Velocity; // Store velocity vector
} PlayerSettings;

// Camera settings for player and its camera
typedef struct
{
    Vector3 camPosition;
    Vector3 camTarget;
    Vector3 camUp;
    float camFOVY;
    int camProjection;
    const char *camSettingsLabel;
    Player associatedPlayer;
} CameraSettings;

// Axis-aligned bounding box for collisions
typedef struct AABB
{
    Vector3 min;
    Vector3 max;
} AABB;

// Initialization Functions
void init_camera(Camera3D *camera, const CameraSettings *cameraSettings)
{
    camera->fovy = cameraSettings->camFOVY;
    camera->position = cameraSettings->camPosition;
    camera->projection = cameraSettings->camProjection;
    camera->target = cameraSettings->camTarget;
    camera->up = cameraSettings->camUp;
}
void init_player_with_settings(Player *player, PlayerSettings *ps)
{
    player->playerCamera = ps->Camera;
    player->playerName = ps->Name;
    player->currentPOS = ps->POS;
    player->playerScore = ps->Score;
    player->velocity = ps->Velocity;
}

void init_player_by_value(
    Player *player,
    Camera3D camera,
    const char *name,
    Vector3 pos,
    double score,
    Vector3 v)
{
    player->playerCamera = &camera;
    player->playerName = name;
    player->currentPOS = &pos;
    player->playerScore = &score;
    player->velocity = &v;
}

int sign(int x)
{
    if (x > 0)
    {
        return 1;
    }
    else if (x == 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

Vector3 get_direction(Camera3D* cam)
{
    Vector3 pos = cam->position;
    Vector3 target = cam->target;
    return Vector3Subtract(target, pos);
}

void move_based_cam(Camera3D *cam, const float speed)
{
    bool moveFwd = IsKeyDown(KEY_W);
    bool moveBack = IsKeyDown(KEY_S);
    bool moveLeft = IsKeyDown(KEY_A);
    bool moveRight = IsKeyDown(KEY_D);
    bool moveJump = IsKeyDown(KEY_SPACE);
    bool moveSprint = IsKeyDown(KEY_LEFT_SHIFT);
    float units = moveSprint ? speed * SPRINT_MODIFIER : speed;
    if (!(moveFwd || moveBack || moveLeft || moveRight || moveJump)) return;

    
    DrawText(TextFormat("units: %.2f", units), 10, 60, 30, PINK);
    Vector3 pos = cam->position;
    Vector3 target = cam->target;
    Vector3 fwd = get_direction(cam);
    Vector3 fwdN = Vector3Normalize(fwd);
    Vector3 fwdNScaled = Vector3Scale(fwdN, units);

    Vector3 delta = (Vector3){0.0f, 0.0f, 0.0f};

    if (moveFwd)  delta = Vector3Add        (delta, (Vector3){fwdNScaled.x, 0, fwdNScaled.z});
    if (moveBack) delta = Vector3Subtract   (delta, (Vector3){fwdNScaled.x, 0, fwdNScaled.z});
    if ((moveRight || moveLeft))
    {
        Vector3 perpV = Vector3CrossProduct(fwdN, cam->up);
        Vector3 perpN = Vector3Normalize(perpV);
        Vector3 perpNScaled = Vector3Scale(perpN, units);
        if (moveLeft)
            delta = Vector3Subtract(delta, perpNScaled);
            delta = Vector3Scale(delta, units);
        if (moveRight)
            delta = Vector3Add(delta, perpNScaled);
            delta = Vector3Scale(delta, units);
    }

    if (moveJump)
        delta.y += units;

    // Scaling speedup scale fix
    delta = Vector3Normalize(delta);
    delta = Vector3Scale(delta, units);

    cam->position = Vector3Add(pos, delta);
}

void rotate_camera(Camera3D *cam, float mouseSensitivity, float *yaw, float *pitch)
{
    Vector2 mouse_delta = GetMouseDelta();

    // looking left/right
    *yaw += mouse_delta.x * mouseSensitivity;
    // looking up/down. Inverted Y for screen so more up of cursor is a negative delta, so to add me flip sign
    *pitch -= mouse_delta.y * mouseSensitivity;

    if (*pitch > 89.0f)
    {
        *pitch = 89.0f;
    }
    if (*pitch < -89.0f)
    {
        *pitch = -89.0f;
    }

    float pitch_radians = DEG2RAD * (*pitch);
    float yaw_radians = DEG2RAD * (*yaw);

    Vector3 direction = {
        cosf(pitch_radians) * cosf(yaw_radians),
        sinf(pitch_radians),
        cosf(pitch_radians) * sinf(yaw_radians)
    };

    cam->target = Vector3Add(cam->position, direction);
}

void Gravity(Camera3D *cam, float *velocityY)
{
    float dt = GetFrameTime();

    if (cam->position.y > GROUND)
    {
        // Apply gravity (increase downward velocity)
        *velocityY += GRAVITY * dt;

        // Apply velocity to position
        cam->position.y -= (*velocityY) * dt;

        // Prevent going below the ground
        if (cam->position.y < GROUND)
        {
            cam->position.y = GROUND;
            *velocityY = 0.0f; // reset velocity when hitting the ground
        }
    }
    else
    {
        // Reset when on the ground
        cam->position.y = GROUND;
        *velocityY = 0.0f;
    }
}

// Points u to v
void set_vector(Vector3 *u, Vector3 *v)
{
    u = v;
}
void set_vector_points(Vector3 *u, Vector3 *v)
{
    u->x = v->x;
    u->y = v->y;
    u->z = v->z;
}
void copy_vector(Vector3 *u, Vector3 pos)
{
    u->x = pos.x;
    u->y = pos.y;
    u->z = pos.z;
}

void set_pos_by_value(Player *player, Vector3 pos)
{
    player->currentPOS->x = pos.x;
    player->currentPOS->y = pos.y;
    player->currentPOS->z = pos.z;
}
void set_player_point(Player *player, float x, float y, float z)
{
    player->currentPOS->x = x;
    player->currentPOS->y = y;
    player->currentPOS->z = z;
}
void set_player_vector(Player *player, Vector3 *u)
{
    player->currentPOS = u;
}

void get_player_angle(Player *player)
{
    double pdx, pdy;
}

void draw_directions()
{
    DrawCube((Vector3){-100, 0, 1000}, 100, 100, 100, RED);   // NORTH
    DrawCube((Vector3){-100, 100, 1000}, 100, 100, 100, RED); // NORTH
    DrawCube((Vector3){0, 100, 1000}, 100, 100, 100, RED);      // NORTH
    DrawCube((Vector3){100, 0, 1000}, 100, 100, 100, RED); 
    DrawCube((Vector3){200, 100, 1000}, 100, 100, 100, RED);  // NORTH

    DrawCube((Vector3){0, 0, -1000}, 100, 100, 100, GREEN); // SOUTH
    DrawCube((Vector3){-1000, 0, 0}, 100, 100, 100, BLUE);  // WEST
    DrawCube((Vector3){1000, 0, 0}, 100, 100, 100, YELLOW); // EAST
}