#include "mats.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
// class mat2 {
// public:
//   GLfloat mat2Arr[4];
//   mat2(GLfloat, GLfloat, GLfloat, GLfloat);
//   mat2 addMat2(mat2);
//   mat2 multMat2(mat2);
//   mat2 identityMat2();
// };

mat2::mat2(GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4) {
  mat2Arr[0] = f1;
  mat2Arr[1] = f2;
  mat2Arr[2] = f3;
  mat2Arr[3] = f4;
}

mat2 mat2::addMat2(mat2 matrix2Add) {
  return mat2(
    (mat2Arr[0] + matrix2Add.mattToArr[0]),
    (mat2Arr[1] + matrix2Add.mattToArr[1]),
    (mat2Arr[2] + matrix2Add.mattToArr[2]),
    (mat2Arr[3] + matrix2Add.mattToArr[3])
  );
}

mat2 mat2::multMat2(mat2 matrix2Multiply) {
  return mat2(
    (mat2Arr[0] * matrix2Multiply.mattToArr[0] + mat2Arr[1] * matrix2Multiply.mat2Arr[2]),
    (mat2Arr[0] * matrix2Multiply.mattToArr[1] + mat2Arr[1] * matrix2Multiply.mat2Arr[3]),
    (mat2Arr[2] * matrix2Multiply.mattToArr[0] + mat2Arr[3] * matrix2Multiply.mat2Arr[2]),
    (mat2Arr[2] * matrix2Multiply.mattToArr[1] + mat2Arr[3] * matrix2Multiply.mat2Arr[3])
  )
}

mat2 mat2::identityMat2() {
  return mat2(
    1, 0,
    0, 1);
}

//mat3
// class mat3 {
// public:
//   GLfloat mat3Arr[9];
//   mat3(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
//   mat3 addMat3(mat3);
//   mat3 multMat3(mat3);
//   mat3 identityMat3();
// };

mat3::mat3(GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4, GLfloat f5, GLfloat f6, GLfloat f7, GLfloat f8, GLfloat f9) {
  mat3Arr[0] = f1;
  mat3Arr[1] = f2;
  mat3Arr[2] = f3;
  mat3Arr[3] = f4;
  mat3Arr[4] = f5;
  mat3Arr[5] = f6;
  mat3Arr[6] = f7;
  mat3Arr[7] = f8;
  mat3Arr[8] = f9;
}

mat3 mat3::addMat3(mat3 matrix3Add) {
  return mat3(
    (mat3Arr[0] + matrix3Add.mattToArr[0]),
    (mat3Arr[1] + matrix3Add.mattToArr[1]),
    (mat3Arr[2] + matrix3Add.mattToArr[2]),
    (mat3Arr[3] + matrix3Add.mattToArr[3]),
    (mat3Arr[4] + matrix3Add.mattToArr[4]),
    (mat3Arr[5] + matrix3Add.mattToArr[5]),
    (mat3Arr[6] + matrix3Add.mattToArr[6]),
    (mat3Arr[7] + matrix3Add.mattToArr[7]),
    (mat3Arr[8] + matrix3Add.mattToArr[8])
  );
}

mat3 mat3::multMat3(mat3 matrix3Multiply) {
  return mat3(
    (mat3Arr[0] * matrix3Multiply.mattToArr[0] + mat3Arr[1] * matrix3Multiply.mat3Arr[3] + mat3Arr[2] * matrix3Multiply.mat3Arr[6] ),
    (mat3Arr[0] * matrix3Multiply.mattToArr[1] + mat3Arr[1] * matrix3Multiply.mat3Arr[4] + mat3Arr[2] * matrix3Multiply.mat3Arr[7]),
    (mat3Arr[0] * matrix3Multiply.mattToArr[2] + mat3Arr[1] * matrix3Multiply.mat3Arr[5] + mat3Arr[2] * matrix3Multiply.mat3Arr[8]),
    (mat3Arr[3] * matrix3Multiply.mattToArr[0] + mat3Arr[4] * matrix3Multiply.mat3Arr[3] + mat3Arr[5] * matrix3Multiply.mat3Arr[6]),
    (mat3Arr[3] * matrix3Multiply.mattToArr[1] + mat3Arr[4] * matrix3Multiply.mat3Arr[4] + mat3Arr[5] * matrix3Multiply.mat3Arr[7]),
    (mat3Arr[3] * matrix3Multiply.mattToArr[2] + mat3Arr[4] * matrix3Multiply.mat3Arr[5] + mat3Arr[5] * matrix3Multiply.mat3Arr[8]),
    (mat3Arr[6] * matrix3Multiply.mattToArr[0] + mat3Arr[7] * matrix3Multiply.mat3Arr[3] + mat3Arr[8] * matrix3Multiply.mat3Arr[6]),
    (mat3Arr[6] * matrix3Multiply.mattToArr[1] + mat3Arr[7] * matrix3Multiply.mat3Arr[4] + mat3Arr[8] * matrix3Multiply.mat3Arr[7]),
    (mat3Arr[6] * matrix3Multiply.mattToArr[2] + mat3Arr[7] * matrix3Multiply.mat3Arr[5] + mat3Arr[8] * matrix3Multiply.mat3Arr[8])
  )
}

mat3 mat3::identityMat3() {
  return mat2(
    1, 0, 0,
    0, 1, 0,
    0, 0, 1
  );
}

//mat4
// class mat4 {
// public:
//   GLfloat mat4Arr[16];
//   mat4(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
//   mat4 addMat4(mat4);
//   mat4 multMat4(mat4);
//   mat4 identityMat4();
//   void transpose();
// };

mat4::mat4(GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4, GLfloat f5, GLfloat f6, GLfloat f7, GLfloat f8, GLfloat f9, GLfloat f10, GLfloat f11, GLfloat f12, GLfloat f13, GLfloat f14, GLfloat f15, GLfloat f16) {
  mat4Arr[0] = f1;
  mat4Arr[1] = f2;
  mat4Arr[2] = f3;
  mat4Arr[3] = f4;
  mat4Arr[4] = f5;
  mat4Arr[5] = f6;
  mat4Arr[6] = f7;
  mat4Arr[7] = f8;
  mat4Arr[8] = f9;
  mat4Arr[9] = f10;
  mat4Arr[10] = f11;
  mat4Arr[11] = f12;
  mat4Arr[12] = f13;
  mat4Arr[13] = f14;
  mat4Arr[14] = f15;
  mat4Arr[15] = f16;
}

mat4 mat4::addMat4(mat4 matrix4Add) {
  return mat4(
    (mat4Arr[0] + matrix4Add.mattToArr[0]),
    (mat4Arr[1] + matrix4Add.mattToArr[1]),
    (mat4Arr[2] + matrix4Add.mattToArr[2]),
    (mat4Arr[3] + matrix4Add.mattToArr[3]),
    (mat4Arr[4] + matrix4Add.mattToArr[4]),
    (mat4Arr[5] + matrix4Add.mattToArr[5]),
    (mat4Arr[6] + matrix4Add.mattToArr[6]),
    (mat4Arr[7] + matrix4Add.mattToArr[7]),
    (mat4Arr[8] + matrix4Add.mattToArr[8]),
    (mat4Arr[9] + matrix4Add.mattToArr[9]),
    (mat4Arr[10] + matrix4Add.mattToArr[10]),
    (mat4Arr[11] + matrix4Add.mattToArr[11]),
    (mat4Arr[12] + matrix4Add.mattToArr[12]),
    (mat4Arr[13] + matrix4Add.mattToArr[13]),
    (mat4Arr[14] + matrix4Add.mattToArr[14]),
    (mat4Arr[15] + matrix4Add.mattToArr[15])
  );
}

mat4 mat4::multMat4(mat4 matrix4Multiply) {
  return mat4(
    (mat4Arr[0] * matrix4Multiply.mat4Arr[0] + mat4Arr[1] * matrix4Multiply.mat4Arr[4] + mat4Arr[2] * matrix4Multiply.mat4Arr[8] + mat4Arr[3] * matrix4Multiply.mat4Arr[12] ),
    (mat4Arr[0] * matrix4Multiply.mat4Arr[1] + mat4Arr[1] * matrix4Multiply.mat4Arr[5] + mat4Arr[2] * matrix4Multiply.mat4Arr[9] + mat4Arr[3] * matrix4Multiply.mat4Arr[13] ),
    (mat4Arr[0] * matrix4Multiply.mat4Arr[2] + mat4Arr[1] * matrix4Multiply.mat4Arr[6] + mat4Arr[2] * matrix4Multiply.mat4Arr[10] + mat4Arr[3] * matrix4Multiply.mat4Arr[14] ),
    (mat4Arr[0] * matrix4Multiply.mat4Arr[3] + mat4Arr[1] * matrix4Multiply.mat4Arr[7] + mat4Arr[2] * matrix4Multiply.mat4Arr[11] + mat4Arr[3] * matrix4Multiply.mat4Arr[15] ),
    (mat4Arr[4] * matrix4Multiply.mat4Arr[0] + mat4Arr[5] * matrix4Multiply.mat4Arr[4] + mat4Arr[6] * matrix4Multiply.mat4Arr[8] + mat4Arr[7] * matrix4Multiply.mat4Arr[12] ),
    (mat4Arr[4] * matrix4Multiply.mat4Arr[1] + mat4Arr[5] * matrix4Multiply.mat4Arr[5] + mat4Arr[6] * matrix4Multiply.mat4Arr[9] + mat4Arr[7] * matrix4Multiply.mat4Arr[13] ),
    (mat4Arr[4] * matrix4Multiply.mat4Arr[2] + mat4Arr[5] * matrix4Multiply.mat4Arr[6] + mat4Arr[6] * matrix4Multiply.mat4Arr[10] + mat4Arr[7] * matrix4Multiply.mat4Arr[14] ),
    (mat4Arr[4] * matrix4Multiply.mat4Arr[3] + mat4Arr[5] * matrix4Multiply.mat4Arr[7] + mat4Arr[6] * matrix4Multiply.mat4Arr[11] + mat4Arr[7] * matrix4Multiply.mat4Arr[15] ),
    (mat4Arr[8] * matrix4Multiply.mat4Arr[0] + mat4Arr[9] * matrix4Multiply.mat4Arr[4] + mat4Arr[10] * matrix4Multiply.mat4Arr[8] + mat4Arr[11] * matrix4Multiply.mat4Arr[12] ),
    (mat4Arr[8] * matrix4Multiply.mat4Arr[1] + mat4Arr[9] * matrix4Multiply.mat4Arr[5] + mat4Arr[10] * matrix4Multiply.mat4Arr[9] + mat4Arr[11] * matrix4Multiply.mat4Arr[13] ),
    (mat4Arr[8] * matrix4Multiply.mat4Arr[2] + mat4Arr[9] * matrix4Multiply.mat4Arr[6] + mat4Arr[10] * matrix4Multiply.mat4Arr[10] + mat4Arr[11] * matrix4Multiply.mat4Arr[14] ),
    (mat4Arr[8] * matrix4Multiply.mat4Arr[3] + mat4Arr[9] * matrix4Multiply.mat4Arr[7] + mat4Arr[10] * matrix4Multiply.mat4Arr[11] + mat4Arr[11] * matrix4Multiply.mat4Arr[15] ),
    (mat4Arr[12] * matrix4Multiply.mat4Arr[0] + mat4Arr[13] * matrix4Multiply.mat4Arr[4] + mat4Arr[14] * matrix4Multiply.mat4Arr[8] + mat4Arr[15] * matrix4Multiply.mat4Arr[12] ),
    (mat4Arr[12] * matrix4Multiply.mat4Arr[1] + mat4Arr[13] * matrix4Multiply.mat4Arr[5] + mat4Arr[14] * matrix4Multiply.mat4Arr[9] + mat4Arr[15] * matrix4Multiply.mat4Arr[13] ),
    (mat4Arr[12] * matrix4Multiply.mat4Arr[2] + mat4Arr[13] * matrix4Multiply.mat4Arr[6] + mat4Arr[14] * matrix4Multiply.mat4Arr[10] + mat4Arr[15] * matrix4Multiply.mat4Arr[14] ),
    (mat4Arr[12] * matrix4Multiply.mat4Arr[3] + mat4Arr[13] * matrix4Multiply.mat4Arr[7] + mat4Arr[14] * matrix4Multiply.mat4Arr[11] + mat4Arr[15] * matrix4Multiply.mat4Arr[15] )
  );
}

mat4 mat4::identityMat4() {
  return mat4(
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0
  );
}

mat4 mat4::transpose() {
  float arrToTranspose[16] = {
    mat4Arr[0], mat4Arr[1], mat4Arr[2], mat4Arr[3],
    mat4Arr[4], mat4Arr[5], mat4Arr[6], mat4Arr[7],
    mat4Arr[8], mat4Arr[9], mat4Arr[10], mat4Arr[11],
    mat4Arr[12], mat4Arr[13], mat4Arr[14], mat4Arr[15]
  };
  //reset
  mat4Arr[1] = arrToTranspose[4];
  mat4Arr[2] = arrToTranspose[8];
  mat4Arr[3] = arrToTranspose[12];
  mat4Arr[4] = arrToTranspose[1];
  //mat4Arr[5] = arrToTranspose[5];
  mat4Arr[6] = arrToTranspose[9];
  mat4Arr[7] = arrToTranspose[13];
  mat4Arr[8] = arrToTranspose[2];
  mat4Arr[9] = arrToTranspose[6];
  mat4Arr[10] = arrToTranspose[4];
  mat4Arr[11] = arrToTranspose[14];
  mat4Arr[12] = arrToTranspose[3];
  mat4Arr[13] = arrToTranspose[7];
  mat4Arr[14] = arrToTranspose[11];
  mat4Arr[15] = arrToTranspose[4];
}
