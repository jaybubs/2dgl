#include "Window.h"
#include <Errors.h>

namespace njin {
  Window::Window(){

  }

  Window::~Window(){

  }

  int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {

    Uint32 flags = SDL_WINDOW_OPENGL; //=2

    if (currentFlags & INVISIBLE) {
      flags |= SDL_WINDOW_HIDDEN;
    }
    if (currentFlags & FULLSCREEN) {
      flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    if (currentFlags & BORDERLESS) {
      flags |= SDL_WINDOW_BORDERLESS;
    }




    sdlWindow = SDL_CreateWindow(windowName.c_str(), 2400, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);

    if (sdlWindow == nullptr) {
      fatalError("Window could not be created");
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(sdlWindow);
    if (glContext == nullptr) {
      fatalError("context fucked");
    }

    GLenum error = glewInit();
    if (error != GLEW_OK) {
      fatalError("couldn't glew");
    }

    //check opengl version
    printf("*** OpenGL Version: %s ***", glGetString(GL_VERSION));

    glClearColor(0.0f,0.0f,1.0f,1.0f);

    //turn on vsync
    SDL_GL_SetSwapInterval(1);

    //enable alpha blend
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return 0;
  }

  void Window::swapBuffer() {
    SDL_GL_SwapWindow(sdlWindow);
  }
}
