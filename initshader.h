#ifndef INIT_SHADER_H
#define INIT_SHADER_H
//hw4
//start with simple
//add header file after
//#include "common.hpp"

//********Globals*******//
GLuint initshader(const char* vShaderFile, const char* fShaderFile);
GLuint make_bo(GLenum type, const void *buf, GLsizei buf_size);
static char* readShaderSource(const char* shaderFile);
#endif
