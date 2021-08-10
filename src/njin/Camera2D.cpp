#include "Camera2D.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
namespace njin {
  Camera2D::Camera2D() : 
    screenW(500),
    screenH(500),
    position(0.0f,0.0f), 
    cameraMatrix(1.0f),
    scale(1.0f),
    needsMatrixUpdate(1),
    orthoMatrix(1.0f)
  {

  }

  Camera2D::~Camera2D(){

  }

  void Camera2D::init(int screenWidth, int screenHeight) {
    screenW = screenWidth;
    screenH = screenHeight;
    //screen projection
    orthoMatrix = glm::ortho(0.0f, (float)screenW, 0.0f, (float)screenH);
  }

  void Camera2D::update() {
    if (needsMatrixUpdate) {

      glm::vec3 camTranslate((- position.x + (screenW * 0.5)), (- position.y + (screenH * 0.5)), 0.0f);
      cameraMatrix = glm::translate(orthoMatrix, camTranslate);

      glm::vec3 camScale(scale, scale, 0.0f);
      //make the scaling focal point the centre of the screen, for this first the identity mx needs to be scaled and then applied onto the cam mx, otherwise noncommutitavity will make it scale around a corner instead
      cameraMatrix = glm::scale(glm::mat4(1.0f), camScale)*cameraMatrix;

      needsMatrixUpdate = false;
    }

  }

  glm::vec2 Camera2D::convertSTW(glm::vec2 screenCoords) {
    //invert y coord
    screenCoords.y = screenH - screenCoords.y;
    //screen edges wil be relative to 0,0 in the centre
    screenCoords -= glm::vec2(screenW*0.5, screenH*0.5);
    //take into account camera scale too, optimise for division?
    screenCoords /= scale;
    // translate wrt camera
    screenCoords += position;

    return screenCoords;


  }
}
