#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int main(){

    if(SDL_Init((SDL_INIT_VIDEO) < 0)) {
        printf("sdl error: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *iwindow = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 600, 600, 0);
    SDL_Renderer *irenderer = SDL_CreateRenderer(iwindow, -1, 0);

    int running = 1;
    SDL_Event event;

    while(running) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(irenderer, 255, 255, 255, 255);
        SDL_RenderClear(irenderer);

        SDL_RenderPresent(irenderer);
    }

    SDL_DestroyRenderer(irenderer);
    SDL_DestroyWindow(iwindow);
    SDL_Quit();

    return 0;
}
