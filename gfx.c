#include "common.h"
#include "gfx.h"

SDL_Texture *loadImage(char *filename)
{
    SDL_Texture *t = NULL;
    SDL_Surface *img = IMG_Load(filename);
    if(!img)
    {
        printf("Image failed to load: %s\n", IMG_GetError());
        return NULL;
    }
    t = SDL_CreateTextureFromSurface(renderer, img);
    return t;
}

void blitImage(SDL_Texture *image, int x, int y, int w, int h, int s)
{
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = w * s;
    destRect.h = h * s;

    SDL_RenderCopy(renderer, image, NULL, &destRect);
}

void blitTile(SDL_Texture *image, int x, int y, int w, int h, SDL_Rect destRect)
{
    SDL_Rect srcRect;
    srcRect.x = x;
    srcRect.y = y;
    srcRect.w = w;
    srcRect.h = h;

    SDL_RenderCopy(renderer, image, &srcRect, &destRect);
}


// TO DO: move with other text related functions to new file
void drawLetter(char c, int x, int y, int s)
{
    //int x = ((c - 32) % 8) * 8; // ASCII starts at char = 32, font width = 8px
    //int y = ((c - 32) / 16) * 12; // ASCII starts at char = 32, num of chars in width = 16, font height = 12px

    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = 8 * s;
    destRect.h = 12 * s;
    
    int fontIndex = c - 32; // ASCII starts at character #32
    blitTile(font, fontTiles[fontIndex].x, fontTiles[fontIndex].y, fontTiles[fontIndex].w, fontTiles[fontIndex].h, destRect);
}

// TO DO: move with other text related functions to new file
void setupFontTiles(SDL_Rect f[], int num)
{
    for(int i = 0; i < num; i++)
    {
        f[i].x = (i % 16) * 8;
        f[i].y = (i / 16) * 12;
        f[i].w = 8;
        f[i].h = 12;
    }
}

// TO DO: move with other text related functions to new file
void drawString(char *string, int y) // this can possibly be discarded...
{
    // only draw a string max length of 40 characters! (1,280 res width / (8 * 4) don't forget the upscale of 4x
    // technically can be drawn closer due to the way I've drawn the pixel art!
    int x = 0;
    int len = strlen(string);
    if(len > MAX_LEN)
        len = MAX_LEN; // max out at 40

    for(int i = 0; i < len; i++)
    {
        drawLetter(string[i], x, y, 4);
        if(string[i] == 'i')
            x += ((FONT_WIDTH - 4) * 4); // more for i...maybe l?
        else
            x += ((FONT_WIDTH - 2) * 4); // Minus two for distancing...kerning(?)
    }
}

// TO DO: move with other text related functions to new file
void drawFPS(int fps)
{
    char c;
    int x;

    drawLetter('F', 1000, 0, 1);
    drawLetter('P', 1008, 0, 1);
    drawLetter('S', 1016, 0, 1);
    drawLetter(':', 1024, 0, 1);
    drawLetter(' ', 1032, 0, 1);

    if(fps > 1000)
        fps = 1000;
    
    for(int i = 0; i < 4; i++)
    {
        c = (fps % 10) + 48; // need 48 to convert to ASCII numbers
        fps = fps / 10;
        x = 1064 - (i * 8);
        drawLetter(c, x, 0, 1);
    }   
}

// TO DO: move with other text related functions to new file
void drawAnimatedLine(LineStruct *L, int currentTicks, CursorStruct *C)
{
    int drawX = L->x;
    for(int i = 0; i < L->currentFrame; i++)
    {
        char c = L->string[i];
        drawLetter(c, drawX, L->y, L->s);
        if(c == 'i')
            drawX += ((FONT_WIDTH - 4) * L->s); // more for i...maybe l?
        else
            drawX += ((FONT_WIDTH - 2) * L->s); // Minus two for distancing...kerning(?)            
    }
    int deltaTicks = currentTicks - L->lastTick;
    if(deltaTicks > L->delay)
    {
        L->currentFrame++;
        if(L->currentFrame > L->length)
            L->currentFrame = L->length; // prevent out of bounds
        L->lastTick = currentTicks;
        C->x += ((FONT_WIDTH - 2) * L->s);
        if(C->x > drawX)
            C->x = drawX;
    }
}

// TO DO: move with other text related functions to new file
void drawCursor(CursorStruct *C, int currentTicks) // TO DO: add a function for changing location of cursor
{
    char c;
    if(C->currentFrame == 1)
        c = C->c2;
    else
        c = C->c1;
    drawLetter(c, C->x, C->y, C->s);
    int deltaTicks = currentTicks - C->lastTick;
    if(deltaTicks > C->delay)
    {
        C->currentFrame++;
        if(C->currentFrame > 1)
            C->currentFrame = 0; // I think there's a better way to do this but whatever
        C->lastTick = currentTicks;
    }
}

// TO DO: move with other text related functions to new file
void drawParagraph(TextStruct *T, int currentTicks, CursorStruct *C)
{
    int drawX = 10;
    int drawY = 10;
    int scale = 4;
    int delay = 450;

    for(int i = 0; i <= T->currentLetter; i++)
    {
        char c = T->string1[i];
        drawLetter(c, drawX, drawY, scale);
        if(c == 'i')
            drawX += ((FONT_WIDTH - 4) * scale); // more for i...maybe l?
        else
            drawX += ((FONT_WIDTH - 2) * scale); // Minus two for distancing...kerning(?)
    }
                 
    int deltaTicks = currentTicks - T->lastTick;
    if(deltaTicks > delay)
    {
        T->currentLetter++;
        if(T->currentLetter > T->string1Len)
            T->currentLetter = T->string1Len;
        T->lastTick = currentTicks;
        C->x += ((FONT_WIDTH - 2) * scale);
        if(C->x > drawX)
            C->x = drawX;
    }
}

void drawTile(SDL_Texture *t, int index, int x, int y, int s)
{
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = TILE_SIZE * s;
    destRect.h = TILE_SIZE * s;
    
    blitTile(t, tileIndex[index].x, tileIndex[index].y, tileIndex[index].w, tileIndex[index].h, destRect);
}

void drawBoard(SDL_Texture *t)
{
    int xOffset = 150;
    int yOffset = 130;
    for(int i = 0; i < MAX_ROWS; i++)
    {
        for(int j = 0; j < MAX_COLUMNS; j++)
        {
            drawTile(t, 0, (j * TILE_SIZE * TILE_SCALE) + xOffset, (i * TILE_SIZE * TILE_SCALE) + yOffset, TILE_SCALE);
        }
    }
}

void drawMapCursor(int x, int y, int offsetX, int offsetY, SDL_Texture *img)
{
    int h = heightMap[x][y];
    int cx = (x - y) * 64 + offsetX;
    int cy = (x + y) * 32 + offsetY - (TILE_SIZE * 2 * h);
    blitImage(img, cx, cy, TILE_SIZE, TILE_SIZE, 4);
}

void drawMenu()
{
    drawString("Connect Four", 50);
    drawString("Start?", 150);
}

void drawMovement()
{
    
}