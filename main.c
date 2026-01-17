#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <dirent.h>
#include <string.h>

SDL_Texture *itexture = NULL;
SDL_Renderer *irenderer = NULL;
int imgW = 0;
int imgH = 0;


char *image_list[512];
int total_images = 0;
int current_index = 0;
char *current_dir = ".";


void load_new_image(const char *file_path) {
    if (itexture != NULL) {
        SDL_DestroyTexture(itexture);
        itexture = NULL;
    }

    SDL_Surface *isurface = IMG_Load(file_path);
    if(isurface == NULL) {
        printf("Failed to load image: %s | SDL_image Error: %s\n", file_path, IMG_GetError());
        return;
    }

    itexture = SDL_CreateTextureFromSurface(irenderer, isurface);
    SDL_FreeSurface(isurface);

    if (itexture == NULL) {
        printf("Failed to create texture from %s: %s\n", file_path, SDL_GetError());
        return;
    }

    SDL_QueryTexture(itexture, NULL, NULL, &imgW, &imgH);
    printf("Successfully loaded: %s (%dx%d)\n", file_path, imgW, imgH);
}


void scan_directory(const char *path) {
    DIR *dir = opendir(path);
    struct dirent *entry;

    if (dir == NULL) {
        printf("couldn't open directory: %s\n", path);
        return;
    }

    printf("scanning directory: %s\n", path);

    while ((entry = readdir(dir)) != NULL) {
                if (strstr(entry->d_name, ".jpg") || strstr(entry->d_name, ".png")) {
            if (total_images < 512) {
                image_list[total_images] = strdup(entry->d_name);
                total_images++;
            }
        }
    }
    
    closedir(dir);
    printf("total images found: %d\n", total_images);
} 


int main(int argc, char* argv[]){
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
    int imgflags = IMG_INIT_JPG | IMG_INIT_PNG;
    IMG_Init(imgflags);

    //char *filePath = "Red_Kitten_01.jpg";

    int winW = 600;
    int winH = 600;

    SDL_Window *iwindow = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, winW, winH, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    irenderer = SDL_CreateRenderer(iwindow, -1, SDL_RENDERER_ACCELERATED);
    scan_directory(".");

    if (argc > 1) {
        load_new_image(argv[1]);
    }else if (total_images > 0 ) {
        load_new_image(image_list[0]);
    }
    

    int running = 1;
    SDL_Event event;

    while(running) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = 0;
            }
            else if (event.type == SDL_DROPFILE) {
                load_new_image(event.drop.file);
            }
            else if (event.type == SDL_KEYDOWN) {
                if(total_images > 0) {
                    current_index = (current_index + 1) % total_images;
                    load_new_image(image_list[current_index]);
                }
                else if (event.key.keysym.sym == SDLK_LEFT) {
                    current_index = (current_index - 1 + total_images) % total_images;
                    load_new_image(image_list[current_index]);
                }
            }
        }

        if(itexture != NULL) {
            SDL_SetRenderDrawColor(irenderer, 0, 0, 0, 255);
            SDL_RenderClear(irenderer);
            
            SDL_GetWindowSize(iwindow, &winW, &winH);
            SDL_QueryTexture(itexture, NULL, NULL, &imgW, &imgH);
            
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
        
    }

    SDL_DestroyRenderer(irenderer);
    SDL_DestroyWindow(iwindow);
    IMG_Quit();

    for(int i = 0; i< total_images; i++) {
        free(image_list[1]);
    }
    SDL_Quit();

    return 0;
}
