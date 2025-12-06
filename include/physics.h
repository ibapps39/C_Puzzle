#pragma once
#include "raylib.h"
#include "raymath.h"
#include <assert.h>
#define G -0.02f
#define JUMP_FORCE G*.20f
#define GROUND 0
#define TERMINAL_Y_VELOCITY -0.05f
#define SPRINT 2

typedef struct physics_info_player
{
    Vector3 player_dir_norm;
    Vector3 player_pos;
    Vector3 player_velocity;
    Vector3 player_accel;
} physics_info_player;

Vector3 get_direction_norm(Camera3D* cam)
{
    Vector3 pos = cam->position;
    Vector3 target = cam->target;
    
    return Vector3Normalize(Vector3Subtract(target, pos));
}

// Pass Camera's up vector usually
Vector3 get_right_vec_norm(Vector3 norm_dir, Vector3 norm_up_vec)
{
    return  Vector3Normalize(Vector3CrossProduct(norm_dir, norm_up_vec));
}

int is_movement_key_pressed()
{
    bool moveFwd = IsKeyDown(KEY_W);
    bool moveBack = IsKeyDown(KEY_S);
    bool moveLeft = IsKeyDown(KEY_A);
    bool moveRight = IsKeyDown(KEY_D);
    bool moveJump = IsKeyDown(KEY_SPACE);
    bool moveSprint = IsKeyDown(KEY_LEFT_SHIFT);
    return ( moveFwd || moveBack || moveLeft || moveRight || moveJump );
}

// just applies g. Should only call if player is above ground
void physics_gravity(Vector3* pos, float y_min, float gravity)
{
    float dt = GetFrameTime();
    float g = gravity > 0 ? gravity*-1: gravity;
    if (pos->y < y_min || g < TERMINAL_Y_VELOCITY)
    {
        g = 0;
        pos->y = y_min + 0.001;
    }
    pos->y += g*dt;
}


Vector3 get_da();
Vector3 get_dv(Vector3* a_v);
Vector3 get_dp(Vector3* pos, Vector3 dir_norm, Vector3 v)
{
    int key = GetKeyPressed();
    Vector3 delta = Vector3Zero();
    float sprint = (key == (KEY_LEFT_SHIFT || KEY_RIGHT_SHIFT)) ? SPRINT : 1;
    Vector3 dir = dir_norm;
    v = Vector3Scale(v, sprint);
    Vector3 p = *pos;
    
    switch (key)
    {
    case KEY_W:
    delta = Vector3Add(p, dir)
        break;
    case KEY_S:
        break;
    case KEY_A:
        break;
    case KEY_D:
        break;
    case KEY_SPACE:
        break;
    default:
        break;
    }
}