#ifndef EVENTS_H
#define EVENTS_H

#define UP      0
#define LEFT    1
#define DOWN    2
#define RIGHT   3

int checkGameEvents(SDL_Event e);
int checkMenuEvents(SDL_Event e);
void moveCursor(int dir, MapCursor *c);

#endif