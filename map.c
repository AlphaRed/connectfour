#include"common.h"

// Setup map tiles to tile array
void setupTiles(SDL_Rect t[], int num)
{
    for(int i = 0; i < num; i++)
    {
        t[i].x = (i % 4) * TILE_SIZE; // four tiles per row
        t[i].y = (i / 4) * TILE_SIZE; // four tiles per column
        t[i].w = TILE_SIZE;
        t[i].h = TILE_SIZE;
    }
}