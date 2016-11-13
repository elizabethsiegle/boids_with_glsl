//vec2
#ifndef VECS_H
#define VECS_H

class vector2 {
public:
  float vec2Arr[2];
  vector2(GLfloat, GLfloat);
  void normalizeVec2();
  void vec2Add(vector2);
};

//vector3
class vector3 {
public:
  float vec3Arr[3];
  vector3(GLfloat, GLfloat,GLfloat);
  void normalizeVec3();
  void add(vector3);
};

//vector4
class vector4 {
public:
  float vec4Arr[4];
  vector4(GLfloat, GLfloat,GLfloat, GLfloat);
  vector4::normalizeVec4();
  void add(vector4);
};

#endif
