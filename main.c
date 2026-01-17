#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char* argv[]){

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

    char *filePath = "Red_Kitten_01.jpg";

    if (argc > 1) {
        filePath = argv[1];
    }


    int winW = 600;
    int winH = 600;

    SDL_Window *iwindow = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, winW, winH, 0);
    SDL_Renderer *irenderer = SDL_CreateRenderer(iwindow, -1, 0);
    SDL_Surface *isurface = IMG_Load(filePath);
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
            else if (event.type == SDL_DROPFILE) {
                char* dropped_filedir = event.drop.file;

                    if (itexture != NULL) {
                    SDL_DestroyTexture(itexture);
                }

                    SDL_Surface* temp_surface = IMG_Load(dropped_filedir);
                if (temp_surface == NULL) {
                    printf("Image can't loaded: %s\n", IMG_GetError());
                } else {
                    
                    itexture = SDL_CreateTextureFromSurface(irenderer, temp_surface);
                    SDL_FreeSurface(temp_surface);
                }

                
                SDL_free(dropped_filedir);
            }
        }


        int imgW, imgH;
        
        SDL_SetRenderDrawColor(irenderer, 0,0,0,255);
        SDL_GetWindowSize(iwindow, &winW, &winH);
        SDL_QueryTexture(itexture, NULL, NULL, &imgW, &imgH);
        SDL_RenderClear (irenderer);
        
        SDL_Rect target;
        
        float scaleW = (float)winW / imgW;
        float scaleH = (float)winH/ imgH;
        float scale = (scaleW < scaleH) ? scaleW : scaleH;

        target.w = (int)(imgW * scale);
        target.h = (int)(imgH * scale);



        target.x = (winW - target.w) / 2;
        target.y = (winH - target.h) / 2;

        SDL_RenderCopy(irenderer, itexture, NULL, &target);
        SDL_RenderPresent(irenderer);
    }

    SDL_DestroyRenderer(irenderer);
    SDL_DestroyWindow(iwindow);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
