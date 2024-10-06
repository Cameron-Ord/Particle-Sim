#include "../inc/render.h"
#include "../inc/main.h"

void render_present() { SDL_RenderPresent(sdl2.r); }

void render_clear() { SDL_RenderClear(sdl2.r); }

void render_bg() {
  uint8_t r = theme.background.r, g = theme.background.g,
          b = theme.background.b, a = theme.background.a;

  SDL_SetRenderDrawColor(sdl2.r, r, g, b, a);
}
