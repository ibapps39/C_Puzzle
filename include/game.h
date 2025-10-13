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
#define GRAVITY -9.8f
#define MOVE_SPEED 5.0f
#define JUMP_FORCE 6.0f

#define TURQUOISE CLITERAL(Color){ 64, 224, 208, 255 }



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

int sign(int x){
    if(x > 0){
        return 1;
    }else if(x == 0){
        return 0;
    }else{
        return -1;
    }
}

void MovePlayer(Player *player, Camera3D* cam, const float units)
{
    Vector3 pos = *player->currentPOS;

    // Calculate forward and right direction based on the camera's orientation
    Vector3 forward = Vector3Normalize(Vector3Subtract(cam->target, cam->position));
    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, cam->up));

    // Movement input
    if (IsKeyDown(KEY_W)) pos = Vector3Add(pos, Vector3Scale(forward, units));
    if (IsKeyDown(KEY_S)) pos = Vector3Subtract(pos, Vector3Scale(forward, units));
    if (IsKeyDown(KEY_A)) pos = Vector3Subtract(pos, Vector3Scale(right, units));
    if (IsKeyDown(KEY_D)) pos = Vector3Add(pos, Vector3Scale(right, units));
    if (IsKeyDown(KEY_SPACE)) pos.y += units;
    if (IsKeyDown(KEY_LEFT_CONTROL)) pos.y -= units;

    // Update the player's position
    *player->currentPOS = pos;

    // Also update the camera to follow the player
    cam->position = pos;
    cam->target = Vector3Add(pos, (Vector3){0, 0, 1}); // Look slightly forward
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

void drawDirections()
{
        DrawCube((Vector3){-100,0,1000}, 100, 100, 100, RED); // NORTH
        DrawCube((Vector3){-100,100,1000}, 100, 100, 100, RED); // NORTH
        DrawCube((Vector3){0,0,1000}, 100, 100, 100, RED); // NORTH
        DrawCube((Vector3){100,100,1000}, 100, 100, 100, RED); // NORTH
        
        DrawCube((Vector3){0,0,-1000}, 100, 100, 100, GREEN); // SOUTH
        DrawCube((Vector3){-1000,0,0}, 100, 100, 100, BLUE); // WEST
        DrawCube((Vector3){1000,0,0}, 100, 100, 100, YELLOW); // EAST
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
