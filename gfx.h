#ifndef GFX_H
#define GFX_H

#define FONT_WIDTH  8
#define MAX_LEN     32
#define MAX_ROWS    6
#define MAX_COLUMNS 7

extern SDL_Renderer *renderer;
extern SDL_Texture *font;

SDL_Texture *loadImage(char *filename);
void blitImage(SDL_Texture *image, int x, int y, int w, int h, int s);
void blitTile(SDL_Texture *image, int x, int y, int w, int h, SDL_Rect destRect);
void drawLetter(char c, int x, int y, int s);
void setupFontTiles(SDL_Rect f[], int num);
void drawString(char *string, int y);
void drawFPS(int fps);
void drawAnimatedLine(LineStruct *L, int currentTicks, CursorStruct *C);
void drawCursor(CursorStruct *C, int currentTicks);
void drawParagraph(TextStruct *T, int currentTicks, CursorStruct *C);
void drawTile(SDL_Texture *t, int index, int x, int y, int s);
void drawBoard(SDL_Texture *t);
void drawMapCursor(int x, int y, int offsetX, int offsetY, SDL_Texture *img);
void drawMenu();
void drawMovement();

#endif