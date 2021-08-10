#pragma once
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtx/io.hpp>

#include <iostream>

namespace njin {
  class InputManager
  {
    private:
      std::unordered_map<unsigned int, bool> keyMap;

    public:
      InputManager();
      ~InputManager();

      void pressKey(unsigned int keyID);
      void releaseKey(unsigned int keyID);
      void setMouseCoords(float x, float y); //publicise
      glm::vec2 const getMouseCoords() { return mouseCoords; }; //publicise
      bool isKeyPressed(unsigned int keyID);
      glm::vec2 mouseCoords;
  };
}
