#pragma once
#include <GL/glew.h>
#include "GLTexture.h"
#include <string>


namespace njin {
  /* 2d sprite class */
  class Sprite
  {
    private:

      float sx;
      float sy;
      float swidth;
      float sheight;

      //vertex buffer object
      GLuint vboID;
      GLTexture texture;

    public:
      Sprite();
      ~Sprite();

      void init(float x, float y, float width, float height, std::string texturePath);
      void draw();
  };
}
