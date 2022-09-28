#ifndef EVENTS_H
#define EVENTS_H

#define FIRST   150
#define SECOND  150 + 32
#define THIRD   150 + 32 + 32
#define FOURTH  150 + 32 + 32 + 32
#define FIFTH   150 + 32 + 32 + 32 + 32
#define SIXTH   150 + 32 + 32 + 32 + 32 + 32
#define SEVENTH 150 + 32 + 32 + 32 + 32 + 32 + 32

extern Turnstate turn;
extern int board[7][6];
extern int win;

int checkGameEvents(SDL_Event e, Cursor_t *c);
int checkMenuEvents(SDL_Event e, Cursor_t *c);
void checkMCursorBounds(Cursor_t *c);
void checkGCursorBounds(Cursor_t *c);
int setPiece(int array[7][6], Cursor_t *c);
void changeTurn(Turnstate *t);
int checkColumn(int n, int array[7][6]);
int setRow(int n, int r);
void debugBoard();
int checkWin();
int checkHorizontal(int n);
int checkVertical(int n);
int checkDiagonalLeft(int n);
int checkDiagonalRight(int n);
void clearBoard();

#endif