#include "InputManager.h"

namespace njin {
  InputManager::InputManager() : mouseCoords(0.0f, 0.0f) {

  }

  InputManager::~InputManager(){

  }
  void InputManager::pressKey(unsigned int keyID) {
    keyMap[keyID] = true; //umaps can be treated as arrays
  }
  void InputManager::releaseKey(unsigned int keyID) {
    keyMap[keyID] = false;
  }

  void InputManager::setMouseCoords(float x, float y) {
    mouseCoords.x = x;
    mouseCoords.y = y;

    /* enable for debugging mouse position in the console */
    /* std::cout << mouseCoords << std::endl; */
  }


  bool InputManager::isKeyPressed(unsigned int keyID) {
    auto it = keyMap.find(keyID);
    if (it != keyMap.end()) {
      return it->second;
      } else {
      return false;
    }
  }
}
