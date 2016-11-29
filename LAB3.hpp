#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#ifdef __APPLE__
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#import <OpenGL/gl.h>
#else
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#endif



//Create a NULL-terminated string by reading the provided file
static char* readShaderSource(const char* shaderFile) {
  FILE* fp = fopen(shaderFile, "r");

  if ( fp == NULL ) { return NULL; }
  fseek(fp, 0L, SEEK_END);
  long size = ftell(fp);
  fseek(fp, 0L, SEEK_SET);
  char* buf = (char *) malloc(size + 1);
  fread(buf, 1, size, fp);

  buf[size] = '\0';
  fclose(fp);

  return buf;
}
// Create a GLSL program object from vertex and fragment shader files
GLuint initshader(const char* vShaderFile, const char* fShaderFile){
  struct Shader {
    const char*  filename;
    GLenum type;
    GLchar* source;
  }
  shaders[2] = {
    {vShaderFile, GL_VERTEX_SHADER, NULL},
    {fShaderFile, GL_FRAGMENT_SHADER, NULL}
  };
  GLuint program = glCreateProgram();
  int i;
  struct Shader *s;
  GLint  shader, compiled, linked, logSize;
  char *logMsg;
  for (i = 0; i < 2; ++i) {
    s = &shaders[i];
    s->source = readShaderSource(s->filename);
    if (shaders[i].source == NULL) {
      fprintf(stderr, "Failed to read %s\n", s->filename);
      exit(EXIT_FAILURE);
    }
    shader = glCreateShader(s->type);
    glShaderSource(shader, 1, (const GLchar**) &s->source, NULL);
    glCompileShader(shader );
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
      fprintf(stderr, "%s failed to compile\n", s->filename);
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
      logMsg = (char *) malloc(logSize);
      glGetShaderInfoLog(shader, logSize, NULL, logMsg);
      fprintf(stderr, "%s\n", logMsg);
      free(logMsg);
      exit( EXIT_FAILURE );
    }
    free(s->source);
    glAttachShader(program, shader);
  }
  /* link  and error check */
  glLinkProgram(program);
  glGetProgramiv( program, GL_LINK_STATUS, &linked );
  if ( !linked ) {
    fprintf(stderr, "Shader program failed to link\n");
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
    logMsg = (char *) malloc(logSize);
    glGetProgramInfoLog(program, logSize, NULL, logMsg);
    fprintf(stderr, "%s\n", logMsg);
    free(logMsg);
    exit( EXIT_FAILURE );
  }
  return program;
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

    for(i = 0; i < 4; i++) {
      for(j = 0; j < 4; j++) {
        mat1[i][j] = matrix1[count];
	      mat2[i][j] = matrix2[count];
        count++;
      }
    }
    i = j = 0;
    for(i = 0; i < 4; i++) { //for each element in a column
       for(j = 0; j < 4; j++) { //for each element in a row
         tot = 0;
         for(k = 0; k < 4; k++) {//add togther multiplied rows
           tot +=  mat1[i][k] * mat2[k][j];
         } //for
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
void glLookAtf(GLfloat Matrix[], GLfloat eyeVec[], GLfloat centerVec[], GLfloat upVec[]) {
  GLfloat forward[3], side[3], up[3];//size 3
  GLfloat matrix2[16];
  GLfloat resultMatrix[16]; //size 16
   //Source: https://www.opengl.org/sdk/docs/man2/xhtml/gluLookAt.xml
   //col major
   forward[0] = centerVec[0] - eyeVec[0];
   forward[1] = centerVec[1] - eyeVec[1];
   forward[2] = centerVec[2] - eyeVec[2];
   norm(forward);

   //Side = forward x up
   cross(side, forward, upVec);
   norm(side);

   //up = side x forward
   cross(up, side, forward);
   norm(up);

   matrix2[0] = side[0];
   matrix2[4] = side[1];
   matrix2[8] = side[2];

   matrix2[1] = up[0];
   matrix2[5] = up[1];
   matrix2[9] = up[2];

   matrix2[2] = -forward[0];
   matrix2[6] = -forward[1];
   matrix2[10] = -forward[2];

   matrix2[12] = matrix2[13] = matrix2[14] = 0.0;
   matrix2[3] = matrix2[7] = matrix2[11] = 0.0;
   matrix2[15] = 1.0;

   //side[0] side[1] side[2] 0
   //up[0] up[1] up[2] 0
   //-forward[0] -forward[1] -forward[2] 0
   //0 0 0 1

   //multiply by modelview
   multiMatrix(resultMatrix, Matrix, matrix2);
   matTranslatef(resultMatrix, -eyeVec[0], -eyeVec[1], -eyeVec[2]);

   multiMatrix(Matrix, Matrix, matrix2);
   matTranslatef(Matrix, -eyeVec[0], -eyeVec[1], -eyeVec[2]);

   //save in Matrix
   memcpy(Matrix, resultMatrix, 16*sizeof(float));
}

void rotatey(GLfloat Matrix[16], GLfloat aX, GLfloat aY, GLfloat aZ) {
  //Matrix = modelview matrix
  //angles are in degrees
  GLfloat resultMatrix[16];

  GLfloat xRot[16] = {
    1, 0, 0, 0,
    0, cos(aX), sin(aX), 0,
    0, -1*sin(aX), cos(aX), 0,
		0, 0, 0, 1
  };

  GLfloat yRot [16] = {
    cos(aY), 0, -1*sin(aY), 0,
		0, 1, 0, 0,
		sin(aY), 0, cos(aY), 0,
		0, 0, 0, 1
  };

  GLfloat zRot [16] = {
    cos(aZ), sin(aZ), 0, 0,
    -1*sin(aZ), cos(aZ), 0,
		0, 0, 0, 1,
		0, 0, 0, 0, 1
  };
   //multiply by modelview
   multiMatrix(Matrix, Matrix, xRot);
   multiMatrix(Matrix, Matrix, yRot);
   multiMatrix(Matrix, Matrix, zRot);

   //resultMatrix = matTranslatef(resultMatrix, -eyeVec[0], -eyeVec[1], -eyeVec[2]);
   //save in Matrix
   memcpy(Matrix, resultMatrix, 16*sizeof(float));
}
