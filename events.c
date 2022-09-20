#include"common.h"
#include "events.h"

int checkGameEvents(SDL_Event e)
{
    if(e.type == SDL_QUIT)
        return 0;
    else if(e.type == SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_w:
                //moveCursor(UP, c);
                break;
            case SDLK_s:
                //moveCursor(DOWN, c);
                break;
            case SDLK_a:
                //moveCursor(LEFT, c);
                break;
            case SDLK_d:
                //moveCursor(RIGHT, c);
                break;
            case SDLK_SPACE:
                // select mech?
                break;
            default:
                break;
        }
        return 1;    
    }
}

int checkMenuEvents(SDL_Event e)
{
    if(e.type == SDL_QUIT)
        return 0;
    else if(e.type == SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_RETURN:
                return 2; // change this maybe?
                break;
            default:
                break;
        }
        return 1;    
    }
}

void moveCursor(int dir, MapCursor *c)
{
    switch(dir)
    {
        case UP:
            c->y -= 1;
            if(c->y < 0)
                c->y = 0;
            break;
        case LEFT:
            c->x -= 1;
            if(c->x < 0)
                c->x = 0;
            break;
        case DOWN:
            c->y += 1;
            if(c->y > MAX_MAP_SIZE - 1)
                c->y = MAX_MAP_SIZE - 1;
            break;
        case RIGHT:
            c->x += 1;
            if(c->x > MAX_MAP_SIZE - 1)
                c->x = MAX_MAP_SIZE - 1;
            break;
        default:
            break;
    }
}