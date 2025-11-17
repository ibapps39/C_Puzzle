#pragma once
#include "render.h"
#define COLLISION_TOUCH_DIST 0.025f
typedef struct clVertex
{
    float x;
    float y;
    float z;
} clVertex;

// check the distance of only nearby nodes
// typedef struct CollisionNode
// {
//     clVertex* pos;
//     struct CollisionNode* left;
//     struct CollisionNode* right;
//     float dist_nearest_node;
// } CollisionNode;

// typedef struct CollisionTree
// {
//     CollisionNode* nodes;
// } CollisionTree;

// typedef struct CollisionList
// {
//     RenderList* rl;
    
// } CollisionList;


bool is_collision(Vector3 u, Vector3 v, float radius)
{
    return Vector3Distance(u, v) < radius;
}

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
        *object_pos = Vector3Add(*object_pos, Vector3Scale(dir, pushback));
    }
}
