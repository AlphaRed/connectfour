#include "common.h"
#include "events.h"
#include "gfx.h"
#include "system.h"
#include "map.h"

// some things were meant to be global
SDL_Window *window;
SDL_Renderer *renderer;
Gamestate gs = MENU;
Turnstate turn;
int board[BOARD_WIDTH][BOARD_HEIGHT];
int win;
// resources
SDL_Texture *bg;
SDL_Texture *tiles;
SDL_Texture *font;
Mix_Music   *menuMusic;

SDL_Rect fontTiles[FONT_NUM];
SDL_Rect tileIndex[TILE_NUM];
int levelMap[MAX_MAP_SIZE][MAX_MAP_SIZE];
int heightMap[MAX_MAP_SIZE][MAX_MAP_SIZE];

int main(int argc, char *args[])
{    
    // SDL setup
    if(initSDL())
    {
        printf("initSDL failed.\n");
        return 1;
    }

    // Load in images and tiles
    loadResources();
    setupFontTiles(fontTiles, FONT_NUM); // move this?
    setupTiles(tileIndex, TILE_NUM);
    clearBoard();

    Cursor_t menuCursor;
    menuCursor.imgIndex = 4;
    menuCursor.x = 5;
    menuCursor.y = 305;

    Cursor_t gameCursor;
    gameCursor.imgIndex = 3;
    gameCursor.x = 150;
    gameCursor.y = 90;

    menuMusic = Mix_LoadMUS("sound/nes_07-simple.wav");
    if(menuMusic == NULL)
    {
        printf("Could not load menu music: %s\n", Mix_GetError());
        SDL_Delay(1000);
        return 1;
    }
    Mix_PlayMusic(menuMusic, -1);

    int quit = 1;
    SDL_Event e;
    int current_ticks;
    int fps_counter = 0;
    int renderTicks = 0;
    win = 0;

    // Game loop
    while(quit)
    {
        current_ticks = SDL_GetTicks();

        // Input
        SDL_WaitEvent(&e); // seems to work better than PollEvent
        if(gs == GAME)
        {
            quit = checkGameEvents(e, &gameCursor);
            if(quit == 2)
            {
                gs = MENU;
                // reset stuff
                clearBoard();
                win = 0;
            }
        }
        else if(gs == MENU)
        {
            quit = checkMenuEvents(e, &menuCursor);
            if(quit == 2)
            {
                gs = GAME;
                turn = PLAYER; // start as the player for now...
            }     
        }

        // Logic
        if(gs == GAME)
        {
            checkGCursorBounds(&gameCursor);
            win = checkWin();
        }
        else if(gs == MENU)
        {
            checkMCursorBounds(&menuCursor);
        }

        // Render
        renderTicks = SDL_GetTicks();

        if(gs == GAME)
        {
            blitImage(bg, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1); // clear bg to black      
            drawBoard(tiles);
            drawCursor(gameCursor, tiles);
            drawTurn(turn);
            drawPieces(board, tiles);
            drawWin(win);
        }
        else if(gs == MENU)
        {
            blitImage(bg, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1); // clear bg to black
            drawMenu(tiles);
            drawCursor(menuCursor, tiles);
        }

        drawFPS(fps_counter);
        SDL_RenderPresent(renderer);
        fps_counter = calculateFPS(current_ticks);
    }

    Mix_HaltMusic();
    cleanup();
    return 0;
}