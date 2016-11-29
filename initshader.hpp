#ifndef INIT_SHADER_H
#define INIT_SHADER_H
//hw4
//start with simple
//add header file after
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
// #include <GL/glew.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <memory.h>
#include "list.h"
#include "common.hpp"

//********Globals*******//
// struct node *headx = NULL;
// struct node *heady = NULL;
// struct node *headz = NULL;
// unsigned dsize = sizeof(double);
// unsigned bsize = sizeof(bool);
// unsigned isize = sizeof(int);
// unsigned fsize = sizeof(float);
GLuint initshader(const char* vShaderFile, const char* fShaderFile);
GLuint make_bo(GLenum type, const void *buf, GLsizei buf_size);
static char* readShaderSource(const char* shaderFile);
#endif
