#pragma once
#define ROOMA_CELLS_LONG 10
#define ROOMA_CELLS_WIDE 10
#define ROOMA_CELLS_SIZE 10
#include "game.h"

struct ROOM
{
    int* room_map;
    size_t  room_length;
    size_t  room_width;
    size_t  room_height;
    Color   wall_color;
    float     room_cell_size;
};
typedef struct ROOM ROOM;

void initRoomZERO(ROOM* room)
{
    room->room_map          = NULL;
    room->room_length       = 0;
    room->room_width        = 0;
    room->room_height       = 0;
    room->wall_color        = (Color){0};
    room->room_cell_size    = 0.0f;
}
void initRoom(ROOM* room,
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

// void LoadRoom(Vector3 origin, int* room)
// {
// int ROOM_WIDTH = r
// for (size_t ROWS = 0; ROWS < ROOM_WIDTH; ROWS++)
// {
//     /* code */
// }


//     for (int row = 0; row < ROOMA_CELLS_LONG; row++)
//     {
//         int column = 0;
//         while (column < ROOMA_CELLS_WIDE)
//         {
//             int i = row * ROOMA_CELLS_WIDE + column;

//             // Skip empty row cells
//             if (roomA[i] == 0) { column++; continue; }

//             // Found start of a solid run
//             int runStart = column;
//             while (column < ROOMA_CELLS_WIDE && roomA[row * ROOMA_CELLS_WIDE + column] == 1)
//                 column++;
//             int runLength = column - runStart;

//             // Compute the center position of the run
//             Vector3 pos = {
//                 origin.x + (runStart + runLength / 2.0f - 0.5f) * ROOMA_CELLS_SIZE,
//                 origin.y,
//                 origin.z + row * ROOMA_CELLS_SIZE
//             };
            
//             // Draw one long cube
//             DrawCube(
//                 pos,
//                 runLength * ROOMA_CELLS_SIZE,
//                 ROOMA_CELLS_SIZE*10,
//                 ROOMA_CELLS_SIZE,
//                 wallColor
//             );
//             // DrawCubeWires(
//             //     pos,
//             //     runLength * ROOMA_CELLS_SIZE,
//             //     ROOMA_CELLS_SIZE*10,
//             //     ROOMA_CELLS_SIZE,
//             //     (Color){(unsigned)255-wallColor.r, (unsigned)255-wallColor.g, (unsigned)255-wallColor.b, 255}
//             // );
//         }
//     }
// }
// int getRoomRow(int* room, size_t size)
// {
//     int before = 1;
//     int after = 1;
// for (size_t i = 0; i < size; i++)
// {
    
// }
// }
// void LoadRoomB(Vector3 pos)
// {
//     int* roomB ={
//     1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//     1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
//     1,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,
//     1,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,
//     1,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,
//     1,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,
//     1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
// };
// size_t size = sizeof(*roomB)/sizeof(roomB[0]);

// for (size_t i = 0; i < size_t; i++)
// {
//     if (roomB[i] == 0) continue;
//     DrawCube()
// }

// }

