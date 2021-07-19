#include "ResourceManager.h"

namespace njin {
  TextureCache ResourceManager::textureCache;

  GLTexture ResourceManager::getTexture(std::string texturePath) {
    return textureCache.getTexture(texturePath);
  }
}
