
#include "../inc/main.h"
#include "../inc/particles.h"
#include "../inc/render.h"
#include <SDL2/SDL_events.h>
#include <stdlib.h>
#include <time.h>

struct SDL2 sdl2;
struct Colors theme;

int main(int argc, char **argv) {

  srand(time((NULL)));
  memset(&sdl2, 0, sizeof(struct SDL2));

  SDL_Color p = {166, 172, 205, 255};
  SDL_Color s = {68, 66, 103, 255};
  SDL_Color bg = {41, 45, 62, 255};

  theme.primary = p;
  theme.secondary = s;
  theme.background = bg;

  initialize_sdl2();
  sdl2.w = create_window();
  sdl2.r = create_renderer(sdl2.w);

  size_t buffer_size = 0;
  Particle **particle_buffer = create_particle_buffer(&buffer_size);

  sdl2.running = true;

  const int ticks_per_frame = (1000.0 / 60);
  uint64_t frame_start;
  int frame_time;

  while (sdl2.running) {
    frame_start = SDL_GetTicks64();

    render_bg();
    render_clear();

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      switch (e.type) {

      default: {
        break;
      }

      case SDL_QUIT: {
        sdl2.running = false;
        break;
      }

      case SDL_WINDOWEVENT: {
        switch (e.window.event) {

        default: {
          break;
        }
        case SDL_WINDOWEVENT_SIZE_CHANGED: {
          SDL_GetWindowSize(sdl2.w, &sdl2.win_width, &sdl2.win_height);
          break;
        }
        case SDL_WINDOWEVENT_RESIZED: {
          SDL_GetWindowSize(sdl2.w, &sdl2.win_width, &sdl2.win_height);
          break;
        }
        }

        break;
      }

      case SDL_KEYDOWN: {
        break;
      }
      }
    }

    draw_particles(particle_buffer, &buffer_size, &theme.primary);

    frame_time = SDL_GetTicks64() - frame_start;
    if (ticks_per_frame > frame_time) {
      SDL_Delay(ticks_per_frame - frame_time);
    }

    render_present();
  }

  if (particle_buffer) {
    free(particle_buffer);
  }
  SDL_Quit();

  return 0;
}

bool initialize_sdl2() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0) {
    fprintf(stderr, "Could not initialize sdl2! -> %s", SDL_GetError());
    return false;
  }

  return true;
}

SDL_Window *create_window() {
  SDL_Window *w =
      SDL_CreateWindow("Particle Sim", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_RESIZABLE);
  if (!w) {
    return NULL;
  }

  return w;
}

SDL_Renderer *create_renderer(SDL_Window *w) {
  SDL_Renderer *r = SDL_CreateRenderer(w, -1, SDL_RENDERER_SOFTWARE);
  if (!r) {
    return NULL;
  }

  return r;
}
