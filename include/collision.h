#pragma once
#include "render.h"
#define COLLISION_TOUCH_DIST 0.025f


// Use as: cam, rl.pos, default size
bool is_collision(Vector3 u, Vector3 v, float radius)
{
    return Vector3Distance(u,v) <= radius+0.01f;
}

//Apply collision to ever renderlist object, but ideally change to just nearby
void apply_rl_collisions(RenderList* rl, Vector3* object_pos)
{
    for (size_t i = 0; i < rl->capacity; i++)
    {
        Vector3 block = rl->positions_array[i];
        Vector3 incoming_object = *object_pos;
        
        float dist = Vector3Distance(block, incoming_object);
        float radius = DEFAULT_BLOCK_SIZE;
        
        if (dist >= radius)
        {
            continue;
        
        }
        Vector3 dir = Vector3Normalize(Vector3Subtract(incoming_object, block));
        float pushback = radius - dist;
        // As the distance decreases, less pushback is needed, hence the scale
        *object_pos = Vector3Add(incoming_object, Vector3Scale(dir, pushback));
    }
}

