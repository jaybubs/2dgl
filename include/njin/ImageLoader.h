#pragma once
#include "GLTexture.h"
#include <string>

namespace njin {
  class ImageLoader {
    public:
      static GLTexture loadPNG(std::string filePath);
  };
}
