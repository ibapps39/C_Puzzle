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
    Vector3* velocity;         // Store velocity vector
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

// Camera related functions
void InitCamera(Camera3D *camera, const CameraSettings *cameraSettings);
void CameraTests(Camera *camera);
void GetCameraProjectionInfo(Camera *camera);

// Game Update and Draw functions
void UpdateGame(void);
void UpdatePlayerCAM(Player *player, Camera3D *playerCamera);
void DrawGame(void);
void CheckCollisions(void);
float playersDist(const Player *player, const Player *opponent);


// Level Functions

// Drawing Functions
void DrawPlayerScore(const Player *player, const Camera3D *camera);


// Player Movement and Interaction
bool currentKey(KeyboardKey k); 
void MoveCamera(Camera3D *camera);
void MovePlayer(Player *player, const float units);
void PlayerJump(Player *player, const float jumpHeight);
void GetPlayerInfo(const Player *player);
void DrawCameraInfo(const Camera3D *camera, const Player *player);
void CameraInfo(Camera3D *camera);
void UpdatePlayerCamera(Player *player);


// Score and Scoring
void incrementPoints(Player *player, double points);
void animatedScored(Player* player, Camera* cam);

//Set Functions
// bool setPOS(Player* player, Vector3* pos);
// bool setPOS(Player* player, Vector3* pos));
bool setPOS(Player* player, float x, float y, float z);
bool setVelocity(Player* player, Vector3* v);
bool setCamera(Player* player, Camera3D* Camera3D);
bool setName(Player* player, const char* name);
bool setScore(Player* player, double score);


void debugDisplay(Player player, Camera* camera);

void UpdatePlayerVelocity(Player *player);
