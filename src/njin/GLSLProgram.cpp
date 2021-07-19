#include "GLSLProgram.h"
#include <Errors.h>
#include <fstream>
#include <vector>

namespace njin {
  GLSLProgram::GLSLProgram(): programID(0), vertexShaderID(0), fragmentShaderID(0), numAttr(0) {

  }

  GLSLProgram::~GLSLProgram(){

  }

  void GLSLProgram::createShaders(const std::string& vertexFilePath, const std::string& fragmentFilePath) {

    //must go first, otherwise opengl will guess and might guess wrong
    programID = glCreateProgram();

    //create shaders
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (vertexShaderID == 0) {
      fatalError("vertex shader failed to be created");
    }

    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (fragmentShaderID == 0) {
      fatalError("fragment shader failed to be created");
    }

    compileShader(vertexFilePath, vertexShaderID);
    compileShader(fragmentFilePath, fragmentShaderID);

  }

  void GLSLProgram::compileShader(const std::string& shaderFilePath, GLuint shaderID) {

    //load shaders
    std::ifstream shaderFile(shaderFilePath); //process the shader file as a string
    if (shaderFile.fail()) {
      perror(shaderFilePath.c_str());
      fatalError("failed to open " + shaderFilePath);
    }

    std::string fileContents = "";
    std::string line;

    while (std::getline(shaderFile, line)) {
      fileContents += line + "\n"; //getline doesn't know when to insert newline automatically
    }

    shaderFile.close();

    const char* contentsPtr = fileContents.c_str(); //ptr to an array of c_str because opengl demands it as an argument, cannot just dereference
    glShaderSource(shaderID, 1, &contentsPtr, nullptr);

    //compile shader
    glCompileShader(shaderID);

    GLint success = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE) {
      GLint maxLength = 0;
      glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength); //sets the maxlength of the log

      //maxlength includes NULL char
      std::vector<char> errorLog(maxLength);
      glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);



      //provide the infolog in whatever manor you deem best, exit with failure
      glDeleteShader(shaderID); //don't leak

      std::printf("%s\n", &(errorLog[0])); //prints out the vector of chars as a string

      fatalError("shader " + shaderFilePath + " failed to compile");
    }

  }


  void GLSLProgram::linkShaders() {

    //run after shaders have been compiled
    //create program, attach shaders and link


    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);

    glLinkProgram(programID);

    //error checking
    GLint isLinked = 0;
    glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE) {
      GLint maxLength = 0;
      glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);
      std::vector<char> errorLog(maxLength);
      glGetProgramInfoLog(programID, maxLength, &maxLength, &errorLog[0]);
      //don't leak
      glDeleteProgram(programID);
      glDeleteShader(vertexShaderID);
      glDeleteShader(fragmentShaderID);

      std::printf("%s\n", &(errorLog[0])); //prints out the vector of chars as a string

      fatalError("shaders failed to link");
    }

    //detach shaders after linking
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);


  }


  void GLSLProgram::addAttr(const std::string& attrName) {
    glBindAttribLocation(programID, numAttr++, attrName.c_str()); //need c_str
    //numAttr++ in arg is the same as increasing it after the fx has run
  }

  void GLSLProgram::use() {
    glUseProgram(programID);
    for (int i = 0; i < numAttr; ++i) {
      glEnableVertexAttribArray(i);
    }
  }

  void GLSLProgram::unuse() {
    glUseProgram(0);
    for (int i = 0; i < numAttr; ++i) {
      glDisableVertexAttribArray(i);
    }
  }

  GLint GLSLProgram::getUniformLocation(const std::string& uniformName) {
    GLint location = glGetUniformLocation(programID, uniformName.c_str());
    if (location == (int)GL_INVALID_INDEX) {
      fatalError("Uniform " + uniformName + " not found in shader!");
    }
    return location;

  }
}
