#pragma once
#include "TextureCache.h"
#include <string>



namespace njin {
  /*  */
  class ResourceManager
  {
    private:
      static TextureCache textureCache;

    public:
      static GLTexture getTexture(std::string texturePath); //wrapper

  };
}
