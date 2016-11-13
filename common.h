#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef __APPLE__  // include Mac OS X verions of headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#else // non-Mac OS X operating systems
// #include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
//#include <GLFW/glfw3.h>
#endif  // __APPLE__

//  Helper function to load vertex and fragment shader files
GLuint initshader(const char* vertexShaderFile, const char* fragmentShaderFile);

#endif // __COMMON_H__
