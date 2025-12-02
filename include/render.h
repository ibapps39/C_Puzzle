#pragma once

#include "game.h"
#include <memory.h>

#define ADD_BLOCK_DIST_MAX 2.00
#define DEFAULT_BLOCK_SIZE 2
#define MAX_CUBES 5
#define MAX_RENDER_LIST_ELEMENTS 3
#define INVALID_POSITION \
    (Vector3) { INFINITY, INFINITY, INFINITY }
#define DEFAULT_BLOCK_COLOR PINK

/// @brief Vector3* should be treated and seen as an array. Vector3's because its most geomtry agnostic/generic.
typedef struct RenderList
{
    // Vector3 positions[MAX_CUBES], maybe only allow 3,4?
    Vector3* positions_array;
    unsigned int block_index;
    unsigned int capacity;
    bool overflow_flag;
} RenderList;

void rl_init(RenderList *rl, const int capacity)
{
    rl->positions_array = NULL;
    rl->positions_array = malloc(sizeof(RenderList) * capacity);
    rl->block_index = 0;
    rl->capacity = capacity;
    rl->overflow_flag = 0;
}

void rl_free(RenderList *rl)
{
    free(rl->positions_array);
    rl->positions_array = NULL;
    rl->block_index = 0;
    rl->capacity = 0;
    rl->overflow_flag = 0;
}
void rl_uninit_last_index(RenderList *rl)
{
    if (!rl || !(rl->positions_array))
        return;

    for (size_t i = 0; i < rl->block_index; i++)
    {
        rl->positions_array[i] = INVALID_POSITION;
    }
}

void rl_uninit_index(RenderList *rl, int i)
{
    if (!rl || !(rl->positions_array) || !(rl->positions_array+i)) return; 
    rl->positions_array[i] = INVALID_POSITION;
}
// get what the cam is looking at, place it direction_units away
Vector3 get_placement_vector(Camera3D* cam, float distance_units)
{
    Vector3 dir = Vector3Subtract(cam->target, cam->position);
    dir = Vector3Normalize(dir);
    dir = Vector3Add(cam->target, Vector3Scale(dir, distance_units));
    return dir;
}

// Vector3Equals(v, INVALID_POSITION) seems to always return 1
int is_invalid(Vector3 v)
{
    return v.x == INVALID_POSITION.x || v.y == INVALID_POSITION.y || v.z == INVALID_POSITION.z;
}
int is_placeable(RenderList* rl, Vector3* v)
{
    for (size_t i = 0; i < rl->capacity; i++)
    {
        if (Vector3Distance(rl->positions_array[i], *v) <= DEFAULT_BLOCK_SIZE)
        {
            return 0;
        }
    }
    return 1;
}

bool add_block_to_list(RenderList *rl, Vector3* v)
{
    int size = rl->capacity;
    int current_index = rl->block_index;

    if (is_invalid(*v) || is_placeable(rl, v) == 0)
    {
       return false;
    }
    
    if (current_index >= size)
    {
        rl->block_index = 0;
        rl->overflow_flag = true;
    }

    rl->positions_array[current_index] = *v;
    rl->block_index += 1;
    return true;
}

/// @brief Renders everything in r, an array of user defined points
/// @param r
void rl_draw_list(Vector3 *r, int capacity)
{
    for (size_t i = 0; i < capacity; i++)
    {
        if (is_invalid(r[i]))
        {
            continue;
        }
        // check enum, call rendering function
        DrawCube(r[i], DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE, YELLOW);
        DrawCubeWires(r[i], DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE + 1, BLACK);
    }
}

void draw_reticle(Vector3* pos)
{
    DrawCubeWires(*pos, DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE, BLACK);
}
