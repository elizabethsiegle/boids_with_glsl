//hw4
//hw4
//start with simple
//add header file after
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "GL/glew.h"
#ifdef __APPLE__
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#else
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#endif
#include "list.c"
#include "boid.h"
#include "environment.h"
// #include "LAB3.hpp"
//#include "initshader.h" //idky make_bo, initshader funcs !link
#include "initshader.hpp"
#include "mats.hpp"
// #include "vecs.hpp"
int view = 0;
//********Globals*******//
//Velocity, acceleration and heads
Node *velx = NULL;
Node *vely = NULL;
Node *velz = NULL;
Node *ax = NULL;
Node *ay = NULL;
Node *az = NULL;
float weightSp = .0005; //will go up, down based on key press
GLfloat boid_vertices[4][3];
//Sep, align and coh
Node *allx = NULL;
Node *ally = NULL;
Node *allz = NULL;
Node *sepx = NULL;
Node *sepy = NULL;
Node *sepz = NULL;
Node *cox = NULL;
Node *coy = NULL;
Node *coz = NULL;

GLuint make_bo(GLenum type, const void *buf, GLsizei buf_size) {
    GLuint bufnum;
    glGenBuffers(1, &bufnum);
    glBindBuffer(type, bufnum);
    glBufferData(type, buf_size, buf, GL_STATIC_DRAW);
    return bufnum;
}

unsigned dsize = sizeof(double);
unsigned bsize = sizeof(bool);
unsigned isize = sizeof(int);

GLfloat max[3] = {30, 30, 30};
GLfloat min[3] = {.1, .1, .1};
GLfloat direction[3];
GLfloat vel[3];
GLfloat target[3] = {.5, .5, .5};
GLfloat cToGm, midpt, rad = .1;
bool addB = false, minusB = false;
bool slower = false, faster = false;
bool pause = false, stepBool = false;
// //shading
GLuint program, vao, vbo1, vbo2, vbo3, vbo4,  pos, col, ind, MV;
//u = faster d = slower

void init() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glColor3f(0.0, 0.0, 0.0);
  glClearDepth(1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //gluPerpspective(where camera is places)
  gluPerspective(10, 1, 1, 20);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glLineWidth(3);
  //mat4 ModelViewMat = mat4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  //mat4 ProjectionMat = mat4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    glShadeModel(GL_SMOOTH);

    // //Initialize the vertex position attribute from the vertex shader

    col = glGetAttribLocation(program, "vCol");
    MV = glGetUniformLocation(program, "finalview");
    //create, init buffer obj
    vbo1 = make_bo(GL_ARRAY_BUFFER, boid_vertices, sizeof(boid_vertices));
    vbo2 = make_bo(GL_ARRAY_BUFFER, cube_vertices, sizeof(cube_vertices));
    vbo3 = make_bo(GL_ARRAY_BUFFER, tower_vertices, sizeof(tower_vertices));
    vbo4 = make_bo(GL_ELEMENT_ARRAY_BUFFER, cube_indices, sizeof(cube_indices));

    // glEnableVertexAttribArray(pos);
    // glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    // glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*) 0);
    // glEnableVertexAttribArray(col);
    // glVertexAttribPointer(col, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    // glVertexAttribPointer(col, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    // glVertexAttribPointer(col, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    program = initshader("hw4_vs.glsl", "hw4_fs.glsl");
    glUseProgram(program);
    //boid
    glGenVertexArrays(1, &vao); //boid vao
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    pos = glGetAttribLocation(program, "p0s");
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    //ed
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    col = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(col);
    glVertexAttribPointer(col, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    MV = glGetUniformLocation(program, "m");
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void moveTarget(int i, float spW){
    //x, y, z
    vel[0]=valF(headx, i, numBoid);
    vel[1]=valF(heady, i, numBoid);
    vel[2]=valF(headz, i, numBoid);
    for(int j = 0; j < 3; j++) {
      vel[j] = target[j]-vel[j];
      if(!pause) {
        vel[j] *= weightSp;
      }
      else {
        vel[j] *= 0;
      }
      // printf("%f", weightSp);
      // printf("\n");
    }
}

void separation() {
  //Method checks for nearby boids and steers away
  //collision function
  //checks for all boids so that they don't collide
  //array of boids with x, y, z's for all
  //GLfloat seper  = .08;
  //for(int i = 1; i <= numBoid; i++){
  //  addF(&headx, i, numBoid, seper);
  //}
}

void alignment() {
  // For every nearby boid in the system, calculate the average velocity
  //takes in:
  //-Velocity-
  //array boids
  //speed
  //speedGoal and acceleration rate that we want to reach goal at

  //-steering-
  //angle
  //normailzed vectors
  //goal point

  //nearest neighbor?
  //goal funtion
}

void cohesion() {
  //movement together function
  //center C
  //center of flock C
  //radius of flock
  //move toawrds center gradually but not at expence of colliding
  // For the average location (i.e. center) of all nearby boids, calculate steering vector towards that location
}

void seek() {
  //minus goal-currentPos
  //normalize?
  //
}

void defaultView(GLfloat centerFlock[3]) {
  //v
  gluLookAt(-1.3, .8, -1.3,
          //centerFlock[0]+cos(0)*(.8), centerFlock[1]+cos(0)*(.8), centerFlock[2]+cos(0)*(.8),
          centerFlock[0], centerFlock[1], centerFlock[2],
          0, 1, 0);
}

void sideView(GLfloat centerFlock[3]) {
  //s
  gluLookAt(-3, 0.4, 0.3,
          centerFlock[0]+cos(0)*(.3), centerFlock[1]+cos(0)*(.3), centerFlock[2]+cos(0)*(.3),
          //centerFlock[0], centerFlock[1], centerFlock[2],
          0, 1, 0);
}

void trailView(GLfloat centerFlock[3]) {
  //t
  gluLookAt(//-1.3, .8, -1.3,
          centerFlock[0]+cos(0)*(.8), centerFlock[1]+cos(0)*(.8), centerFlock[2]+cos(0)*(.8),
          centerFlock[0], centerFlock[1], centerFlock[2],
          0, 1, 0);
}

GLfloat normX(GLfloat x, GLfloat y, GLfloat z, GLfloat x2, GLfloat y2, GLfloat z2) {
  GLfloat mag = sqrt(x*x2 + y*y2 + z*z2);
  x = x2/mag;
  return x;
}

GLfloat normY(GLfloat x, GLfloat y, GLfloat z, GLfloat x2, GLfloat y2, GLfloat z2) {
  GLfloat mag = sqrt(x*x2 + y*y2 + z*z2);
  y = y2/mag;
  return y;
}


GLfloat normZ(GLfloat x, GLfloat y, GLfloat z, GLfloat x2, GLfloat y2, GLfloat z2) {
  GLfloat mag = sqrt(x*x2 + y*y2 + z*z2);
  z = z2/mag;
  return z;
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

void reshape(GLFWwindow *w, int width, int height){
  printf("Got a Reshape Event");
  printf(":\t width = %d height = %d\n", width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1, 1, -1, 1, 0.4, 15);
  glMatrixMode(GL_MODELVIEW);
  // Set the new viewport size
  glViewport(0, 0, width, height);
}

/*void framebuffer_resize(GLFWwindow *wind, int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (double)w/RESIZE_FACTOR, (double)h/RESIZE_FACTOR, 0.0);
    glMatrixMode(GL_MODELVIEW);
    }*/

void normalize(int i) {
   GLfloat xu = valF(headx, i, numBoid);
   GLfloat yu = valF(heady, i, numBoid);
   GLfloat zu = valF(headz, i, numBoid);
   GLfloat m = 1/sqrt(xu*xu + yu*yu + zu*zu);
   multiF(&headx, i, numBoid, m);
   multiF(&heady, i, numBoid, m);
   multiF(&headz, i, numBoid, m);
}

void step(GLfloat goal[3]){
  printf("\n___Step___ \n");
  printf("Goal");
  for(int i = 0; i < 3; i++) {
    printf("%f ", goal[i]);
   }
  printf("/n");
  GLfloat temp[3];

  for(int i = 1; i <= numBoid; i++) {
    printf("curent pos of");
    printf("%d ", i);
    temp[0] = valF(headx, i, numBoid);
    temp[1] = valF(heady, i, numBoid);
    temp[2] = valF(headz, i, numBoid);
    for(int j = 0; j < 3; j++) {
      printf(" %f ", temp[j]);
    }
    printf("\n");
  }
}

void keyboard(GLFWwindow *w, int key, int scancode, int action, int mods) {
  //quit
  switch(key) {
   case GLFW_KEY_ESCAPE :
   case 'q' :
   case 'Q' :
    printf("end\n");
    glfwSetWindowShouldClose(w, GL_TRUE);
    break;
  case 'v' :
  case 'V' :
    view = DEFAULT;
    break;
  case 't' :
  case 'T' :
    view = TRAILING;
    break;
  case 's':
  case 'S' :
    view = SIDE;
  break;
  default:
  break;
  }
   //steering and speed
   //general - step, pause, views, and add and minus boids
   switch(action) {
     case GLFW_PRESS:
        switch(key) {
	case GLFW_KEY_ENTER:
           addBoid();
        break;
        case GLFW_KEY_END:
         minusBoid();
        break;
        case GLFW_KEY_SPACE:
	       stepBool = true;
        break;

        case GLFW_KEY_UP:
	  target[1] += .1;
        break;
        case GLFW_KEY_DOWN:
	  if(target[1] > .05) {
	    target[1] -= .1;
	  } else {
	    printf("target can not go any lower!");
	  }
        break;
        case GLFW_KEY_LEFT:
	  target[0] += .1;
        break;
        case GLFW_KEY_RIGHT:
	  target[0] -= .1;
        break;
        //speed up
        case 'U':
        case 'u':
          weightSp+=0.0002;
	  //given plus or minus x value calulate y value
        break;
        //slow down
        case 'D':
        case 'd':
          if(weightSp > 0) {
            weightSp-=0.0002;
          }
          else {
            weightSp = .000100;
          }
        break;
        case 'P':
        case 'p':
          pause = !pause;
        break;
        default:
          break;
      }
        default:
        break;
     }
}

void render() {
  //*********draw*********//
  float mult;
  draw_cube();
  draw_tower();
  GLfloat temp[3];
  for(int i = 1; i <= numBoid; i++){
    if(!pause) {
      mult = weightSp;
    }
    else {
      mult = 0;
    }
    moveTarget(i, mult);
    temp[0] = valF(headx, i, numBoid) + vel[0];
    temp[1] = valF(heady, i, numBoid) + vel[1];
    temp[2] = valF(headz, i, numBoid) + vel[2];
    draw_boid(temp);
    printf("%d", i);
    printf("\n");
    printf("%d", headx);
    printf("\n");
    //update values
    addF(&headx, i, numBoid, vel[0]);
    addF(&heady, i, numBoid, vel[1]);
    addF(&headz, i, numBoid, vel[2]);
    } //for
  }

int main(int argc, char **argv) {
  GLFWwindow* window;

  glColor3f(1.0, 1.0, 0.0);
  //GLfloat cenFlock[3] = {target[0]-rad, target[1], target[2]};
  //GLfloat cenFlock[3] = {2, 2, 2};
  srand(time(NULL));

  // Initialize the library
  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }
  // Create a window and its OpenGL context
  window = glfwCreateWindow(850, 800, "hw4!", NULL, NULL);
  if (!window){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
      glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
      glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
      glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  //events
  glfwSetWindowPos(window, 100, 100);
  glfwMakeContextCurrent(window);
  glfwSetWindowSizeCallback(window, reshape);
  glfwSetKeyCallback(window, keyboard);
  //glfwMakeContextCurrent(window);
  //glfwSetFramebufferSizeCallback(window, framebuffer_resize);

  init();
  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window)) {
    // if(!pause) {
      //goal[2] += .0005;
      //cenFlock[2] += .0005;
      //*******setup**********//
      //LIST
      //push(&headd, &aa, dsize);
      //printList(headi, printI);
      // int e = valD(headi, 0, 4);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearDepth(1.0);
      glLoadIdentity();
      if(view == DEFAULT) {
	       defaultView(target);
      } else if (view == SIDE) {
	       sideView(target);
      } else {
	       trailView(target);
      }
      //bool dview = true, sideVw = false, tView = false;

      //********update*********//
      //spead, number of birds, weight adjustment
      render();
      //seperate();
      //allignment();
      //cohesion();


      //*****end process*****//
      glfwSwapBuffers(window);
      glfwPollEvents();
      // if(stepBool == true) {
      //   step(target);
      // }
      //stepBool = false;

      //print
      /*for(int h = 1; h <= numBoid; h++) {
       printf("curent pos of");
       printf("%d ", h);
       temp[0] = valF(headx, h, numBoid);
       temp[1] = valF(heady, h, numBoid);
       temp[2] = valF(headz, h, numBoid);
       for(int l = 0; l < 3; l++) {
           printf(" %f ", temp[l]);
       }
       printf("\n");
       }*/
    //  } //if statement
    //  else {
    //    printf("why");
    //  }
  }//while

  glfwTerminate();
  exit(EXIT_SUCCESS);
}
//start with simple
//add header file after
// #include "initshader.hpp"
// #include <stdlib.h>
// #include <stdio.h>
// #include <math.h>
// #include <time.h>
// #include <GL/glew.h>
// #include <stdbool.h>
// #include <GLFW/glfw3.h>
// #include <GL/glu.h>
// #include <GL/glut.h>
// #include <memory.h>
// #include "list.c"
// #include "list.h"
// #include "common.hpp"
// #include "vecs.hpp"
// #include "mats.hpp"
// // #include "LAB3.hpp"
// #define X 1.3
// #define Y 0
// #define Z 1.3
// #define TX .03
// #define TY .2
// #define TZ .03
// enum {DEFAULT, TRAILING, SIDE}; // 0, 1, 2
// int view = 0;
//
// //********Globals*******//
// Node *headx = NULL;
// Node *heady = NULL;
// Node *headz = NULL;
// unsigned dsize = sizeof(double);
// unsigned bsize = sizeof(bool);
// unsigned isize = sizeof(int);
// unsigned fsize = sizeof(float);
// int numBoid = 0;
// GLfloat boid_vertices[4][3]; //need to declare??
//
// GLfloat max[3] = {30, 30, 30};
// GLfloat min[3] = {.1, .1, .1};
// GLfloat direction[3];
// GLfloat velocity = .001;
// GLfloat steerTo[3] = {0, 0, 0};
// GLfloat cToGm, midpt, rad = .1;
// bool lArw = false, rArw = false, upArw = false, downArw = false, addB = false, minusB = false;
// bool slower = false, faster = false, pause = false, stepBool = false;
// //u = faster d = slower
// //Create a NULL-terminated string by reading the provided file
// // static char* readShaderSource(const char* shaderFile) {
// //   FILE* fp = fopen(shaderFile, "r");
// //
// //   if ( fp == NULL ) { return NULL; }
// //   fseek(fp, 0L, SEEK_END);
// //   long size = ftell(fp);
// //   fseek(fp, 0L, SEEK_SET);
// //   char* buf = (char *) malloc(size + 1);
// //   fread(buf, 1, size, fp);
// //
// //   buf[size] = '\0';
// //   fclose(fp);
// //
// //   return buf;
// // }
// // // Create a GLSL program object from vertex and fragment shader files
// // GLuint initshader(const char* vShaderFile, const char* fShaderFile){
// //   struct Shader {
// //     const char*  filename;
// //     GLenum type;
// //     GLchar* source;
// //   }
// //   shaders[2] = {
// //     {vShaderFile, GL_VERTEX_SHADER, NULL},
// //     {fShaderFile, GL_FRAGMENT_SHADER, NULL}
// //   };
// //   GLuint program = glCreateProgram();
// //   int i;
// //   struct Shader *s;
// //   GLint  shader, compiled, linked, logSize;
// //   char *logMsg;
// //   for (i = 0; i < 2; ++i) {
// //     s = &shaders[i];
// //     s->source = readShaderSource(s->filename);
// //     if (shaders[i].source == NULL) {
// //       fprintf(stderr, "Failed to read %s\n", s->filename);
// //       exit(EXIT_FAILURE);
// //     }
// //     shader = glCreateShader(s->type);
// //     glShaderSource(shader, 1, (const GLchar**) &s->source, NULL);
// //     glCompileShader(shader );
// //     glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
// //     if (!compiled) {
// //       fprintf(stderr, "%s failed to compile\n", s->filename);
// //       glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
// //       logMsg = (char *) malloc(logSize);
// //       glGetShaderInfoLog(shader, logSize, NULL, logMsg);
// //       fprintf(stderr, "%s\n", logMsg);
// //       free(logMsg);
// //       exit( EXIT_FAILURE );
// //     }
// //     free(s->source);
// //     glAttachShader(program, shader);
// //   }
// //   /* link  and error check */
// //   glLinkProgram(program);
// //   glGetProgramiv( program, GL_LINK_STATUS, &linked );
// //   if ( !linked ) {
// //     fprintf(stderr, "Shader program failed to link\n");
// //     glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
// //     logMsg = (char *) malloc(logSize);
// //     glGetProgramInfoLog(program, logSize, NULL, logMsg);
// //     fprintf(stderr, "%s\n", logMsg);
// //     free(logMsg);
// //     exit( EXIT_FAILURE );
// //   }
// //   return program;
// // }
//
// //shading
// GLuint program, vao, vbo1, vbo2, vbo3, vbo4, pos, col, ind, MV;
//
// void norm(GLfloat vecs[]) {
//    GLfloat m = sqrt(vecs[0]*vecs[0] + vecs[1]*vecs[1] + vecs[2]*vecs[2]);
//    vecs[0] = vecs[0]/m;
//    vecs[1] = vecs[1]/m;
//    vecs[2] = vecs[2]/m;
//    //return vecs;
// }
//
// void matTranslatef(GLfloat matrix[], GLfloat x, GLfloat y, GLfloat z) {
// 	matrix[12]=matrix[0]*x+matrix[4]*y+matrix[8]*z+matrix[12];
// 	matrix[13]=matrix[1]*x+matrix[5]*y+matrix[9]*z+matrix[13];
// 	matrix[14]=matrix[2]*x+matrix[6]*y+matrix[10]*z+matrix[14];
// 	matrix[15]=matrix[3]*x+matrix[7]*y+matrix[11]*z+matrix[15];
// }
//
// void multiMatrix(GLfloat result[], GLfloat matrix1[], GLfloat matrix2[]) {
//     GLfloat tot;
//     GLfloat mat1[4][4];
//     GLfloat mat2[4][4];
//
//     int i = 0;
//     int j = 0;
//     int k = 0;
//     int count = 0;
//
//     for(i = 0; i < 4; i++) {
//       for(j = 0; j < 4; j++) {
//         mat1[i][j] = matrix1[count];
// 	      mat2[i][j] = matrix2[count];
//         count++;
//       }
//     }
//     i = j = 0;
//     for(i = 0; i < 4; i++) { //for each element in a column
//        for(j = 0; j < 4; j++) { //for each element in a row
//          tot = 0;
//          for(k = 0; k < 4; k++) {//add togther multiplied rows
//            tot +=  mat1[i][k] * mat2[k][j];
//          } //for
//          result[count] = tot;
//          count++;
//        }
//      }
// }
//
// void cross(GLfloat res[], GLfloat vec1[], GLfloat vec2[]) {
//   res[0] = vec1[1]*vec2[2]-vec1[2]*vec2[1];
//   res[1] = vec1[2]*vec2[0]-vec1[0]*vec2[2];
//   res[2] = vec1[0]*vec2[1]-vec1[1]*vec2[0];
//   //return res;
// }
//
// GLfloat dot(GLfloat vec1[], GLfloat vec2[]) {
//   GLfloat DOT = vec1[0]*vec2[0] + vec1[1]*vec2[1] + vec1[2]*vec2[2];
//   return DOT;
// }
//
// //void glLookAtf(GLfloat Matrix[16], GLfloat eyeVec[3], GLfloat centerVec[3], GLfloat upVec[3]) {
// void glLookAtf(GLfloat Matrix[], GLfloat eyeVec[], GLfloat centerVec[], GLfloat upVec[]) {
//   GLfloat forward[3], side[3], up[3];//size 3
//   GLfloat matrix2[16];
//   GLfloat resultMatrix[16]; //size 16
//    //Source: https://www.opengl.org/sdk/docs/man2/xhtml/gluLookAt.xml
//    //col major
//    forward[0] = centerVec[0] - eyeVec[0];
//    forward[1] = centerVec[1] - eyeVec[1];
//    forward[2] = centerVec[2] - eyeVec[2];
//    norm(forward);
//
//   //  //Side = forward x up
//    cross(side, forward, upVec);
//    norm(side);
//   //
//   //  //up = side x forward
//    cross(up, side, forward);
//    norm(up);
//
//    matrix2[0] = side[0];
//    matrix2[4] = side[1];
//    matrix2[8] = side[2];
//
//    matrix2[1] = up[0];
//    matrix2[5] = up[1];
//    matrix2[9] = up[2];
//
//    matrix2[2] = -forward[0];
//    matrix2[6] = -forward[1];
//    matrix2[10] = -forward[2];
//
//    matrix2[12] = matrix2[13] = matrix2[14] = 0.0;
//    matrix2[3] = matrix2[7] = matrix2[11] = 0.0;
//    matrix2[15] = 1.0;
//
//    //side[0] side[1] side[2] 0
//    //up[0] up[1] up[2] 0
//    //-forward[0] -forward[1] -forward[2] 0
//    //0 0 0 1
//
//    //multiply by modelview
//    multiMatrix(resultMatrix, Matrix, matrix2);
//    matTranslatef(resultMatrix, -eyeVec[0], -eyeVec[1], -eyeVec[2]);
//
//    multiMatrix(Matrix, Matrix, matrix2);
//    matTranslatef(Matrix, -eyeVec[0], -eyeVec[1], -eyeVec[2]);
//
//    //save in Matrix
//    memcpy(Matrix, resultMatrix, 16*sizeof(float));
// }
//
// void rotatey(GLfloat Matrix[16], GLfloat aX, GLfloat aY, GLfloat aZ) {
//   //Matrix = modelview matrix
//   //angles are in degrees
//   GLfloat resultMatrix[16];
//
//   GLfloat xRot[16] = {
//     1, 0, 0, 0,
//     0, cos(aX), sin(aX), 0,
//     0, -1*sin(aX), cos(aX), 0,
// 		0, 0, 0, 1
//   };
//
//   GLfloat yRot [16] = {
//     cos(aY), 0, -1*sin(aY), 0,
// 		0, 1, 0, 0,
// 		sin(aY), 0, cos(aY), 0,
// 		0, 0, 0, 1
//   };
//
//   GLfloat zRot [16] = {
//     cos(aZ), sin(aZ), 0, 0,
//     -1*sin(aZ), cos(aZ), 0,
// 		0, 0, 0, 1,
// 		0, 0, 0, 0, 1
//   };
//    //multiply by modelview
//    multiMatrix(Matrix, Matrix, xRot);
//    multiMatrix(Matrix, Matrix, yRot);
//    multiMatrix(Matrix, Matrix, zRot);
//    //resultMatrix = matTranslatef(resultMatrix, -eyeVec[0], -eyeVec[1], -eyeVec[2]);
//    //save in Matrix
//    memcpy(Matrix, resultMatrix, 16*sizeof(float));
// }
//
// void init() {
//   // glClearColor(0.0, 0.0, 0.0, 0.0);
//   // glColor3f(0.0, 0.0, 0.0);
//   // glClearDepth(1.0);
//   // glMatrixMode(GL_PROJECTION);
//   // glLoadIdentity();
//   // //gluPerpspective(where camera is places)
//   // gluPerspective(10, 1, 1, 20);
//   // glMatrixMode(GL_MODELVIEW);
//   // glEnable(GL_DEPTH_TEST);
//   // program = initshader( "hw4_vs.glsl", "hw4_fs.glsl" );
//   // glUseProgram(program);
//   // glLineWidth(3);
//   // glShadeModel(GL_FLAT);
//   // mat4 ModelViewMat = mat4(
// 	// 		   0, 0, 0, 0,
// 	// 		   0, 0, 0, 0,
// 	// 		   0, 0, 0, 0,
// 	// 		   0, 0, 0, 0
//   // );
//   // mat4 ProjectionMat = mat4(
// 	// 		    0, 0, 0, 0,
// 	// 		    0, 0, 0, 0,
// 	// 		    0, 0, 0, 0,
// 	// 		    0, 0, 0, 0
// 	// 	);
//   // glShadeModel(GL_SMOOTH);
//   // glEnable(GL_DEPTH_TEST);
//   // program = initshader("hw4_vs.glsl", "hw4_fs.glsl");
//   // glUseProgram(program);
//   // vbo = make_bo(GL_ARRAY_BUFFER, cubeVertices, sizeof(cubeVertices));
//   // idx_vbo = make_bo(GL_ELEMENT_ARRAY_BUFFER, cubeIndices, sizeof(cubeIndices));
//   // glGenVertexArrays(1, &vao);
//   // //
//   // glBindVertexArray(vao);
//   // glBindBuffer(GL_ARRAY_BUFFER, vbo);
//   // pos = glGetAttribLocation(program, "vPos");
//   // glEnableVertexAttribArray(pos);
//   // glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
//   // //
//   // modelview = glGetUniformLocation(program, "ModelView");
//   // project = glGetUniformLocation(program, "Project");
//   // glClearColor(1.0, 1.0, 1.0, 1.0);
// }
//
// GLfloat cube_vertices[][3] = {
//   {-X, -Y, Z},
//   {-X, Y,  Z},
//   {X,  Y,  Z},
//   {X, -Y,  Z},
//   {-X,-Y, -Z},
//   {-X, Y, -Z},
//   {X,  Y, -Z},
//   {X, -Y, -Z}
// };
//
// GLfloat tower_vertices[][3] = {
//   {-TX, -TY, TZ},
//   {-TX, TY,  TZ},
//   {TX,  TY,  TZ},
//   {TX, -TY,  TZ},
//   {-TX,-TY, -TZ},
//   {-TX, TY, -TZ},
//   {TX,  TY, -TZ},
//   {TX, -TY, -TZ}
// };
//
// GLfloat cube_colors[][3] ={
//   {0.0,0.0,0.0},
//   {1.0,0.0,0.0},
//   {1.0,1.0,0.0},
//   {0.0,1.0,0.0},
//   {0.0,0.0,1.0},
//   {1.0,0.0,1.0},
//   {1.0,1.0,1.0},
//   {0.0,1.0,1.0}
// };
//
// GLubyte cube_indices[24] = {
//   0,3,2,1,
//   2,3,7,6,
//   0,4,7,3,
//   1,2,6,5,
//   4,5,6,7,
//   0,1,5,4
// };
//
// GLubyte cube_wireframe_indices[48] = {
//   0, 1,
//   1, 2,
//   2, 3,
//   3, 0,
//   6, 5,
//   5, 1,
//   1, 2,
//   2, 6,
//   7, 4,
//   4, 5,
//   5, 6,
//   6, 7,
//   7, 3,
//   3, 0,
//   0, 4,
//   4, 7,
//   4, 0,
//   0, 1,
//   1, 5,
//   5, 4,
//   3, 7,
//   7, 6,
//   6, 2,
//   2, 3
// };
//
// GLubyte boid_wireframe_indices[10] = {
//   0, 1,
//   1, 2,
//   2, 0,
//   0, 3,
//   3, 1
// };
//
// void separation() {
//   //collision function
//   //checks for all boids so that they don't collide
//   //array of boids with x, y, z's for all
//   // GLfloat seper  = .08;
//   // for(int i = 1; i <= numBoid; i++){
//   //
//   // }
// }
//
// void alignment() {
//   //takes in:
//   //-Velocity-
//   //array boids
//   //speed
//   //speedGoal and acceleration rate that we want to reach goal at
//
//   //-steering-
//   //angle
//   //normailzed vectors
//   //goal point
//
//   //nearest neighbor?
//   //goal funtion
// }
//
// void cohesion() {
//   //movement together function
//   //center C
//   //center of flock C
//   //radius of flock
//   //move toawrds center gradually but not at expence of colliding
// }
//
// void GLLOOKAT() {
// }
//
// void GLUPER() {
// }
//
// void GLFRUST() {
// }
//
// void defaultView(GLfloat centerFlock[3]) {
//   //v
//   gluLookAt(-1.3, .8, -1.3,
//           //centerFlock[0]+cos(0)*(.8), centerFlock[1]+cos(0)*(.8), centerFlock[2]+cos(0)*(.8),
//           centerFlock[0], centerFlock[1], centerFlock[2],
//           0, 1, 0);
// }
//
// void sideView(GLfloat centerFlock[3]) {
//   //s
//   gluLookAt(-3, 0.4, 0.3,
//           centerFlock[0]+cos(0)*(.3), centerFlock[1]+cos(0)*(.3), centerFlock[2]+cos(0)*(.3),
//           //centerFlock[0], centerFlock[1], centerFlock[2],
//           0, 1, 0);
// }
//
// void trailView(GLfloat centerFlock[3]) {
//   //t
//   gluLookAt(//-1.3, .8, -1.3,
//           centerFlock[0]+cos(0)*(.8), centerFlock[1]+cos(0)*(.8), centerFlock[2]+cos(0)*(.8),
//           centerFlock[0], centerFlock[1], centerFlock[2],
//           0, 1, 0);
// }
//
// GLfloat square(GLfloat s) {
//     float sqr;
//     sqr = s*s;
//     return sqr;
// }
//
// GLfloat dist(GLfloat x, GLfloat y, GLfloat z, GLfloat x2, GLfloat y2, GLfloat z2){
//   GLfloat distance;
//   distance = sqrt(square(x2-x)+square(y2-y)+square(z2-z));
//   return distance;
// }
//
// void draw_cube() {
//   glEnableClientState(GL_COLOR_ARRAY);
//   glEnableClientState(GL_VERTEX_ARRAY);
//   glVertexPointer(3, GL_FLOAT, 0, cube_vertices);
//   glColorPointer(3, GL_FLOAT, 0, cube_colors);
//   glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cube_indices);
//   glDisableClientState(GL_COLOR_ARRAY);
//   glDisableClientState(GL_VERTEX_ARRAY);
// }
//
// void draw_tower() {
//   glEnableClientState(GL_COLOR_ARRAY);
//   glEnableClientState(GL_VERTEX_ARRAY);
//   glVertexPointer(3, GL_FLOAT, 0, tower_vertices);
//   glColorPointer(3, GL_FLOAT, 0, cube_colors);
//   glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cube_indices);
//   glDisableClientState(GL_COLOR_ARRAY);
//   glDisableClientState(GL_VERTEX_ARRAY);
// }
//
// void draw_wireframe_cube() {
//   glEnableClientState(GL_VERTEX_ARRAY);
//   glVertexPointer(3, GL_FLOAT, 0, cube_vertices);
//   glColor3f(1,1,1);
//   glDrawElements(GL_LINES, 48, GL_UNSIGNED_BYTE, cube_wireframe_indices);
//   glDisableClientState(GL_VERTEX_ARRAY);
// }
//
// GLuint make_bo(GLenum type, const void *buf, GLsizei buf_size) {
//     GLuint bufnum;
//     glGenBuffers(1, &bufnum);
//     glBindBuffer(type, bufnum);
//     glBufferData(type, buf_size, buf, GL_STATIC_DRAW);
//     return bufnum;
// }
//
// void draw_boid(GLfloat boid_vertices[4][3], GLfloat pos[3]) {
//   boid_vertices[0][0] = pos[0];
//   boid_vertices[0][1] = pos[1]+.05;
//   boid_vertices[0][2] = pos[2];
//   boid_vertices[1][0] = pos[0];
//   boid_vertices[1][1] = pos[1]+.05;
//   boid_vertices[1][2] = pos[2]-.025;
//   boid_vertices[2][0] = pos[0]-.025;
//   boid_vertices[2][1] = pos[1]+.075;
//   boid_vertices[2][2] = pos[2]-.0125;
//   boid_vertices[3][0] = pos[0]+.025;
//   boid_vertices[3][1] = pos[1]+.075;
//   boid_vertices[3][2] = pos[2]-.0125;
//   glEnableClientState(GL_VERTEX_ARRAY);
//   glVertexPointer(3, GL_FLOAT, 0, boid_vertices);
//   glColor3f(1,1,1);
//   glDrawElements(GL_LINES, 10, GL_UNSIGNED_BYTE, boid_wireframe_indices);
//   glDisableClientState(GL_VERTEX_ARRAY);
// }
// void secondInit() {
//   // mat4 ModelViewMat = mat4(
// 	// 		   0, 0, 0, 0,
// 	// 		   0, 0, 0, 0,
// 	// 		   0, 0, 0, 0,
// 	// 		   0, 0, 0, 0
//   // );
//   // mat4 ProjectionMat = mat4(
// 	// 		    0, 0, 0, 0,
// 	// 		    0, 0, 0, 0,
// 	// 		    0, 0, 0, 0,
// 	// 		    0, 0, 0, 0
// 	// 	);
//   // glShadeModel(GL_SMOOTH);
//   program = initshader("hw4_fs.glsl", "hw4_vs.glsl");
//
//   glGenVertexArrays(1, &vao);
//   glBindVertexArray(vao);
//   //Initialize the vertex position attribute from the vertex shader
//   pos = glGetAttribLocation(program, "vPos");
//   col = glGetAttribLocation(program, "vCol");
//   MV = glGetUniformLocation(program, "finalview");
//
//   //create, init buffer obj
//   vbo1 = make_bo(GL_ARRAY_BUFFER, boid_vertices, sizeof(boid_vertices));
//   vbo2 = make_bo(GL_ARRAY_BUFFER, cube_vertices, sizeof(cube_vertices));
//   vbo3 = make_bo(GL_ARRAY_BUFFER, tower_vertices, sizeof(tower_vertices));
//   vbo4 = make_bo(GL_ELEMENT_ARRAY_BUFFER, cube_indices, sizeof(cube_indices));
//   //
//   glUseProgram(program);
//
//   glEnableVertexAttribArray(pos);
//   glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//   glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*) 0);
//   //
//   glEnableVertexAttribArray(col);
//   //
//   glVertexAttribPointer(col, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//   glVertexAttribPointer(col, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
// }
//
// void addBoid() {
//   float randX, randY, randZ, deciX, deciY, deciZ;
//   printf("bird added!");
//   randX = rand()%3;
//   randY = rand()%3;
//   randZ = rand()%3;
//   deciX = ((rand()%999999));
//   deciY = ((rand()%999999));
//   deciZ = ((rand()%999999));
//   deciX /= 1000000;
//   deciY /= 1000000;
//   deciZ /= 1000000;
//   randX += deciX;
//   randY += deciY;
//   randZ += deciZ;
//   if(numBoid != 100) {
//     push(&headx, &randX, fsize);
//     push(&heady, &randY, fsize);
//     push(&headz, &randZ, fsize);
//   }
//   else {
//     printf("To many birds! ! !");
//   }
//   numBoid = numBoid + 1;
// }
//
// void minusBoid() {
//   printf("bird taken away!");
//   int index = rand()%numBoid+1;
//   printf("% d index \n", index);
//   deleteNode(&headx, index, numBoid);
//   deleteNode(&heady, index, numBoid);
//   deleteNode(&headz, index, numBoid);
//   numBoid--;
// }
//
// void reshape(GLFWwindow *w, int width, int height){
//   printf("Got a Reshape Event");
//   printf(":\t width = %d height = %d\n", width, height);
//   glMatrixMode(GL_PROJECTION);
//   glLoadIdentity();
//   glFrustum(-1, 1, -1, 1, 0.4, 15);
//   glMatrixMode(GL_MODELVIEW);
//   // Set the new viewport size
//   glViewport(0, 0, width, height);
// }
//
// void framebuffer_resize(GLFWwindow *wind, int w, int h) {
//     glViewport(0, 0, w, h);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     //gluOrtho2D(0.0, (double)w/RESIZE_FACTOR, (double)h/RESIZE_FACTOR, 0.0);
//     glMatrixMode(GL_MODELVIEW);
//   }
//
// void step(GLfloat cenFlock[3], GLfloat goal[3]){
//   printf("\n___Step___ \n");
//   printf("Goal");
//   for(int i = 0; i < 3; i++) {
//     printf("%f ", goal[i]);
//    }
//   printf("Center Flock");
//   for(int i = 0; i < 3; i++) {
//     printf("%f ", cenFlock[i]);
//    }
// }
//
// void keyboard(GLFWwindow *w, int key, int scancode, int action, int mods) {
//   //quit
//   switch(key) {
//    case GLFW_KEY_ESCAPE :
//    case 'q' :
//    case 'Q' :
//     printf("end\n");
//     glfwSetWindowShouldClose(w, GL_TRUE);
//     break;
//   case 'v' :
//   case 'V':
//   case 'S' :
//     view = SIDE;
//     break;
//   default:
//     break;
//   }
//    //steering and speed
//    //general - step, pause, views, and add and minus boids
//    switch(action) {
//      case GLFW_RELEASE:
//      switch(key) {
//        case GLFW_KEY_SPACE:
//         stepBool = true;
//         break;
//       case GLFW_KEY_UP:
//         upArw = true;
//         //printf("uparw");
//         break;
//       case GLFW_KEY_DOWN:
//         downArw = true;
//         break;
//       case GLFW_KEY_LEFT:
//         lArw = true;
//         break;
//       case GLFW_KEY_RIGHT:
//         rArw = true;
//         break;
//       //speed up
//       case 'u':
//         faster = true;
//         break;
//       //slow down
//       case 'd':
//         slower = true;
//         break;
//       case 'p':
//         pause = !pause;
//         break;
//       case GLFW_KEY_KP_ADD:
//         //addB = true;
//         addBoid();
//         break;
//       case GLFW_KEY_KP_SUBTRACT:
//         //minusB = true;
//         minusBoid();
//         break;
//       default:
//         break;
//       }
//       default:
//         break;
//     }
// }
//
// int main(int argc, char **argv) {
//     GLFWwindow* window;
//     GLfloat temp[3];
//     GLfloat goal[3] = {.3, .2, .3};
//     GLfloat cenFlock[3] = {goal[0]-rad, goal[1], goal[2]};
//     GLfloat boid_vertices[4][3];
//     int iter = 0;
//     GLfloat *Matrix;//len=16
//     GLfloat e[3] = {1, .3, 2};
//     GLfloat cv[3] = {0, 0, 0};
//     GLfloat uv[3] = {0, 1, 0};
//     srand(time(NULL));
//     // Initialize the library
//   if (!glfwInit())
//     exit(EXIT_FAILURE);
//
//     glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
//     glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//     glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//   // Create a window and its OpenGL context
//   window = glfwCreateWindow(850, 800, "Hello GL!", NULL, NULL);
//   glewInit();
//   if (!window){
//     glfwTerminate();
//     exit(EXIT_FAILURE);
//   }
//
//   //events
//   glfwSetWindowPos(window, 100, 100);
//   glfwMakeContextCurrent(window);
//   glfwSetWindowSizeCallback(window, reshape);
//   glfwSetKeyCallback(window, keyboard);
//   glfwMakeContextCurrent(window);
//   //glfwSetFramebufferSizeCallback(window, framebuffer_resize);
//
//   init();
//   //secondInit();
//   // Loop until the user closes the window
//   while (!glfwWindowShouldClose(window)) {
//     if(pause == false || stepBool == true) {
//       goal[2] += .0005;
//       cenFlock[2] += .0005;
//        //*******setup**********//
//       //LIST
//       //push(&headd, &aa, dsize);
//       //printList(headi, printI);
//       //int e = valD(headi, 0, 4);
//       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//       glMatrixMode(GL_MODELVIEW);
//       glClearDepth(1.0);
//       glLoadIdentity();
//       //glGetFloatv(GL_MODELVIEW_MATRIX, Matrix);
//       //glLookAtf(Matrix, e, cv, uv);
//       glLoadMatrixf(Matrix);
//       if(view == DEFAULT) {
//         defaultView(cenFlock);
//       }
//       else if (view == SIDE) {
//         sideView(cenFlock);
//       }
//       else {
//         trailView(cenFlock);
//       }
//       bool dview = true, sideVw = false, tView = false;
//
//       //********update*********//
//       //spead, number of birds, weight adjustment
//
//       //*********draw*********//
//       draw_cube();
//       draw_tower();
//       glColor3f(1.0, 1.0, 0.0);
//       for(int i = 0; i < 3; i++) {
//         goal[i] += velocity;
//         cenFlock[i] += velocity;
//       }
//       draw_boid(boid_vertices, cenFlock);
//       draw_boid(boid_vertices, goal);
//       for(int i = 1; i <= numBoid; i++){
//         temp[0] = valF(headx, i, numBoid) + iter*velocity;
//         temp[1] = valF(heady, i, numBoid) + iter*velocity;
//         temp[2] = valF(headz, i, numBoid) + iter*velocity;
//         draw_boid(boid_vertices, temp);
//       }
//       iter++;
//       //*****end process*****//
//       glfwSwapBuffers(window);
//       glfwPollEvents();
//       if(stepBool == true) {
//         step(cenFlock, goal);
//       }
//       stepBool = false;
//     } //if statement
//     else {
//      printf("Pause!");
//     }
//   }//while
//
//   glfwTerminate();
//   exit(EXIT_SUCCESS);
// }
