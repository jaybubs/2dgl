#include "IOManager.h"
#include <fstream>

namespace njin {
  bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
    std::ifstream file(filePath, std::ios::binary);
    if (file.fail()) {
      perror(filePath.c_str());
      return false;
    }

    //seek to the eof
    file.seekg(0, std::ios::end);

    //get file size
    int fileSize = file.tellg();

    //return the ptr back to the beginning
    file.seekg(0, std::ios::beg);

    fileSize -= file.tellg(); //disregard the header, reduce file size

    //prealloc
    buffer.resize(fileSize);
    file.read((char *)&(buffer[0]), fileSize); //will return c_str, casting to char * to pretend using char * but will later use it as unsigned char anyway
    file.close();

    return true;

  }
}
