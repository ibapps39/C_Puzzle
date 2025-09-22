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




// Camera struct to store camera settings and label
typedef struct
{
    Camera3D camera;
    const char *cameraLabel;
} CameraName;

// Player data, including shape and score
typedef struct
{
    Vector3 playerPOS;
    PlayerShape playerBody;
    double playerScore;
    const char *playerName;
    Camera3D playerCamera;
    Vector3 previousPOS;       // Store previous position
    Vector3 velocity;          // Store velocity vector
    float collisionCooldown;   // Prevent multiple collisions in quick succession
} Player;

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

/ Camera related functions
void InitCamera(Camera3D *camera, const CameraSettings *cameraSettings);
void CameraTests(Camera *camera);
void GetCameraProjectionInfo(Camera *camera);

// Game Update and Draw functions
void UpdateGame(void);
void UpdatePlayerCAM(Player *player, Camera3D *playerCamera);
void DrawGame(void);
void CheckCollisions(void);
float playersDist(const Player *player, const Player *opponent);
adjustedMessage2D adjustMessage(const worldMessage *details);

// Level Functions
void DrawLevel(const Level *level);
void DrawLevels(Level (*levels)[5]);
void increaseLevelRadius(Level *level, float amount);
void increaseLevelsRadi(Level (*levels)[NUM_LEVELS], float amount);
// Draw Player
void DrawPlayer(const Player *player);


// Player Movement and Interaction
void MoveCamera(Camera3D *camera);
void MovePlayer(Player *player, const float units);
void PlayerJump(Player *player, const float jumpHeight);
void GetPlayerInfo(const Player *player);
void DrawCameraInfo(const Camera3D *camera, const Player *player);
void CameraInfo(Camera3D *camera);
void UpdatePlayerCamera(Player *player);

void DrawPlayerArms(const PlayerArms *arms, const Player *player);
void repulsePlayer(Player *player, Player *opponent, float repulse);
void repulsePlayersCollisions(Player *player, Player* players[NUM_PLAYERS], float repulse);
void swayCPU(Player *cpu, Vector3 *center, const float *baseRadius, const float *angle, const float swayAmp, const float swayFreq);

void displayPlayersDist(Player *player, Player *player2, Camera *cam);

// Score and Scoring
void incrementPoints(Player *player, double points);
void animatedScored(Player* player, Camera* cam);


void DrawPlayerScore(const Player *player, const Camera3D *camera);

void displayPlayerPoints(const worldMessage *wm);

void debugDisplay(Player player, Camera* camera);

void UpdatePlayerVelocity(Player *player);
void playersAnimatedScored(Player *players[NUM_PLAYERS], Camera *cam);
