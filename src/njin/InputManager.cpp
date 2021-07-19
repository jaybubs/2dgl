#include "InputManager.h"

namespace njin {
  InputManager::InputManager(){

  }

  InputManager::~InputManager(){

  }
  void InputManager::pressKey(unsigned int keyID) {
    keyMap[keyID] = true; //umaps can be treated as arrays
  }
  void InputManager::releaseKey(unsigned int keyID) {
    keyMap[keyID] = false;
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
