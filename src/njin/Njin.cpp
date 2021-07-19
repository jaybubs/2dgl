#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace njin {
  int init() {

    SDL_Init(SDL_INIT_EVERYTHING);

    // empty one buffer while other is being drawn to, can prevent flicker
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    return 0;
  }
}

