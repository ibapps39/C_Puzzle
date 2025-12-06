#pragma once
#include "game.h"
#include "render.h"
#include "collision.h"

//idk, maybe just rectangle?
#define DEFAULT_BASE_WIDTH 4
#define DEFAULT_BASE_HEIGHT 1
#define DEFAULT_BASE_LENGTH 4

// #define DEFAULT_BRIDGE_WIDTH
// #define DEFAULT_BRIDGE_HEIGHT
// #define DEFAULT_BRIDGE_LENGTH

// #define DEFAULT_RAMP_WIDTH
// #define DEFAULT_RAMP_HEIGHT
// #define DEFAULT_RAMP_LENGTH

typedef enum block_type
{
    Base,       // Squares / Square
    Ramp,       // Triangle
    Bridge,     // Rectangle
} block_type;

typedef struct block_whl
{
    float width;
    float height;
    float length;
} block_whl;

typedef struct block
{
    block_type type;
    Vector3 center_point; // Where the reticle places the entire shape, tether
    BoundingBox bbox;
    //BoundingBox* bboxes;
    //block
} Block;

Block get_base_block(Vector3* pos, float radius)
{
    Block block = {
        .type = Base,
        .center_point = *pos,
        .bbox = get_bbox_at(*pos, radius)
    };
    return block;
}
Block get_ramp_block(Vector3* pos, float radius)
{
    Block block = {
        .type = Ramp,
        .center_point = *pos,
        .bbox = get_bbox_at(*pos, radius)
    };
    return block;
}
Block get_bridge_block(Vector3* pos, float radius)
{
    Block block = {
        .type = Bridge,
        .center_point = *pos,
        .bbox = get_bbox_at(*pos, radius)
    };
    return block;
}