#pragma once
#include <vector>
#include <string>

namespace njin {
  struct IOManager {
    static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer); //by ref so no new copies
  };
}
