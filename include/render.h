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

/// @brief Create an "array" but let initial values default to NULL rather than (Vector3){0}s.
/// @param rl The RenderList to be modified.
/// @param capacity The max amount of elements that can be added to the positions_array.
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

// void rl_uninit(RenderList* rl)
// {
//     if (!rl || !(rl->positions_array)) return;

//     memset(rl->positions_array, NULL, sizeof(Vector3) * rl->capacity);

//     rl->block_index = 0;
//     rl->overflow_flag = 0;
// }

// void rl_undo(RenderList* rl)
// {
//     if (!rl || !(rl->positions_array)) return;
//     rl->positions_array[rl->block_index] = INVALID_POSITION;
//     rl->block_index--;
// }
Vector3 getTarget(Camera3D *cam)
{
    return cam->target;
}

Vector3 get_placement_vector(Camera3D* cam, float distance_units)
{
    Vector3 dir = Vector3Subtract(cam->target, cam->position);
    dir = Vector3Normalize(dir);
    dir = Vector3Add(cam->target, Vector3Scale(dir, distance_units));
    return dir;
}

void addBlock(RenderList *rl, Vector3* v)
{
    int size = rl->capacity;
    int current_index = rl->block_index;

    if (current_index >= size)
    {
        rl->block_index = 0;
        rl->overflow_flag = true;
    }

    rl->positions_array[current_index] = *v;
    rl->block_index += 1;
}

/// @brief Renders everything in r, an array of user defined points
/// @param r
void click_add_to_list(Vector3 *r, int capacity)
{
    for (size_t i = 0; i < capacity; i++)
    {
        if (r[i].x == INVALID_POSITION.x || r[i].y == INVALID_POSITION.y || r[i].z == INVALID_POSITION.z)
        {
            continue;
        }
        // check enum, call rendering function
        DrawCube(r[i], DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE, YELLOW);
        DrawCubeWires(r[i], DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE + 1, BLACK);
    }
}
/// @brief Renders everything in the render list, render_list
/// @param render_list 
void draw_render_list(RenderList *render_list)
{
    for (size_t i = 0; i < render_list->capacity; i++)
    {
        const char *txt = TextFormat("render_list.positions_array[%i].x = %.2f\n, render_list.positions_array[%i].y = %.2f\n, render_list.positions_array[%i].z = %.2f", (i, render_list->positions_array[i]).x, i, (render_list->positions_array[i]).y, i, (render_list->positions_array[i]).z);
        DrawText(txt, 260, 230, 20, PURPLE);
    }
}

void draw_reticle(Vector3* pos)
{
    DrawCubeWires(*pos, DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE, BLACK);
}
