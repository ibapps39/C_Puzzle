#pragma once
#define ROOMA_CELLS_LONG 10
#define ROOMA_CELLS_WIDE 10
#define ROOMA_CELLS_SIZE 10
#include "game.h"

typedef struct BASIC_ROOM
{
    int* map;
    Vector3* cells;
} basic_room;

struct ROOM
{
    int* room_map;
    size_t  room_length;
    size_t  room_width;
    size_t  room_height;
    Color   wall_color;
    float   room_cell_size;
};
typedef struct ROOM ROOM;

void init_room_ZERO(ROOM* room)
{
    room->room_map          = NULL;
    room->room_length       = 0;
    room->room_width        = 0;
    room->room_height       = 0;
    room->wall_color        = (Color){0};
    room->room_cell_size    = 0.0f;
}
void init_room(ROOM* room,
    int* room_map,
    size_t  room_length,
    size_t  room_width,
    size_t  room_height,
    Color   wall_color,
    float     room_cell_size)
{
    room->room_map          = room_map ;
    room->room_length       = room_length;
    room->room_width        = room_width;
    room->room_height       = room_height;
    room->wall_color        = wall_color;
    room->room_cell_size    = room_cell_size;
}

int roomA[ROOMA_CELLS_WIDE * ROOMA_CELLS_LONG] =
{
    1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1
};

// int* room_lvl =
// {
//     1,1,1,1,1,1,1,1,1,1,
//     1,0,0,0,0,0,0,0,0,1,
//     1,0,0,0,0,0,0,0,0,1,
//     1,0,0,0,0,0,0,0,0,1,
//     1,0,0,0,0,0,0,0,0,1,
//     1,0,0,0,0,0,0,0,0,1,
//     1,0,0,0,0,0,0,0,0,1,
//     1,0,0,0,0,0,0,0,0,1,
//     1,0,0,0,0,0,0,0,0,1,
//     1,1,1,1,1,1,1,1,1,1
// };
// void basic_room_init(basic_room* room, int* map)
// {
//     room->map = map;
//     size_t map_size = sizeof(*map)/sizeof(map[0]);
//     printf("%i", map_size);
// }
// void basic_room_to_rl(basic_room* lvl, RenderList* rl)
// {
   
// }