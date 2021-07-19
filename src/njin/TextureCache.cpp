#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>


namespace njin {
  TextureCache::TextureCache(){

  }

  TextureCache::~TextureCache(){

  }

  GLTexture TextureCache::getTexture(std::string texturePath) {
    //lookup texture
    std::map<std::string, GLTexture>::iterator mit = textureMap.find(texturePath); //actually can replace with auto
    //check if not in map
    if (mit == textureMap.end()) {
      //load texture
      GLTexture newTexture = ImageLoader::loadPNG(texturePath);
      //insert into map
      textureMap.insert(make_pair(texturePath, newTexture));

      std::cout << "loaded texture! \n" << std::endl;

      return newTexture;
    } // don't need else because first block returns

    /* std::cout << "loaded cached texture! \n" << std::endl; */
    return mit->second; //second is newTexture


  }
}
