#pragma once
#include "game.h"
#include "render.h"

typedef enum block_type
{
    BASE,       // Squares
    RAMP,       // Triangle
    BRIDGE,     // Rectangle
} BLOCK_TYPE;
typedef struct block
{
    BLOCK_TYPE type;
    Vector3 center_point; // Where the reticle places the entire shape, tether
    Vector3* vertices;
} BLOCK;

// BLOCK get_base_block(Vector3* placement_point)
// {
    
// }