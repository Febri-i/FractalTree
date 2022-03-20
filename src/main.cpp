#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#define PI 3.141592653589793
#include "Vector2.hpp"
#include <SDL2/SDL.h>

#include <SDL2/SDL_render.h>
#include <cmath>
#include <cstdint>
#include <iostream>
int divider = 10;
int SCR_SIZE = 720;
float loss = 0.8;

void renderTree(SDL_Renderer *renderer, vec2<int> position, int length,
                float loss, float angle) {
  if (length > 5) {
    vec2<int> pos2(length * cos(angle), sin(angle) * length);
    pos2.x = position.x + pos2.x;
    pos2.y = position.y - pos2.y;
    // std::cout << position.y << std::endl;
    SDL_SetRenderDrawColor(renderer, 0, 100 / length * 150, 100 / length * 255,
                           255);

    SDL_RenderDrawLine(renderer, position.x, position.y, pos2.x, pos2.y);

    renderTree(renderer, pos2, length * loss, loss, angle + (PI / divider));
    renderTree(renderer, pos2, length * loss, loss, angle - (PI / divider));
  }
};

int main() {
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 1;
  } else {
    window = SDL_CreateWindow("Marching SQUARE", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCR_SIZE, SCR_SIZE,
                              SDL_WINDOW_SHOWN);
    if (window == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      return 1;
    } else {
      renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
      if (renderer == NULL) {
        printf("SDL could not create renderer\n%s", SDL_GetError());
        return 1;
      }
    }
  };

  bool running = true;
  SDL_Event e;

  bool dragging = false;

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  renderTree(renderer, vec2<int>(SCR_SIZE / 2, SCR_SIZE), 100, loss, PI / 2);

  SDL_RenderPresent(renderer);

  while (running) {
    // running = 0;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        running = false;
      }
      if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_UP) {
          divider += 1;
        } else if (e.key.keysym.sym == SDLK_DOWN) {
          divider -= 1;
        }
        if (e.key.keysym.sym == SDLK_LEFT && loss > 0) {
          loss -= 0.005;
        } else if (e.key.keysym.sym == SDLK_RIGHT && loss < 1) {
          loss += 0.005;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderClear(renderer);

        renderTree(renderer, vec2<int>(SCR_SIZE / 2, SCR_SIZE), 100, loss,
                   PI / 2);
        SDL_RenderPresent(renderer);
      }
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
};
