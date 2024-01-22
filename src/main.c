#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>

#define WIN_WIDTH 500
#define WIN_HEIGHT 500

#define SNAKE_SIZE 50

#define SNAKE_W_H 25
#define FOOD_W_H SNAKE_W_H


void move_snake(SDL_Rect *snake, int size,char fdir)
{
    for (int i=size-1; i>0; i--)
    {
        snake[i].x = snake[i-1].x;
        snake[i].y = snake[i-1].y;
    }

    if (fdir == 'r')
    {
        snake[0].x = snake[0].x + 25;
        if (snake[0].x > WIN_WIDTH)
        {
            snake[0].x = 0;
        }
    }else if (fdir == 'l')
    {
        snake[0].x = (snake[0].x - 25);
        if (snake[0].x < 0){
            snake[0].x = WIN_WIDTH - SNAKE_W_H;
        }
    }else if (fdir == 'u')
    {
        snake[0].y = (snake[0].y - 25);
        if (snake[0].y < 0){
            snake[0].y = WIN_HEIGHT - SNAKE_W_H;
        }
    }else if (fdir == 'd')
    {
        snake[0].y = snake[0].y + 25;
        if (snake[0].y > WIN_HEIGHT)
        {
            snake[0].y = 0;
        }    
    }
}

bool isInRect(SDL_Rect r1,SDL_Rect r2) // check r1 in r2
{
    if (r1.x == r2.x && r1.y == r2.y)
    {
        return true;
    }

    return false;
}

char is_snake_collide(SDL_Rect *snake,int size,SDL_Rect food)
{
    for (int i=2; i<size; i++)
    {
        if(isInRect(snake[0],snake[i]))
        {
            return 'i';
        }
    }

    if(isInRect(snake[0],food))
    {
        return 'f';
    }

    return '\0';
}

int main(int ac,char *av[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *win = SDL_CreateWindow("snakeGame",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIN_WIDTH,WIN_HEIGHT,SDL_WINDOW_SHOWN);

    SDL_Renderer *ren = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event e;

    char fdir = 'r'; // l,r,u,d

    SDL_Rect snake[SNAKE_SIZE];
    int snake_len = 3;

    SDL_Rect food;

    // snake init
    snake[0].x = 300;
    snake[0].y = 200;

    snake[1].x = snake[0].x - SNAKE_W_H;
    snake[1].y = snake[0].y;

    snake[2].x = snake[1].x - SNAKE_W_H;
    snake[2].y = snake[1].y;


    for (int i=0; i<SNAKE_SIZE; i++)
    {
        snake[i].h = snake[i].w = SNAKE_W_H;
    }


    // food init
    food.w = food.h = FOOD_W_H;
    
    food.x = 50*(rand()%10) ;
    food.y = 50*(rand()%10) ;        



    srand(time(NULL));

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }else if (e.type == SDL_KEYDOWN)
            {
                int key = e.key.keysym.sym;

                if(key == SDLK_UP && fdir != 'd')
                {
                    fdir = 'u';
                }
                else if(key == SDLK_DOWN && fdir != 'u')
                {
                    fdir = 'd';
                }
                else if(key == SDLK_LEFT && fdir != 'r')
                {
                    fdir = 'l';
                }
                else if(key == SDLK_RIGHT && fdir != 'l')
                {
                    fdir = 'r';
                }
            }
        }

        SDL_SetRenderDrawColor(ren,45,45,45,255);
        SDL_RenderClear(ren);


        for (int i=0; i<snake_len; i++)
        {
            if (i == 0)
                SDL_SetRenderDrawColor(ren,40,45,205,255);
            else
                SDL_SetRenderDrawColor(ren,45,205,45,255);


            SDL_RenderFillRect(ren,&snake[i]);
        }
        
        move_snake(snake,snake_len,fdir);
        char coll = is_snake_collide(snake,snake_len,food);

        if (coll == 'f')
        {
            if (fdir == 'l')
            {
                snake[snake_len].x = snake[snake_len - 1].x + SNAKE_W_H;
                snake[snake_len].y = snake[snake_len - 1].y;
            }else if (fdir == 'r')
            {
                snake[snake_len].x = snake[snake_len - 1].x - SNAKE_W_H;
                snake[snake_len].y = snake[snake_len - 1].y;
            }else if (fdir == 'd')
            {
                snake[snake_len].x = snake[snake_len - 1].x;
                snake[snake_len].y = snake[snake_len - 1].y - SNAKE_W_H;
            }else if(fdir == 'u')
            {
                snake[snake_len].x = snake[snake_len - 1].x;
                snake[snake_len].y = snake[snake_len - 1].y + SNAKE_W_H;
            }
            snake_len++;

            food.x = 50*(rand()%10) ;
            food.y = 50*(rand()%10) ;        
        }
        else if(coll == 'i')
        {
            SDL_Delay(3000);
            break;
        }

        SDL_SetRenderDrawColor(ren,200,45,45,255);
        SDL_RenderFillRect(ren,&food);

        SDL_RenderPresent(ren);
        SDL_Delay(300);
    }

    SDL_Quit();
    return (EXIT_SUCCESS);
}