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