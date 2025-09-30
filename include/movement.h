#pragma once
#include "game.h"

void MovePlayer(Player *player, const float units)
{
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
        player->currentPOS->x -= units;
    }
    if (IsKeyDown(KEY_D))
    {
        player->currentPOS->x += units;
    }
}

bool setPOS(Player* player, Vector3* pos)
{
    player->currentPOS = pos;
}
bool setPOS(Player* player, Vector3 pos)
{
    player->currentPOS->x = pos.x;
    player->currentPOS->y = pos.y;
    player->currentPOS->z = pos.z;
}
bool setPOS(Player* player, float x, float y, float z)
{
    player->currentPOS->x = x;
    player->currentPOS->y = y;
    player->currentPOS->z = z;
}