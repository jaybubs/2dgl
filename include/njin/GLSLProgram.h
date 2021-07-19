#pragma once
#include <string>
#include <GL/glew.h>

namespace njin {
  /* needed to run shaders */
  class GLSLProgram
  {
    private:
      GLuint programID; //refers to the finished product
      GLuint vertexShaderID;
      GLuint fragmentShaderID;

      void compileShader(const std::string& filePath, GLuint shaderID);
      int numAttr;

    public:
      GLSLProgram();
      ~GLSLProgram();


      GLint getUniformLocation(const std::string& uniformName);
      void createShaders(const std::string& vertexFilePath, const std::string& fragmentFilePath);
      void linkShaders();
      void addAttr(const std::string& attrName);
      void use();
      void unuse();
  };
}
