#ifndef PARTICLES_H
#define PARTICLES_H
#include <SDL2/SDL_render.h>
#include <stdbool.h>
#define DEFAULT_PARTICLE_COUNT 1000
#define MAX_FRAME_TIME 10

struct Particle {
  int frame;
  int x;
  int y;
  int w;
  int h;
};

typedef struct Particle Particle;

Particle **create_particle_buffer(size_t *buffer_size);
void draw_particles(Particle **buffer, const size_t *buffer_length,
                    const SDL_Color *rgba);
bool particle_is_dead(int frame);
void cull_dead_particle(Particle *dead_particle);
Particle *create_particle(int area_w, int area_h);

#endif
