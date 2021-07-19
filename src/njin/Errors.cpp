#include <Errors.h>
#include <cstdlib>
#include <iostream>
#include <SDL2/SDL.h>

namespace njin {
  void fatalError(std::string errorString) {
    std::cout << errorString << std::endl;
    std::cout << "enter any key to quit" << std::endl;
    int tmp;
    std::cin >> tmp;
    SDL_Quit();
    exit(69);
  }
}
