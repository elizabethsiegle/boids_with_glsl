//vec2
#ifndef VECS_H
#define VECS_H
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <GL/glew.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <memory.h>

class vector2 {
public:
  float vec2Arr[2];
  vector2(float, float);
  void normalizeVec2();
  void add(vector2);
};

//vector3
class vector3 {
public:
  float vec3Arr[3];
  vector3(float, float, float);
  void normalizeVec3();
  void add(vector3);
};

//vector4
class vector4 {
public:
  float vec4Arr[4];
  vector4(float, float, float, float);
  void normalizeVec4();
  void add(vector4);
};

#endif
