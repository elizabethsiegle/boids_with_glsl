#ifndef MATS_H
#define MATS_H
class mat2 {
public:
  float mat2Arr[4];
  mat2(float, float, float, float);
  mat2 addMat2(mat2);
  mat2 multMat2(mat2);
  mat2 identityMat2();
  mat2 zeroMat2();
};

class mat3 {
public:
  float mat3Arr[9];
  mat3(float, float, float, float, float, float, float, float, float);
  mat3 addMat3(mat3);
  mat3 multMat3(mat3);
  mat3 identityMat3();
  mat3 zeroMat3();
};

//mat4
class mat4 {
public:
  float mat4Arr[16];
  float arrToTranspose[16];
  mat4(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);
  mat4 addMat4(mat4);
  mat4 multMat4(mat4);
  mat4 identityMat4();
  mat4 zeroMat4();
  void transpose();
};

#endif
