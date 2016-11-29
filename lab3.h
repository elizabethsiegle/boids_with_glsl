#ifndef LAB3_H
#define LAB3_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#ifdef __APPLE__
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#else
#include <GLFW/glfw3.h>
#define WIDTH 400
#define HEIGHT 400
#endif

void init();
void draw2();
void drawWireframeCube();
GLubyte cubeWireframeIndices[48];
GLubyte cubeIndices[24];
GLfloat cubeVertices[][3];
GLfloat cubeColors[][3];
void reshape(GLFWwindow *wind, int w, int h);

#endif

