#pragma once
#include "render.h"

typedef struct CollisionList
{
    RenderList* rl;
} CollisionList;

// anything with a distance of center is repelled, return the opposite vector
void collision_cube(Vector3 cube_pos)
{
    
}