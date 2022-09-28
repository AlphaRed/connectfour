#include"common.h"
#include "events.h"

int checkGameEvents(SDL_Event e, Cursor_t *c)
{
    if(win == 0)
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
                    if(setPiece(board, c) > 0)
                        changeTurn(&turn);
                    break;
                case SDLK_RETURN:
                    debugBoard();
                    break;
                default:
                    break;
            }
            return 1;    
        }
    }
    else
    {
        if(e.type == SDL_QUIT)
            return 0;
        else if(e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_RETURN:
                    return 2;
                    break;
                default:
                    break;
            }
            return 1;
        }
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

int setPiece(int array[BOARD_WIDTH][BOARD_HEIGHT], Cursor_t *c)
{
    int num;
    int check = 0;
    // find where the cursor is
    // check the lowest free space in the column
    // set the free space
    switch (c->x)
    {
    case FIRST:
        num = checkColumn(0, array);
        check = setRow(0, num);
        break;
    case SECOND:
        num = checkColumn(1, array);
        check = setRow(1, num);
        break;
    case THIRD:
        num = checkColumn(2, array);
        check = setRow(2, num);
        break;
    case FOURTH:
        num = checkColumn(3, array);
        check = setRow(3, num);
        break;
    case FIFTH:
        num = checkColumn(4, array);
        check = setRow(4, num);
        break;
    case SIXTH:
        num = checkColumn(5, array);
        check = setRow(5, num);
        break;
    case SEVENTH:
        num = checkColumn(6, array);
        check = setRow(6, num);
        break;
    default:
        break;
    }

    if(check > 0) // check if something was set
        return 1;
    else
        return 0;
}

void changeTurn(Turnstate *t)
{
    if(*t == PLAYER)
        *t = CPU;
    else if(*t == CPU)
        *t = PLAYER;
}

int checkColumn(int n, int array[BOARD_WIDTH][BOARD_HEIGHT])
{
    int row;
    for(int i = 0; i < 6; i++)
    {
        //printf("Checking row %d\n", i);
        if(array[n][i] != 0)
        {
            //printf("Row %d is not empty\n", i);
            row = i - 1;
            return row;
        }
        else
            row = i;
    }
    return row;
}

int setRow(int n, int r)
{
    if(board[n][r] > 0)
        return 0;
    else
    {
        if(turn == PLAYER)
            board[n][r] = 1;
        else if(turn == CPU)
            board[n][r] = 2;
        
        return 1;
    }
}

void debugBoard()
{
    for(int i = 0; i < 6; i++) // checks
    {
        printf("%d %d %d %d %d %d %d\n", board[0][i], board[1][i], board[2][i], board[3][i], board[4][i], board[5][i],board[6][i]);
    }
}

int checkWin()
{
    int w = 0;
    // check horizontals
    for(int i = 0; i < 6; i++)
    {
        w = checkHorizontal(i);
        if(w == 1)
            return 1;
        else if(w == 2)
            return 2;
    }

    // check verticals
    for(int i = 0; i < 7; i++)
    {
        //printf("Checking row -> %d\n", i);
        w = checkVertical(i);
        if(w == 1)
            return 1;
        else if(w == 2)
            return 2;
    }

    // check diagonals
    for(int i = 0; i < 7; i++)
    {
        w = checkDiagonalLeft(i);
        if(w == 1)
            return 1;
        else if(w == 2)
            return 2;
    }

    for(int i = 0; i < 7; i++)
    {
        w = checkDiagonalRight(i);
        if(w == 1)
            return 1;
        else if(w == 2)
            return 2;
    }
    
    // all else fails
    return 0;
}

int checkHorizontal(int n)
{
    int count = 0;
    int token = 1; // set as one to start, doesn't matter really

    for(int i = 0; i < 7; i++)
    {
        if(token == board[i][n])
        {
            count++;
        }
        else
        {
            count = 1;
            token = board[i][n];
        }

        if(count > 3 & token > 0) // we don't care about empty slots
        {
            if(token == 1)
                return 1;
            else if(token == 2)
                return 2;
        }
    }
    return 0;
}

int checkVertical(int n)
{
    int count = 0;
    int token = 1; // set as one to start, doesn't matter really

    for(int i = 0; i < 6; i++)
    {
        if(token == board[n][i])
        {
            count++;
        }
        else
        {
            count = 1;
            token = board[n][i];
        }

        if(count > 3) // we don't care about empty slots
        {
            if(token == 1)
                return 1;
            else if(token == 2)
                return 2;
        }
    }
    return 0;
}

int checkDiagonalLeft(int n) // so disgusting, don't look please
{
    int count = 0;
    int token = 1; // set as one to start, doesn't matter really

    if(n == 0)
    {
        for(int i = 0; i < 4; i++)
        {
            if(token == board[i][2 + i])
            {
                count++;
            }
            else
            {
                count = 1;
                token = board[i][2 + i];
            }

            if(count > 3) // we don't care about empty slots
            {
                if(token == 1)
                    return 1;
                else if(token == 2)
                    return 2;
            }
        }
    }
    else if(n == 1)
    {
        for(int i = 0; i < 5; i++)
        {
            if(token == board[i][1 + i])
            {
                count++;
            }
            else
            {
                count = 1;
                token = board[i][1 + i];
            }

            if(count > 3) // we don't care about empty slots
            {
                if(token == 1)
                    return 1;
                else if(token == 2)
                    return 2;
            }
        }
    }
    else if(n == 2)
    {
        for(int i = 0; i < 6; i++)
        {
            if(token == board[i][i])
            {
                count++;
            }
            else
            {
                count = 1;
                token = board[i][i];
            }

            if(count > 3) // we don't care about empty slots
            {
                if(token == 1)
                    return 1;
                else if(token == 2)
                    return 2;
            }
        }
    }
    else if(n == 3)
    {
        for(int i = 0; i < 6; i++)
        {
            if(token == board[1 + i][i])
            {
                count++;
            }
            else
            {
                count = 1;
                token = board[1 + i][i];
            }

            if(count > 3) // we don't care about empty slots
            {
                if(token == 1)
                    return 1;
                else if(token == 2)
                    return 2;
            }
        }
    }
    else if(n == 4)
    {
        for(int i = 0; i < 5; i++)
        {
            if(token == board[2 + i][i])
            {
                count++;
            }
            else
            {
                count = 1;
                token = board[2 + i][i];
            }

            if(count > 3) // we don't care about empty slots
            {
                if(token == 1)
                    return 1;
                else if(token == 2)
                    return 2;
            }
        }
    }
    else if (n == 5)
    {
        for(int i = 0; i < 4; i++)
        {
            if(token == board[3 + i][i])
            {
                count++;
            }
            else
            {
                count = 1;
                token = board[3 + i][i];
            }

            if(count > 3) // we don't care about empty slots
            {
                if(token == 1)
                    return 1;
                else if(token == 2)
                    return 2;
            }
        }
    }
    
    return 0;
}

int checkDiagonalRight(int n) // so disgusting, don't look please
{
    int count = 0;
    int token = 1; // set as one to start, doesn't matter really

    if(n == 0)
    {
        for(int i = 0; i < 4; i++)
        {
            if(token == board[i][3 - i])
            {
                count++;
            }
            else
            {
                count = 1;
                token = board[i][3 - i];
            }

            if(count > 3) // we don't care about empty slots
            {
                if(token == 1)
                    return 1;
                else if(token == 2)
                    return 2;
            }
        }
    }
    else if(n == 1)
    {
        for(int i = 0; i < 5; i++)
        {
            if(token == board[i][4 - i])
            {
                count++;
            }
            else
            {
                count = 1;
                token = board[i][4 - i];
            }

            if(count > 3) // we don't care about empty slots
            {
                if(token == 1)
                    return 1;
                else if(token == 2)
                    return 2;
            }
        }
    }
    else if(n == 2)
    {
        for(int i = 0; i < 6; i++)
        {
            if(token == board[i][5 - i])
            {
                count++;
            }
            else
            {
                count = 1;
                token = board[i][5 - i];
            }

            if(count > 3) // we don't care about empty slots
            {
                if(token == 1)
                    return 1;
                else if(token == 2)
                    return 2;
            }
        }
    }
    else if(n == 3)
    {
        for(int i = 0; i < 6; i++)
        {
            if(token == board[i + 1][5 - i])
            {
                count++;
            }
            else
            {
                count = 1;
                token = board[i + 1][5 - i];
            }

            if(count > 3) // we don't care about empty slots
            {
                if(token == 1)
                    return 1;
                else if(token == 2)
                    return 2;
            }
        }
    }
    else if(n == 4)
    {
        for(int i = 0; i < 5; i++)
        {
            if(token == board[i + 2][5 - i])
            {
                count++;
            }
            else
            {
                count = 1;
                token = board[i + 2][5 - i];
            }

            if(count > 3) // we don't care about empty slots
            {
                if(token == 1)
                    return 1;
                else if(token == 2)
                    return 2;
            }
        }
    }
    else if (n == 5)
    {
        for(int i = 0; i < 4; i++)
        {
            if(token == board[i + 3][5 - i])
            {
                count++;
            }
            else
            {
                count = 1;
                token = board[i + 3][5 - i];
            }

            if(count > 3) // we don't care about empty slots
            {
                if(token == 1)
                    return 1;
                else if(token == 2)
                    return 2;
            }
        }
    }
    
    return 0;
}

void clearBoard()
{
    for(int i = 0; i < BOARD_HEIGHT; i++) // clear board it for good measure
    {
        for(int j = 0; j < BOARD_WIDTH; j++)
        {
            board[j][i] = 0;
        }
    }
}