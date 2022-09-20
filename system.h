#ifndef SYSTEM_H
#define SYSTEM_H

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *bg;
extern SDL_Texture *tiles;
extern SDL_Texture *font;



int initSDL();
void cleanup();
SDL_Rect initTile(int x, int y, int w, int h);
int calculateFPS(int currentTicks);
void loadResources();

// to be moved elsewhere
FILE *openTextFile(char *filename);
int loadTextFile(FILE *f, TextStruct *t); 
void closeTextFile(FILE *f);

#endif