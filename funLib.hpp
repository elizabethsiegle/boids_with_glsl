#include "common.hpp"

void getHeading(GLfloat heading[], GLfloat prev[], GLfloat next[]) {
  for(int i; i < 3; i++) {
    heading[i] = next[i] - prev[i];
  }
}

GLfloat square(GLfloat s) {
  float sqr;
  sqr = s*s;
  return sqr;
}

GLfloat dist(GLfloat x, GLfloat y, GLfloat z, GLfloat x2, GLfloat y2, GLfloat z2) {
  GLfloat distance;
  distance = sqrt(square(x2-x)+square(y2-y)+square(z2-z));
  return distance;
}

GLfloat mag(GLfloat vecs[3]) {
  GLfloat mags;
  mags = sqrt(square(vecs[0])+square(vecs[1])+square(vecs[2]));
  return mags;
}

GLfloat deter4x4(GLfloat mat[]) {
  GLfloat det = mat[4]*(mat[14]*mat[11]+mat[10]*mat[15])+mat[8]*(mat[6]*mat[15]+mat[7]*mat[14])+mat[12]*(mat[6]*mat[11]+mat[7]*mat[9]);
  return det;
}

GLfloat trace4x4(GLfloat Matrix[]) {
  //increment = (size-1)/width
  GLfloat tray = Matrix[0]+Matrix[5]+Matrix[10]+Matrix[15];
  return tray;
}

void norm(GLfloat vecs[]) {
   GLfloat m = sqrt(vecs[0]*vecs[0] + vecs[1]*vecs[1] + vecs[2]*vecs[2]);
   vecs[0] = vecs[0]/m;
   vecs[1] = vecs[1]/m;
   vecs[2] = vecs[2]/m;
   //return vecs;
}

void matTranslatef(GLfloat matrix[], GLfloat x, GLfloat y, GLfloat z) {
	matrix[12]=matrix[0]*x+matrix[4]*y+matrix[8]*z+matrix[12];
	matrix[13]=matrix[1]*x+matrix[5]*y+matrix[9]*z+matrix[13];
	matrix[14]=matrix[2]*x+matrix[6]*y+matrix[10]*z+matrix[14];
	matrix[15]=matrix[3]*x+matrix[7]*y+matrix[11]*z+matrix[15];
}

void multiMatrix(GLfloat result[], GLfloat matrix1[], GLfloat matrix2[]) {
    GLfloat tot;
    GLfloat mat1[4][4];
    GLfloat mat2[4][4];
    int i = 0;
    int j = 0;
    int k = 0;
    int count = 0;

    //convert to matrix for multiplication
    for(i = 0; i < 4; i++) {
      for(j = 0; j < 4; j++) {
	mat1[i][j] = matrix1[count];
	mat2[i][j] = matrix2[count];
	count++;
      }
    }

    i = j = count = 0;

    for(i = 0; i < 4; i++) { //for each element in a column
       for(j = 0; j < 4; j++) { //for each element in a row
         tot = 0;
         for(k = 0; k < 4; k++) {//add togther multiplied rows
           tot +=  mat1[i][k] * mat2[k][j];
         }
         result[count] = tot;
         count++;
      }
    }
}

void cross(GLfloat res[], GLfloat vec1[], GLfloat vec2[]) {
  res[0] = vec1[1]*vec2[2]-vec1[2]*vec2[1];
  res[1] = vec1[2]*vec2[0]-vec1[0]*vec2[2];
  res[2] = vec1[0]*vec2[1]-vec1[1]*vec2[0];
  //return res;
}

GLfloat dot(GLfloat vec1[], GLfloat vec2[]) {
  GLfloat DOT = vec1[0]*vec2[0] + vec1[1]*vec2[1] + vec1[2]*vec2[2];
  return DOT;
}


//void glLookAtf(GLfloat Matrix[16], GLfloat eyeVec[3], GLfloat centerVec[3], GLfloat upVec[3]) {

void glLookAtf(GLfloat Matrix[], GLfloat eye[], GLfloat center[], GLfloat upVec[]) {
   //Source: https://www.opengl.org/sdk/docs/man2/xhtml/gluLookAt.xml
   //column major
  GLfloat f[3], u[3], s[3];//size 3
   GLfloat matrix2[16];
   GLfloat tempMat[16];

   f[0] = center[0] - eye[0];
   f[1] = center[1] - eye[1];
   f[2] = center[2] - eye[2];
   norm(f);

   cross(s, f, upVec);
   norm(s);
   cross(u, s, f);
   norm(u);

   matrix2[0] = s[0];
   matrix2[4] = s[1];
   matrix2[8] = s[2];
   matrix2[12] = 0;

   matrix2[1] = u[0];
   matrix2[5] = u[1];
   matrix2[9] = u[2];
   matrix2[13] = 0;

   matrix2[2] = -f[0];
   matrix2[6] = -f[1];
   matrix2[10] = -f[2];
   matrix2[14] = 0;

   matrix2[3] = matrix2[7] = matrix2[11] = 0.0;
   matrix2[15] = 1.0;

   //side[0] side[1] side[2] 0
   //up[0] up[1] up[2] 0
   //-forward[0] -forward[1] -forward[2] 0
   //0 0 0 1;

   matTranslatef(matrix2, -eye[0], -eye[1], -eye[2]);
   GLfloat temp[16];
   for(int i = 0; i < 16; i++){
     temp[i] = Matrix[i];
   }
   multiMatrix(Matrix, temp, matrix2);
}

void glperp(GLfloat Matrix[], GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar){
  //Source: https://www.opengl.org/sdk/docs/man2/xhtml/gluPerspective.xml
  GLfloat f;
  f = 1/(tan(fovy*M_PI/360));
  GLfloat Matrix2[16];

  Matrix2[0] = f/aspect;
  Matrix2[4] = 0;
  Matrix2[8] = 0;
  Matrix2[12] = 0;

  Matrix2[1] = 0;
  Matrix2[5] = f;
  Matrix2[9] = 0;
  Matrix2[13] = 0;

  Matrix2[2] = 0;
  Matrix2[6] = 0;
  Matrix2[10] = ((zFar-zNear)/(zNear-zFar));
  Matrix2[14] = ((2*zFar*zNear)/(zNear-zFar));

  Matrix2[3] = 0;
  Matrix2[7] = 0;
  Matrix2[11] = -1;
  Matrix2[15] = 0; //corner

  multiMatrix(Matrix, Matrix, Matrix2);
}

void rotatef(GLfloat Matrix[], GLfloat angle, GLfloat ax, GLfloat ay, GLfloat az) {
  GLfloat a, b, c, v;
  v = sqrt(square(ax)+square(ay)+square(az));
  a = ax/v;
  b = ay/v;
  c = az/v;
  GLfloat rot[16] = {
    (square(a)+(1-square(a))*cos(angle)), (a*b*(1-cos(angle))-c*sin(angle)), (a*c*(1-cos(angle))+b*sin(angle)), 0,
    (a*b*(1-cos(angle))+c*sin(angle)), (square(b)+(1-square(b))*cos(angle)), (b*c*(1-cos(angle))-a*sin(angle)), 0,
    (a*c*(1-cos(angle))-b*sin(angle)), (b*c*(1-cos(angle))+a*sin(angle)), (square(c)+(1-square(c))*cos(angle)), 0,
    0, 0, 0, 1};
  multiMatrix(Matrix, Matrix, rot);

}
