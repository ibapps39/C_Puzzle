#pragma once
#include "game.h"
#define ADD_BLOCK_DIST_MAX 5.00
#define DEFFAULT_BLOCK_SIZE 10.00
#define MAX_CUBES 5

/// @brief Vector3* should be treated and seen as an array. Vector3's because its most geomtry agnostic/generic.
typedef struct
{
    Vector3* positions_array;
    int last_modified_index;
} RenderList;

/// @brief Create an "array" but let initial values default to NULL rather than (Vector3){0}s.
/// @param rl - The RenderList to be modified.
/// @param max_elements - The max amount of elements that can be added to the positions_array.
void init_render_list(RenderList* rl, const int max_elements)
{
    rl->positions_array = malloc(sizeof(RenderList)*max_elements);
    rl->positions_array = 0;
}
// assumes fixed sized array
void addBlock(Camera3D *cam, Vector3 *list, int* current_index, const size_t allocated_size)
{
    int size = (int)allocated_size;
    float max_dist = (float)ADD_BLOCK_DIST_MAX;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector3 pos = Vector3Subtract(cam->target, cam->position);

        if (Vector3Length(pos) > max_dist)
        {
            pos = Vector3Scale(Vector3Normalize(pos), max_dist);
        }
        // wrap around to first element if at current size
        if (*current_index >= size)
        {
            *current_index = 0;
        }

        list[*current_index] = pos;
        *(current_index) = *(current_index) + 1;
    }
}

/// @brief Renders everything in r, a renderlist array
/// @param r
void ClickArrayRender(Vector3 *r, int size)
{
    for (size_t i = 0; i < size; i++)
    {
        // printf("size: %i\n", size);
        DrawCube(r[i], DEFFAULT_BLOCK_SIZE, DEFFAULT_BLOCK_SIZE, DEFFAULT_BLOCK_SIZE, YELLOW);
        DrawCubeWires(r[i], DEFFAULT_BLOCK_SIZE, DEFFAULT_BLOCK_SIZE, DEFFAULT_BLOCK_SIZE + 1, BLACK);
    }
}