#include"common.h"
#include "system.h"
#include "gfx.h"

int initWindow()
{
    window = NULL;
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL failed to initialize: %s\n", SDL_GetError());
        return 1;
    }
    else
        window = SDL_CreateWindow("Connect Four", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    return 0;
}

int initRenderer()
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        printf("Renderer failed to be created: %s\n", SDL_GetError());
        return 1;
    }
    return 0;
}

int initIMG()
{
    if(IMG_Init(IMG_INIT_PNG) < 0)
    {
        printf("SDL_Image library failed to initialize: %s", IMG_GetError());
        return 1;
    }
    return 0;
}

int initSDL()
{
    if(initWindow())
    {
        printf("initWindow failed.\n");
        return 1;
    }
    
    if(initRenderer())
    {
        printf("initRenderer failed.\n");
        return 1;
    }

    if(initIMG())
    {
        printf("initIMG failed.\n");
        return 1;
    }
    return 0;
}

void cleanup()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

SDL_Rect initTile(int x, int y, int w, int h)
{
    SDL_Rect tileRect;
    tileRect.x = x;
    tileRect.y = y;
    tileRect.w = w;
    tileRect.h = h;

    return tileRect;
}

int calculateFPS(int currentTicks)
{
    int fps = 0;
    int deltaTicks = SDL_GetTicks() - currentTicks;
        
    if(deltaTicks > 0)
        fps = 1000 / deltaTicks;
        
    if(fps > MAX_FPS)
    {
        int delay_time = (1000 / MAX_FPS) - deltaTicks;
        SDL_Delay(delay_time);
        // check again to see that it is fixed
        deltaTicks = SDL_GetTicks() - currentTicks;
        fps = 1000 / deltaTicks;
    }
    return fps;
}

void loadResources()
{
    bg = loadImage("art/bg.png");
    if(bg == NULL)
        printf("BG image failed to load.\n");
    
    tiles = loadImage("art/tiles.png");
    if(tiles == NULL)
        printf("Tiles image failed to load.\n");
    
    font = loadImage("art/font-ascii.png");
    if(font == NULL)
        printf("Font image filed to load.\n");
}