#ifndef COMMON_H
#define COMMON_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH    256 * 2
#define SCREEN_HEIGHT   240 * 2
#define TILE_SIZE       8
#define TILE_SCALE      4
#define FONT_NUM        200
#define MAX_FPS         60
#define MAX_CHARS       30
#define MAX_MAP_SIZE    10
#define MAX_MAP_HEIGHT  3
#define TILE_NUM        4 * 4
#define BOARD_WIDTH     7
#define BOARD_HEIGHT    6

typedef enum {MENU, GAME} Gamestate;
typedef enum {PLAYER, CPU} Turnstate; // add in items and other states later on

typedef struct Cursor_t // could maybe make this a generic sprite/obj struct?
{
    int imgIndex;
    int x;
    int y;
} Cursor_t;

// TO DO MOVE THESE OUT AND USE EXTERN WHERE APPLICABLE
SDL_Rect fontTiles[FONT_NUM];
SDL_Rect tileIndex[TILE_NUM];

int levelMap[MAX_MAP_SIZE][MAX_MAP_SIZE];
int heightMap[MAX_MAP_SIZE][MAX_MAP_SIZE];

#endif