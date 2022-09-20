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
// resources
SDL_Texture *bg;
SDL_Texture *tiles;
SDL_Texture *font;

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

    int quit = 1;
    SDL_Event e;
    int current_ticks;
    int fps_counter = 0;
    int renderTicks = 0;

    // Game loop
    while(quit)
    {
        current_ticks = SDL_GetTicks();

        // Input
        SDL_PollEvent(&e);
        if(gs == GAME)
        {
            quit = checkGameEvents(e);
        }
        else if(gs == MENU)
        {
            quit = checkMenuEvents(e);
            if(quit == 2)
            {
                gs = GAME;
                // maybe add a new function to setup variables for start of game
                turn = P_MOVE;
            }     
        }

        // Logic
        if(gs == GAME)
        {
        }

        // Render
        renderTicks = SDL_GetTicks();

        if(gs == GAME)
        {
            blitImage(bg, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1); // clear bg to black      
            drawBoard(tiles);
            //drawMapCursor(c.x, c.y, cam.offsetX, cam.offsetY, c.img); // draw cursor after map
        }
        else if(gs == MENU)
        {
            blitImage(bg, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1); // clear bg to black
            drawMenu();
        }

        drawFPS(fps_counter);
        SDL_RenderPresent(renderer);
        fps_counter = calculateFPS(current_ticks);
    }

    cleanup();
    return 0;
}