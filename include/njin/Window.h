#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>

namespace njin {
  //window flags, give hexadec vals for bitwise ops
  enum WindowFlags {
    INVISIBLE = 0x1,
    FULLSCREEN = 0x2,
    BORDERLESS = 0x4
  };

  /*  */
  class Window
  {
    private:
      SDL_Window* sdlWindow;


    public:
      Window();
      ~Window();

      int screenWidth;
      int screenHeight;
      int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

      void swapBuffer();
  };
}
