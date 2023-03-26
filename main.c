#include<SDL.h>
#include<stdio.h>
#include<math.h>
#include<stdbool.h>
#include "map.h"
#include "keyboard.h"

float px = 8;
float py = 8;
float dir = 0;
int fov = 45;
int width = 640;
int height = 480;
int c = 1;

void rendering(SDL_Renderer *render) {
    if (dir >= 360) {
        dir = 0;
    }
    SDL_RenderClear(render);
    for(int i = 0; i < width; i++) {
        float ray = (((float)i / width) * fov) + (dir - (fov/2.0f));
        float tx = sin(ray*(3.14/180));
        float ty = cos(ray*(3.14/180));
        float distance = 0;
        unsigned int hit = false;
        while((hit != true) && (distance < 16)) {
            distance += 0.01;
            int cx = (int)(px + (distance * tx));
            int cy = (int)(py - (distance * ty));
            if (cx < 0 || cx >= 16 || cy < 0 || cy >= 16) {
                hit = true;
                distance = height;
            } else if (map[cx + (cy * 16)] == 1) {
                hit = true;
                c = 1;
                distance *= fabs(cos((ray*(3.14/180))-(dir*(3.14/180))));
            } else if (map[cx + (cy * 16)] == 2) {
                hit = true;
                c = 2;
                distance *= fabs(cos((ray*(3.14/180))-(dir*(3.14/180))));
            } else if (map[cx + (cy * 16)] == 3) {
                hit = true;
                c = 3;
                distance *= fabs(cos((ray*(3.14/180))-(dir*(3.14/180))));
            } else if (map[cx + (cy * 16)] == 4) {
                hit = true;
                c = 4;
                distance *= fabs(cos((ray*(3.14/180))-(dir*(3.14/180))));
            }
        }
        int ceiling = (height / 2) - (height / distance);
        int floor = height - ceiling;
        for(int z = 0; z < height; z++) {
            if (z <= ceiling) {
                SDL_SetRenderDrawColor(render, 150, 150, 150, 255);
                SDL_RenderDrawPoint(render, i, z);
            } else if (z > ceiling && z <= floor) {
                if (c == 1) {
                    SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
                } else if (c==2) {
                    SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
                } else if (c==3) {
                    SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
                } else if (c==4) {
                    SDL_SetRenderDrawColor(render, 255, 255, 0, 255);
                }
                SDL_RenderDrawPoint(render, i, z);
            } else {
                SDL_SetRenderDrawColor(render, 150, 150, 150, 255);
                SDL_RenderDrawPoint(render, i, z);
            }
        }
    }
    SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderPresent(render);
}

int main(int argc, char* argv[]) {
    SDL_Window* window = SDL_CreateWindow("Raycasting", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    SDL_Renderer *render = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize");
    } else {
        SDL_Event event;
        while(1) {
            if (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    break;
                }
                keyboard(event, &dir, &px, &py);
                rendering(render);
            }    
        }
    }
}