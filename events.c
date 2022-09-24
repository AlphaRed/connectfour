#include"common.h"
#include "events.h"

int checkGameEvents(SDL_Event e, Cursor_t *c)
{
    if(e.type == SDL_QUIT)
        return 0;
    else if(e.type == SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                return 0;
                break;
            case SDLK_LEFT:
                c->x -= 32;
                break;
            case SDLK_RIGHT:
                c->x += 32;
                break;
            case SDLK_SPACE:
                setPiece(board, c);
                changeTurn(&turn);
                break;
            default:
                break;
        }
        return 1;    
    }
}

int checkMenuEvents(SDL_Event e, Cursor_t *c)
{
    if(e.type == SDL_QUIT)
        return 0;
    else if(e.type == SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_RETURN:
                if(c->y == 305) // Start
                    return 2;
                else if(c->y == 355) // Exit
                    return 0;
                break;
            case SDLK_DOWN:
                c->y += 50;
                break;
            case SDLK_UP:
                c->y -= 50;
                break;
            default:
                break;
        }
        return 1;    
    }
}

void checkMCursorBounds(Cursor_t *c)
{
    // wraps the cursor around the menu
    if(c->y > 355) // 305 + 50
    {
        c->y = 305;
    }   
    else if(c->y < 305)
    {
        c->y = 355;
    }
}

void checkGCursorBounds(Cursor_t *c)
{
    // wraps the cursor around the board
    if(c->x > 342)
    {
        c->x = 150;
    }   
    else if(c->x < 150)
    {
        c->x = 342;
    }
}

void setPiece(int array[7][6], Cursor_t *c)
{
    int num;
    // find where the cursor is
    // check the lowest free space in the column
    // set the free space
    switch (c->x)
    {
    case FIRST:
        num = checkColumn(0, array);
        setRow(0, num);
        break;
    case SECOND:
        num = checkColumn(1, array);
        setRow(1, num);
        break;
    case THIRD:
        num = checkColumn(2, array);
        setRow(2, num);
        break;
    case FOURTH:
        num = checkColumn(3, array);
        setRow(3, num);
        break;
    case FIFTH:
        num = checkColumn(4, array);
        setRow(4, num);
        break;
    case SIXTH:
        num = checkColumn(5, array);
        setRow(5, num);
        break;
    case SEVENTH:
        num = checkColumn(6, array);
        setRow(6, num);
        break;
    default:
        break;
    }
}

void changeTurn(Turnstate *t)
{
    if(*t == PLAYER)
        *t = CPU;
    else if(*t == CPU)
        *t = PLAYER;
}

int checkColumn(int n, int array[7][6])
{
    int row;
    for(int i = 0; i < 6; i++)
    {
        printf("Checking row %d\n", i);
        if(array[n][i] != 0)
        {
            printf("Row %d is not empty\n", i);
            row = i - 1;
            return row;
        }
        else
            row = i;
    }
    return row;
}

void setRow(int n, int r)
{
    if(turn == PLAYER)
        board[n][r] = 1;
    else if(turn == CPU)
        board[n][r] = 2;
}

int checkWin()
{
    // check horizontals
    // check verticals
    // check diagonals
}