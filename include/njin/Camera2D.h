#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> //for orthographic proj code

namespace njin {
  class Camera2D
  {
    private:
      int screenW;
      int screenH;
      glm::vec2 position;
      glm::mat4 cameraMatrix;
      float scale;
      bool needsMatrixUpdate;

    public:
      Camera2D();
      ~Camera2D();

      void init(int screenW, int screenH);

      void update();
      //gettersetter - rewrite later

      void setPosition(const glm::vec2& newPosition) {
        position = newPosition;
        needsMatrixUpdate = true;
      }
      void setScale(float newScale) {
        scale = newScale;
        needsMatrixUpdate = true;
      }

      glm::vec2 getPosition() { return position; }
      float getScale() { return scale; }
      // Screen To World
      glm::vec2 convertSTW(glm::vec2 screenCoords);
      glm::mat4 getCameraMatrix() { return cameraMatrix; }
      glm::mat4 orthoMatrix;
  };
}
