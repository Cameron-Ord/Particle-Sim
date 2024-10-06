#ifndef MAIN_H
#define MAIN_H
#include <SDL2/SDL.h>
#include <stdbool.h>

struct SDL2 {
  SDL_Window *w;
  SDL_Renderer *r;
  int win_height;
  int win_width;
  bool running;
};

struct Colors {
  SDL_Color primary;
  SDL_Color secondary;
  SDL_Color background;
};

bool initialize_sdl2();
SDL_Window *create_window();
SDL_Renderer *create_renderer(SDL_Window *w);

extern struct SDL2 sdl2;
extern struct Colors theme;

#endif
