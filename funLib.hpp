#include "common.hpp"
void norm(GLfloat vecs[]);
void matTranslatef(GLfloat matrix[], GLfloat x, GLfloat y, GLfloat z);
void multiMatrix(GLfloat result[], GLfloat matrix1[], GLfloat matrix2[]);
void cross(GLfloat res[], GLfloat vec1[], GLfloat vec2[]);
GLfloat dot(GLfloat vec1[], GLfloat vec2[]);
void glLookAtf(GLfloat Matrix[], GLfloat eyeVec[], GLfloat centerVec[], GLfloat upVec[]);
void rotatey(GLfloat Matrix[16], GLfloat aX, GLfloat aY, GLfloat aZ);

#endif
