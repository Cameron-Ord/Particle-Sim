#include "../inc/particles.h"
#include "../inc/main.h"
#include <stdlib.h>

Particle **create_particle_buffer(size_t *buffer_size) {
  Particle **particle_buffer =
      (Particle **)malloc(sizeof(Particle *) * DEFAULT_PARTICLE_COUNT);

  for (size_t i = 0; i < DEFAULT_PARTICLE_COUNT; i++) {
    particle_buffer[i] = NULL;
  }

  *buffer_size = DEFAULT_PARTICLE_COUNT;
  return particle_buffer;
}

bool particle_is_dead(int frame) { return frame > MAX_FRAME_TIME; }

Particle *create_particle(int area_w, int area_h) {
  Particle *particle = (Particle *)malloc(sizeof(Particle));
  if (!particle) {
    return NULL;
  }

  particle->frame = rand() % 5;
  particle->w = 2;
  particle->h = 2;

  particle->x = rand() % (area_w - particle->w);
  particle->y = rand() % (area_h - particle->h);

  return particle;
}

void draw_particles(Particle **buffer, const size_t *buffer_length,
                    const SDL_Color *rgba) {
  for (size_t i = 0; i < *buffer_length; i++) {
    if (buffer[i]) {
      if (particle_is_dead(buffer[i]->frame)) {
        cull_dead_particle(buffer[i]);
        buffer[i] = NULL;
      }
    }

    if (!buffer[i]) {
      buffer[i] = create_particle(sdl2.win_width, sdl2.win_height);
    }

    if (buffer[i]) {
      SDL_Rect particle_rect = {buffer[i]->x, buffer[i]->y, buffer[i]->w,
                                buffer[i]->h};
      SDL_SetRenderDrawColor(sdl2.r, rgba->r, rgba->g, rgba->b, rgba->a);
      SDL_RenderFillRect(sdl2.r, &particle_rect);
      buffer[i]->frame++;
    }
  }
}

void cull_dead_particle(Particle *dead_particle) {
  if (dead_particle) {
    free(dead_particle);
  }
}
