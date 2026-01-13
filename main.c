#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int main()
{
    SDL_Window *iwindow = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 600, 600, 0);
    SDL_Surface *isurface = SDL_GetWindowSurface(iwindow);

    SDL_FillRect(isurface, NULL, 0xFFFFFFFF);
    SDL_UpdateWindowSurface(iwindow);
    SDL_Delay(4000);
    return 0;
}
