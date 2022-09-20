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
        window = SDL_CreateWindow("Beverley", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

// In this file for now, will move it elsewhere eventually

FILE *openTextFile(char *filename)
{
    FILE *f = fopen(filename, "r");

    if(f == NULL)
    {
        printf("Failed to load text file, %s\n", filename);
        return NULL;
    }
    else
        return f;
}

int loadTextFile(FILE *f, TextStruct *t)
{
    char tempLoad[MAX_CHARS] = {0};
    char num[5] = {0};
    
    fgets(num, 5, f);
    t->string1Len = strtol(num, NULL, 10);
    //printf("Length1: %d\n", t->string1Len);
    fgets(t->string1, MAX_CHARS, f);
    //printf("String1: %s\n", t->string1);
    fgets(num, 5, f);
    t->string2Len = strtol(num, NULL, 10);
    //printf("Length2: %d\n", t->string2Len);
    fgets(t->string2, MAX_CHARS, f);
    //printf("String2: %s\n", t->string2);
    return 0;
}

void closeTextFile(FILE *f)
{
    fclose(f);
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