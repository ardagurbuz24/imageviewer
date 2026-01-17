#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(){

    int imgflags = IMG_INIT_JPG | IMG_INIT_PNG;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("sdl error: %s", SDL_GetError());
        return 1;
    }

    if((IMG_Init(imgflags) & imgflags) != imgflags) {
        printf("sdl image error: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window *iwindow = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 600, 600, 0);
    SDL_Renderer *irenderer = SDL_CreateRenderer(iwindow, -1, 0);
    SDL_Surface *isurface = IMG_Load("Red_Kitten_01.jpg");
    SDL_Texture *itexture = SDL_CreateTextureFromSurface(irenderer, isurface);
    SDL_FreeSurface(isurface);

    if (itexture == NULL) {
        printf("there is no texture available %s\n", SDL_GetError());

        SDL_FreeSurface(isurface);
        SDL_DestroyRenderer(irenderer);
        SDL_DestroyWindow(iwindow);
        IMG_Quit(),
        SDL_Quit();
        return 1;
    }


    int running = 1;
    SDL_Event event;

    while(running) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = 0;
            }
        }


        SDL_SetRenderDrawColor(irenderer, 0,0,0,255);
        SDL_RenderClear (irenderer);       
        SDL_RenderCopy(irenderer, itexture, NULL, NULL);
        SDL_RenderPresent(irenderer);
    }

    SDL_DestroyRenderer(irenderer);
    SDL_DestroyWindow(iwindow);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
