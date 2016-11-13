//vec2
#include "vecs.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void vector2::vector2(GLfloat f1, GLfloat f2){
  vec2Arr[0] = f1;
  vec2Arr[1] = f2;
}

void vector2::normalizeVec2() {
  if(vec2Arr[0] != 0 && vec2Arr[1] != 0) { // || ??
    vec2Arr[0] /= sqrt(pow(vec2Arr[0], 2) + pow(vec2Arr[1], 2));
    vec2Arr[1]/ = sqrt(pow(vec2Arr[0], 2) + pow(vec2Arr[1], 2));
  }
}

void vector2::add(vector2 vec2ToAdd){
    vec2Arr[0] += vec2ToAdd.vec2Arr[0];
    vec2Arr[1] += vec2ToAdd.vec2Arr[1];
}

vector3::vector3(GLfloat f1, GLfloat f2, GLfloat f3) {
    vec3Arr[0] = f1;
    vec3arr[1] = f2;
    vec3arr[2] = f3;
}
vector3::normalizeVec3() {
  if(vec3Arr[0] != 0 && vec3Arr[1] != 0 && vec3Arr[2] != 0) { // || ??
    vec3Arr[0] /= sqrt(pow(vec3Arr[0], 2) + pow(vec3Arr[1], 2) + pow(vec3Arr[2], 2));
    vec3Arr[1]/ = sqrt(pow(vec3Arr[0], 2) + pow(vec3Arr[1], 2) + pow(vec3Arr[2], 2));
    vec3Arr[2] /= sqrt(pow(vec3Arr[0], 2) + pow(vec3Arr[1], 2) + pow(vec3Arr[2], 2));
  }
}

void vector3::add(vector3 vec3ToAdd){
    vec3Arr[0] += vec3ToAdd.vec3Arr[0];
    vec3Arr[1] += vec3ToAdd.vec3Arr[1];
    vec3Arr[2] += vec3ToAdd.vec3Arr[2];
}

vector4::vector4(GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4) {
    vec4Arr[0] = f1;
    vec4Arr[1] = f2;
    vec4Arr[2] = f3;
}

vector4::normalizeVec4() {
  if(vec4Arr[0] != 0 && vec4Arr[1] != 0 && vec4Arr[2] != 0 && vec4Arr[3] != 0) { // || ??
    vec4Arr[0] /= sqrt(pow(vec4Arr[0], 2) + pow(vec4Arr[1], 2) + pow(vec4Arr[2], 2));
    vec4Arr[1]/ = sqrt(pow(vec4Arr[0], 2) + pow(vec4Arr[1], 2) + pow(vec4Arr[2], 2));
    vec4Arr[2] /= sqrt(pow(vec4Arr[0], 2) + pow(vec4Arr[1], 2) + pow(vec4Arr[2], 2));
  }
}

void vector4::add(vector4 vec4ToAdd){
    vec4Arr[0] += vec4ToAdd.vec4Arr[0];
    vec4Arr[1] += vec4ToAdd.vec4Arr[1];
    vec4Arr[2] += vec4ToAdd.vec4Arr[2];
    vec4Arr[3] += vec4ToAdd.vec4Arr[3];
}
