//hw4
//start with simple
//add header file after
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glew.h>
#include <memory.h>
#include "list.c"
#include "initshader.h"
#include "common.h"
#include "vecs.hpp"
#include "mats.hpp"
#define X 1.3
#define Y 0
#define Z 1.3
#define TX .03
#define TY .2
#define TZ .03
enum {DEFAULT, TRAILING, SIDE}; // 0, 1, 2
int view = 0;

//********Globals*******//
struct node *headx = NULL;
struct node *heady = NULL;
struct node *headz = NULL;
unsigned dsize = sizeof(double);
unsigned bsize = sizeof(bool);
unsigned isize = sizeof(int);
unsigned fsize = sizeof(float);
int numBoid = 0;
GLfloat boid_vertices[4][3]; //need to declare??

GLfloat max[3] = {30, 30, 30};
GLfloat min[3] = {.1, .1, .1};
GLfloat direction[3];
GLfloat velocity = .001;
GLfloat steerTo[3] = {0, 0, 0};
GLfloat cToGm, midpt, rad = .1;
bool lArw = false, rArw = false, upArw = false, downArw = false, addB = false, minusB = false;
bool slower = false, faster = false, pause = false, stepBool = false;
//u = faster d = slower

//shading
GLuint program, vao, vbo1, vbo2, vbo3, vbo4, pos, col, index;

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

}

GLfloat cube_vertices[][3] = {
  {-X, -Y, Z},
  {-X, Y,  Z},
  {X,  Y,  Z},
  {X, -Y,  Z},
  {-X,-Y, -Z},
  {-X, Y, -Z},
  {X,  Y, -Z},
  {X, -Y, -Z}
};

GLfloat tower_vertices[][3] = {
  {-TX, -TY, TZ},
  {-TX, TY,  TZ},
  {TX,  TY,  TZ},
  {TX, -TY,  TZ},
  {-TX,-TY, -TZ},
  {-TX, TY, -TZ},
  {TX,  TY, -TZ},
  {TX, -TY, -TZ}
};

GLfloat cube_colors[][3] ={
  {0.0,0.0,0.0},
  {1.0,0.0,0.0},
  {1.0,1.0,0.0},
  {0.0,1.0,0.0},
  {0.0,0.0,1.0},
  {1.0,0.0,1.0},
  {1.0,1.0,1.0},
  {0.0,1.0,1.0}
};

GLubyte cube_indices[24] = {
  0,3,2,1,
  2,3,7,6,
  0,4,7,3,
  1,2,6,5,
  4,5,6,7,
  0,1,5,4
};

GLubyte cube_wireframe_indices[48] = {
  0, 1,
  1, 2,
  2, 3,
  3, 0,
  6, 5,
  5, 1,
  1, 2,
  2, 6,
  7, 4,
  4, 5,
  5, 6,
  6, 7,
  7, 3,
  3, 0,
  0, 4,
  4, 7,
  4, 0,
  0, 1,
  1, 5,
  5, 4,
  3, 7,
  7, 6,
  6, 2,
  2, 3
};

GLubyte boid_wireframe_indices[10] = {
  0, 1,
  1, 2,
  2, 0,
  0, 3,
  3, 1
};

void separation() {
  //collision function
  //checks for all boids so that they don't collide
  //array of boids with x, y, z's for all
  // GLfloat seper  = .08;
  for(int i = 1; i <= numBoid; i++){

  }
}

void alignment() {
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
}

void GLLOOKAT() {
}

void GLUPER() {
}

void GLFRUST() {
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

GLfloat square(GLfloat s) {
    float sqr;
    sqr = s*s;
    return sqr;
}

GLfloat dist(GLfloat x, GLfloat y, GLfloat z, GLfloat x2, GLfloat y2, GLfloat z2){
  GLfloat distance;
  distance = sqrt(square(x2-x)+square(y2-y)+square(z2-z));
  return distance;
}

void draw_cube() {
  glEnableClientState(GL_COLOR_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, cube_vertices);
  glColorPointer(3, GL_FLOAT, 0, cube_colors);
  glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cube_indices);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void draw_tower() {
  glEnableClientState(GL_COLOR_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, tower_vertices);
  glColorPointer(3, GL_FLOAT, 0, cube_colors);
  glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cube_indices);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void draw_wireframe_cube() {
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, cube_vertices);
  glColor3f(1,1,1);
  glDrawElements(GL_LINES, 48, GL_UNSIGNED_BYTE, cube_wireframe_indices);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void draw_boid(GLfloat boid_vertices[4][3], GLfloat pos[3]) {
  boid_vertices[0][0] = pos[0];
  boid_vertices[0][1] = pos[1]+.05;
  boid_vertices[0][2] = pos[2];
  boid_vertices[1][0] = pos[0];
  boid_vertices[1][1] = pos[1]+.05;
  boid_vertices[1][2] = pos[2]-.025;
  boid_vertices[2][0] = pos[0]-.025;
  boid_vertices[2][1] = pos[1]+.075;
  boid_vertices[2][2] = pos[2]-.0125;
  boid_vertices[3][0] = pos[0]+.025;
  boid_vertices[3][1] = pos[1]+.075;
  boid_vertices[3][2] = pos[2]-.0125;
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, boid_vertices);
  glColor3f(1,1,1);
  glDrawElements(GL_LINES, 10, GL_UNSIGNED_BYTE, boid_wireframe_indices);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void addBoid() {
  float randX, randY, randZ, deciX, deciY, deciZ;
  printf("bird added!");
  randX = rand()%3;
  randY = rand()%3;
  randZ = rand()%3;
  deciX = ((rand()%999999));
  deciY = ((rand()%999999));
  deciZ = ((rand()%999999));
  deciX /= 1000000;
  deciY /= 1000000;
  deciZ /= 1000000;
  randX += deciX;
  randY += deciY;
  randZ += deciZ;
  if(numBoid != 100) {
    push(&headx, &randX, fsize);
    push(&heady, &randY, fsize);
    push(&headz, &randZ, fsize);
  } else {
    printf("To many birds! ! !");
  }
  numBoid = numBoid + 1;
}

void minusBoid() {
   printf("bird taken away!");
  int index = rand()%numBoid+1;
  printf("% d index \n", index);
  deleteNode(&headx, index, numBoid);
  deleteNode(&heady, index, numBoid);
  deleteNode(&headz, index, numBoid);
  numBoid--;
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

void step(GLfloat cenFlock[3], GLfloat goal[3]){
  printf("\n___Step___ \n");
  printf("Goal");
  for(int i = 0; i < 3; i++) {
    printf("%f ", goal[i]);
   }
  printf("Center Flock");
  for(int i = 0; i < 3; i++) {
    printf("%f ", cenFlock[i]);
   }
}

void secondInit() {
  program = initshader("hw4_vs.glsl", "hw4_fs.glsl");
  //init v pos attrib from vertex shader
  pos = glGetAttribLocation(program, "vPos");
  col = glGetAttribLocation(program, "vCol");
  //create, init buffer obj
  vbo1 = make_bo(GL_ARRAY_BUFFER, boid_vertices, sizeof(boid_vertices));
  vbo2 = make_bo(GL_ARRAY_BUFFER, cube_vertices, sizeof(cube_vertices));
  vbo3 = make_bo(GL_ARRAY_BUFFER, tower_vertices, sizeof(tower_vertices));
  vbo4 = make_bo(GL_ELEMENT_ARRAY_BUFFER, cube_indices, sizeof(cube_indices));

  glUseProgram(program);

  glEnableVertexAttribArray(pos);
  glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  glEnableVertexAttribArray(col);
  glVertexAttribPointer(col, 4, GL_FLOAT, GL_FALSE, 0, NULL);

  //glVertexAttribPointer(col, 3, GL_FLOAT, GL_FALSEVERTEXATTRIBSIZE * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  glVertexAttribPointer(col, 3, GL_FLOAT, GL_FALSE, 0, NULL);
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
     case GLFW_RELEASE:
     switch(key) {
       case GLFW_KEY_SPACE:
        stepBool = true;
        break;
      case GLFW_KEY_UP:
        upArw = true;
        //printf("uparw");
        break;
      case GLFW_KEY_DOWN:
        downArw = true;
        break;
      case GLFW_KEY_LEFT:
        lArw = true;
        break;
      case GLFW_KEY_RIGHT:
        rArw = true;
        break;
      //speed up
      case 'u':
        faster = true;
        break;
      //slow down
      case 'd':
        slower = true;
        break;
      case 'p':
        pause = !pause;
 //if(pause == false){
 //  pause = true;
 //} else {
 //  pause = false;
 //}
        break;
      case GLFW_KEY_KP_ADD:
        //addB = true;
        addBoid();
        break;
      case GLFW_KEY_KP_SUBTRACT:
        //minusB = true;
        minusBoid();
        break;
      default:
        break;
      }
      default:
        break;
    }
}

int main(int argc, char **argv) {
    GLFWwindow* window;
    GLfloat temp[3];
    GLfloat goal[3] = {.3, .2, .3};
    GLfloat cenFlock[3] = {goal[0]-rad, goal[1], goal[2]};
    GLfloat boid_vertices[4][3];
    int iter = 0;
    srand(time(NULL));

    // Initialize the library
  if (!glfwInit())
    exit(EXIT_FAILURE);

  // Create a window and its OpenGL context
  window = glfwCreateWindow(850, 800, "Hello GL!", NULL, NULL);
  glewInit();
  if (!window){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

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
    if(pause == false || stepBool == true) {
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
defaultView(cenFlock);
      } else if (view == SIDE) {
sideView(cenFlock);
      } else {
trailView(cenFlock);
      }
      //bool dview = true, sideVw = false, tView = false;

      //********update*********//
      //spead, number of birds, weight adjustment

      //*********draw*********//
      draw_cube();
      draw_tower();
      glColor3f(1.0, 1.0, 0.0);
      for(int i = 0; i < 3; i++) {
goal[i] += velocity;
        cenFlock[i] += velocity;
      }
      draw_boid(boid_vertices, cenFlock);
      draw_boid(boid_vertices, goal);
      for(int i = 1; i <= numBoid; i++){
        temp[0] = valF(headx, i, numBoid) + iter*velocity;
temp[1] = valF(heady, i, numBoid) + iter*velocity;
temp[2] = valF(headz, i, numBoid) + iter*velocity;
draw_boid(boid_vertices, temp);
      }
      iter++;
      //*****end process*****//
      glfwSwapBuffers(window);
      glfwPollEvents();
      if(stepBool == true) {
        step(cenFlock, goal);
      }
      stepBool = false;
    } //if statement
    else {
     printf("Pause!");
    }
  }//while

  glfwTerminate();
  exit(EXIT_SUCCESS);
}
