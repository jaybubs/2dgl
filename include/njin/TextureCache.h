#pragma once
#include <map>
#include "GLTexture.h"


namespace njin {
  /*  */
  class TextureCache
  {
    private:
      std::map<std::string, GLTexture> textureMap;


    public:
      TextureCache();
      ~TextureCache();

      GLTexture getTexture(std::string texturePath); //no need for a ptr, glt class is small
  };
}
