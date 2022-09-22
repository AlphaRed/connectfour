#ifndef EVENTS_H
#define EVENTS_H

#define UP      0
#define LEFT    1
#define DOWN    2
#define RIGHT   3

int checkGameEvents(SDL_Event e, Cursor_t *c);
int checkMenuEvents(SDL_Event e, Cursor_t *c);
void checkMCursorBounds(Cursor_t *c);
void checkGCursorBounds(Cursor_t *c);

#endif