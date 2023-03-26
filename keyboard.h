#include<SDL.h>
#include<math.h>

void keyboard(SDL_Event event, float *dir, float *px, float *py) {
    switch(event.type) {
                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_RIGHT) {
                            *dir += 4;
                        }
                        if (event.key.keysym.sym == SDLK_LEFT) {
                            *dir -= 4;
                        }
                        if (event.key.keysym.sym == SDLK_UP) {
                            *px += sin(*dir*(3.14/180)) * 0.2;
                            *py -= cos(*dir*(3.14/180)) * 0.2;
                        }
                        if (event.key.keysym.sym == SDLK_DOWN) {
                            *px -= sin(*dir*(3.14/180)) * 0.2;
                            *py += cos(*dir*(3.14/180)) * 0.2;
                        }
                        break;
                }
}