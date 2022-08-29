#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_HEIGHT (1000)
#define WINDOW_WIDTH (1000)

#define SCROLL_SPEED (300)

const char* X = "resources/x.jpg";
const char* HELLO = "resources/hello.png";
const char* BOARD = "resources/board.png";

// Pixels in seconds
#define SPEED (300);

int main(void) {

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) 
    {
        printf("Error Initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Tic Tac Toe", 
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    if(!win) 
    {
        printf("Error Creating Window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);

    if (!rend)
    {
        printf("Error Creating Render: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

    SDL_Surface* surface = IMG_Load(BOARD);

    if (!surface) 
    {
        printf("Error Creating Surface: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if (!tex) 
    {
        printf("Error Ceating Texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Rect board;
    SDL_QueryTexture(tex, NULL, NULL, &board.w, &board.h);

    board.w *= 2;
    board.h *= 2;

    board.x = (WINDOW_WIDTH - board.w) / 2;
    board.y = ((WINDOW_HEIGHT - board.h) / 2) + 50;

    int close = 0;
    
    while (!close) 
    {
        SDL_Event event;

        while (SDL_PollEvent(&event)) 
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    close = 1;
                    break;                
            }
        }

        // clears the screen 
		SDL_RenderClear(rend); 
		SDL_RenderCopy(rend, tex, NULL, &board);

		// triggers the double buffers 
		// for multiple rendering 
		SDL_RenderPresent(rend); 

		// calculates to 60 fps 
		SDL_Delay(1000 / 60); 
    }


    // clean up resources before exiting
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    return 0;




}