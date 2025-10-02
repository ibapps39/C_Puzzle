#pragma once

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>


#include "raylib.h"
#include "rlgl.h"

// Constants
#define FRAME_RATE 60
#define PLAYER_HEIGHT 2.0f
#define PLAYER_RADIUS 0.5f
#define GRAVITY -9.8f
#define MOVE_SPEED 5.0f
#define JUMP_FORCE 6.0f



// Camera struct to store camera settings and label
typedef struct
{
    Camera3D camera;
    const char *cameraLabel;
} CameraName;



// Player data, including shape and score
typedef struct
{
    double* playerScore;
    const char* playerName;
    Camera3D* playerCamera;
    Vector3* currentPOS;
    Vector3* velocity;  // Store velocity vector
    float angle;
    float dx, dy, dz;
} Player;


// Player data, including shape and score
typedef struct
{
    Vector3* POS;
    double* Score;
    const char* Name;
    Camera3D* Camera;
    Vector3* Velocity;          // Store velocity vector
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
typedef struct AABB {
    Vector3 min;
    Vector3 max;
} AABB;


// bool CheckCollisionPLAYER(Player* PlayerBox, AABB* CollisionBox)
// {
//     // return CheckCollisionBoxes()

// }

// Initialization Functions
void InitCamera(Camera3D *camera, const CameraSettings *cameraSettings)
{
    camera->fovy = cameraSettings->camFOVY;
    camera->position = cameraSettings->camPosition;
    camera->projection = cameraSettings->camProjection;
    camera->target = cameraSettings->camTarget;
    camera->up = cameraSettings->camUp;
}
void InitPlayerWithSettings(Player* player, PlayerSettings* ps)
{
    player->playerCamera = ps->Camera;
    player->playerName = ps->Name;
    player->currentPOS = ps->POS;
    player->playerScore = ps->Score;
    player->velocity = ps->Velocity;
}

void InitPlayerByValue(
    Player* player, 
    Camera3D camera, 
    const char* name, 
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

void MovePlayer(Player *player, const float units)
{
    // if player turns past 2pi, subtract it 0 for next count
    if (player->angle <= 0) {
        player->angle += 2*PI;
        
    }
    if (player->angle >= 2*PI) 
    {
        player->angle -= 2*PI;
    }
    if (IsKeyDown(KEY_W))
    {
        player->currentPOS->z += units;
    }
    if (IsKeyDown(KEY_S))
    {
        player->currentPOS->z -= units;
    }
    if (IsKeyDown(KEY_A))
    {
        player->currentPOS->x += units;
    }
    if (IsKeyDown(KEY_D))
    {
        player->currentPOS->x -= units;
    }
}
void MoveCamera(Camera3D *cam, const float units)
{
    if (IsKeyDown(KEY_W))
    {
        cam->position.z += units;
    }
    if (IsKeyDown(KEY_S))
    {
        cam->position.z -= units;
    }
    if (IsKeyDown(KEY_A))
    {
        cam->position.x -= units;
    }
    if (IsKeyDown(KEY_D))
    {
        cam->position.x += units;
    }
}

// Points u to v
void SetVector(Vector3* u, Vector3* v)
{
    u = v;
}
void SetVectorPoints(Vector3* u, Vector3* v)
{
    u->x = v->x;
    u->y = v->y;
    u->z = v->z;
}
void CopyVector(Vector3* u, Vector3 pos)
{
    u->x = pos.x;
    u->y = pos.y;
    u->z = pos.z;
}

void SetPosByValue(Player* player, Vector3 pos)
{
    player->currentPOS->x = pos.x;
    player->currentPOS->y = pos.y;
    player->currentPOS->z = pos.z;
}
void SetPlayerPoint(Player* player, float x, float y, float z)
{
    player->currentPOS->x = x;
    player->currentPOS->y = y;
    player->currentPOS->z = z;
}
void SetPlayerVector(Player* player, Vector3* u)
{
    player->currentPOS = u;
}

void GetPlayerAngle(Player* player)
{
    double pdx, pdy;
    
}

//**
// // Game Update and Draw functions
// void UpdateGame(void);
// void UpdatePlayerCAM(Player *player, Camera3D *playerCamera);
// void DrawGame(void);
// void CheckCollisions(void);
// float playersDist(const Player *player, const Player *opponent);


// // Level Functions

// // Drawing Functions
// void DrawPlayerScore(const Player *player, const Camera3D *camera);


// // Player Movement and Interaction
// bool currentKey(KeyboardKey k); 
// void MoveCamera(Camera3D *cam, const float units);
// void MovePlayer(Player *player, const float units);
// void PlayerJump(Player *player, const float jumpHeight);
// void GetPlayerInfo(const Player *player);
// void DrawCameraInfo(const Camera3D *camera, const Player *player);
// void CameraInfo(Camera3D *camera);
// void UpdatePlayerCamera(Player *player);


// // Score and Scoring
// void incrementPoints(Player *player, double points);
// void animatedScored(Player* player, Camera* cam);

// //Set Functions
// // bool setPOS(Player* player, Vector3* pos);
// // bool setPOS(Player* player, Vector3* pos));
// bool setPOS(Player* player, float x, float y, float z);
// bool setVelocity(Player* player, Vector3* v);
// bool setCamera(Player* player, Camera3D* Camera3D);
// bool setName(Player* player, const char* name);
// bool setScore(Player* player, double score);


// void debugDisplay(Player player, Camera* camera);

// void UpdatePlayerVelocity(Player *player);


// void displayViewPortStats(Camera3D viewport_cam)
// {
//     DrawText(
//             TextFormat(
//                 "CAMERA\n
//                 \tviewport_cam.fovy :\t % .2f\n
//                 \tviewport_cam.position :\t % .2f\n
//                 \tviewport_cam.projection :\t % .2f\n
//                 \tviewport_cam.target :\t % .2f % .2f % .2f\n
//                 \tviewport_cam.up :\t % .2f\n",
//                 viewport_cam.fovy,
//                 viewport_cam.position,
//                 viewport_cam.projection,
//                 viewport_cam.target.x,
//                 viewport_cam.target.y,
//                 viewport_cam.target.z,
//                 viewport_cam.up),
//             10, 280, 25, BLACK);
// }