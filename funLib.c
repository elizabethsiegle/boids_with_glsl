
//start with simple
//add header file after
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include "list.c"
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

GLfloat direction[3];
GLfloat velocity[3] = {.01, .01, .01};
GLfloat toVelocity[3] = {0, 0, 0};
GLfloat cToGm, midpt, rad = .1, birdRad = .05;
bool lArw = false, rArw = false, upArw = false, downArw = false, addB = false, minusB = false;
bool slower = false, faster = false, pause = false, stepBool = false;
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
  gluLookAt(-3, 0.7, 0.3,
          centerFlock[0]+cos(0)*(.3), centerFlock[1]+cos(0)*(.3), centerFlock[2]+cos(0)*(.3),
          //centerFlock[0], centerFlock[1], centerFlock[2],
          0, 1, 0);
}

void trailView(GLfloat centerFlock[3]) {
  //t
  gluLookAt(//-1.3, .8, -1.3,
          0.3, 0.8, -5,
          //centerFlock[0]+cos(0)*(.8), centerFlock[1]+cos(0)*(.8), centerFlock[2]+cos(0)*(.8),
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
  randX = rand()%4;
  randY = rand()%4;
  randZ = rand()%4;
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

void minusBoid(int numBoid) {
  int index = rand()%numBoid+1;
  printf("% d", index);
  //delteBoid
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

void step(){
  printf("___Step___ \n");
  //printf("%f", goalVector);
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
  switch(action) {
    case GLFW_RELEASE:
      switch(key) {
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
          break;
        default:
          break;
      }
      default:
        break;
    }
    //general - step, pause, views, and add and minus boids
    switch(action) {
      case GLFW_RELEASE:
        switch(key) {
          case GLFW_KEY_SPACE:
            if(pause == true){
              stepBool = true;
              step();
            }
            else {
              printf("ERROR: Press 'p' for pause before trying to step the program!");
            }
            break;
          case GLFW_KEY_KP_ADD:
            addB = true;
            break;
          case GLFW_KEY_KP_SUBTRACT:
            minusB = true;
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
    srand(time(NULL));

    // Initialize the library
  if (!glfwInit())
    exit(EXIT_FAILURE);

  // Create a window and its OpenGL context
  window = glfwCreateWindow(850, 800, "Hello GL!", NULL, NULL);
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
  //glfwSetMouseButtonCallback(window, mouse);

  addBoid();
  addBoid();
  addBoid();
  addBoid();
  //float xbefore = valF(headx, 1, numBoid);
  //printf("%f before\n ", xbefore);
  printList(headx, printFloat);
  deleteNode(&headx, 4, numBoid);
  numBoid--;
  printf("%d numboud \n", numBoid);
  float Xafter = valF(headx, 4, numBoid);
  printf("%f after XX\n ", Xafter);
  //minusBoid();
  printList(headx, printFloat);

  init();
  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window)) {
    if(pause == false || stepBool == true) {
      goal[2] += .0005;
      cenFlock[2] += .0005;
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
      draw_boid(boid_vertices, cenFlock);
      draw_boid(boid_vertices, goal);

      for(int i = 1; i <= numBoid; i++){
        temp[0] = valF(headx, i, numBoid);
	temp[1] = valF(heady, i, numBoid);
	temp[2] = valF(headz, i, numBoid);
	draw_boid(boid_vertices, temp);
      }

      //for() {
       //yD = valD(headCi, (incC*4)+4, numCirc*4);
      //draw_boid(boid_vertices, goal);
      //}

      //*****end process*****//
      glfwSwapBuffers(window);
      glfwPollEvents();
      stepBool = false;
    }
  }

  glfwTerminate();
  exit(EXIT_SUCCESS);
}


// #include "boid.h"
// #include "list.h"
// #include "events.h" //WIDTH
// //#include <gsl/gsl_vector.h> //! sure why doesn't include in header
//
// GLfloat vertices[][3];
// GLfloat colors[][3];
// GLubyte indices[];
// unsigned floatSize = sizeof(float);
// unsigned boidSize = sizeof(Boid);
// GLfloat worldVec[VECTOR_LENGTH];
//
// GLfloat angle;
// GLint count;
//
// Node *h = NULL;
// Node *t = NULL;
//
// GLfloat square(GLfloat lol) {
//   float retSq;
//   retSq = lol * lol;
//   return retSq;
// }
//
// void goalUpdate(Goal *g) {
//   g->theta += 0.024;
//   gsl_vector_set(g->move, 0, g->width * sin(g->theta));
//   gsl_vector_set(g->move, 1, g->width * cos(g->theta));
// }
//
//
// Boid* boidInit(int numBoids) {
//   GLfloat xPos, yPos, zPos;
//   GLfloat xVel, yVel, zVel = 0;
//   Boid *b = (Boid*) malloc(sizeof(b));
//
//   while(numBoids > 0) {
//     b->num = numBoids;
//     numBoids--;
//   } //while
//   //loc of boids
//   b->xyPos = gsl_vector_alloc(3);
//   xPos = rand() % 24;
//   yPos = rand() % 24;
//   zPos = rand() % 24;
//   gsl_vector_set(b->xyPos, 0, xPos);
//   gsl_vector_set(b->xyPos, 1, yPos);
//   gsl_vector_set(b->xyPos, 2, zPos);
//
//   //speed of boids
//   b->vel = gsl_vector_alloc(3);
//   xVel = rand() % 24;
//   yVel = rand() % 24;
//   zVel = rand() % 24;
//   gsl_vector_set(b->vel, 0, xVel);
//   gsl_vector_set(b->vel, 1, yVel);
//   gsl_vector_set(b->vel, 2, zVel);
//
//   //angle
//   b->angle = rand() % 360;
//   return b;
// }
//
// void printvector(gsl_vector *vect) {
//   printf("xpos %f, ypos %f, zpos %f", gsl_vector_get(vect, 0), gsl_vector_get(vect, 1), gsl_vector_get(vect, 2));
// } //printvector
//
// void scaleWorld(gsl_vector *vec){
//   GLdouble *vecPtr = gsl_vector_ptr(vec, 0);
//   *vecPtr = *vecPtr * worldVec[0];
//   *(vecPtr + 1) = *(vecPtr + 1) * worldVec[1];
//   *(vecPtr + 2) = *(vecPtr + 2) * worldVec[2];
// }
//
// void initMultipleBoids() {
//   int i;
//   //h = makeList();
//   t = h->next;
//   for(i = 0; i < 7; i++) {
//     Boid *b = boidInit(i); //init 6 boids
//     //Node *newnode = makeNode(b, i);
//     push(&h, &b, boidSize); //add to list, //7 6?
//   } //for
// }
// //void printBoids(Node *h) {
//   //Node *curr = h->next;
//   //	while(curr->type == VAL) {
//   //printf(curr->data->num, gsl_vector_get(curr->data->xyPos, 0), gsl_vector_get(curr->data->xyPos, 1), gsl_vector_get(curr->data->xyPos, 2));
//   //curr = curr->next;
//   //} //while
//   //} //printBoids
//
// GLfloat distanceBtwnBoidsFunc(Boid *b1, Boid *b2) {
//   gsl_vector *second = gsl_vector_alloc(3);
//   gsl_vector_memcpy(second, b1->xyPos);
//   gsl_vector_sub(second, b2->xyPos);
//   gsl_vector_mul(second, second);
//   GLfloat distance = gsl_vector_get(second, 0) + gsl_vector_get(second, 1) + gsl_vector_get(second, 2);
//   gsl_vector_free(second);
//   return distance;
// } //distanceBtwnBoids
//
// GLfloat vertices[][3] = {
//   {4, 4, 6},
//   {4, 20, 6},
//   {-20, -10, 6},
//   {20, 0, 6}
// }; //vertices
//
// GLfloat colors[][3] = {
//   {0, 0, 0},
//   {1, 0, 0},
//   {1, 1, 0},
//   {1, 1, 1}
// };
//
// GLubyte indices[] = {
//   3, 2, 1,
//   0, 1, 2
// };
//
// gsl_vector* inBetween(Boid** b, int s, Goal g) {
//   gsl_vector* centerOfBoids = gsl_vector_alloc(VECTOR_LENGTH);
//   gsl_vector_set_zero(centerOfBoids);
//   int i;
//   for(i = 0; i < s; i++) {
//     gsl_vector_add(centerOfBoids, (const gsl_vector*)b[i]->xyPos);
//   }
//   gsl_vector_scale(centerOfBoids, 1.0/s);
//   gsl_vector_free(centerOfBoids);
//   return centerOfBoids;
// }
//
// void drawBoids() {
//   glEnableClientState(GL_COLOR_ARRAY);
//   glEnableClientState(GL_VERTEX_ARRAY);
//   glVertexPointer(3, GL_FLOAT, 0, vertices);
//   glColorPointer(3, GL_FLOAT, 0, colors);
//   Node* curr;
//   curr = h->next;
//   while(curr->num != 0) { //!at end
//     //drawBoid(curr->num);
//     curr = curr->next;
//   }
//   glDisableClientState(GL_COLOR_ARRAY);
//   glDisableClientState(GL_VERTEX_ARRAY);
// }
//
// void goalDraw(Goal g) {
//   glEnableClientState(GL_COLOR_ARRAY);
//   glEnableClientState(GL_VERTEX_ARRAY);
//   glColorPointer(3, GL_FLOAT, 0, gColors);
//   glVertexPointer(3, GL_FLOAT, 0, gVertices);
//   glPushMatrix();
//   glScalef(worldVec[0], worldVec[1], worldVec[2]);
//   glTranslatef(
// 	       gsl_vector_get(g.move, 0),
// 	       gsl_vector_get(g.move, 1),
// 	       gsl_vector_get(g.move, 2)
// 	       );
//   glDrawArrays(GL_POINTS, 0, 1);
//   glPopMatrix();
//   glDisableClientState(GL_VERTEX_ARRAY);
//   glDisableClientState(GL_COLOR_ARRAY);
// }
//
// void initView() {
//   //behind view
//   behindView.up = gsl_vector_calloc(3);
//   gsl_vector_set(behindView.up, 1, 2);
//   //side view
//   sideView.up = gsl_vector_calloc(3);
//   gsl_vector_set(sideView.up, 1, 2); //2, 1??
//   //middle view
//   centerView.pos = gsl_vector_calloc(3);
//   gsl_vector_set(centerView.pos, 2, 1000); //1300??
//   scaleWorld(centerView.pos);
//   centerView.up = gsl_vector_calloc(3);
//   gsl_vector_set(centerView.up, 2, 1);
//   centerView.v = inBetween(boyd, 2, goalLol);
//   scaleWorld(centerView.v);
// }
//
// Goal goalInit() {
//   Goal g;
//   g.theta = 0;
//   g.width = 500;
//   g.move = gsl_vector_alloc(3);
//   gsl_vector_set(g.move, 0, g.width * sin(g.theta));
//   gsl_vector_set(g.move, 1, g.width * cos(g.theta));
//   gsl_vector_set(g.move, 2, 500);
//   return g;
// }


// //hw4
// //start with simple
// //add header file after
// #include <stdlib.h>
// #include <stdio.h>
// #include <math.h>
// #include <time.h>
// #include <stdbool.h>
// #include <GLFW/glfw3.h>
// #include <GL/glu.h>
// // #include "list.c"
// #include "initshader.h"
// #include "vecs.h"
// #include "mats.h"
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
// struct node *headx = NULL;
// struct node *heady = NULL;
// struct node *headz = NULL;
// unsigned dsize = sizeof(double);
// unsigned bsize = sizeof(bool);
// unsigned isize = sizeof(int);
// unsigned fsize = sizeof(float);
// int numBoid = 0;
//
// GLfloat direction[3];
// GLfloat velocity[3] = {.01, .01, .01};
// GLfloat toVelocity[3] = {0, 0, 0};
// GLfloat cToGm, midpt, rad = .1, birdRad = .05;
// bool lArw = false, rArw = false, upArw = false, downArw = false, addB = false, minusB = false;
// bool slower = false, faster = false, pause = false, stepBool = false;
// //u = faster d = slower
//
// void init() {
//   glClearColor(0.0, 0.0, 0.0, 0.0);
//   glColor3f(0.0, 0.0, 0.0);
//   glClearDepth(1.0);
//   glMatrixMode(GL_PROJECTION);
//   glLoadIdentity();
//   //gluPerpspective(where camera is places)
//   gluPerspective(10, 1, 1, 20);
//   glMatrixMode(GL_MODELVIEW);
//   glEnable(GL_DEPTH_TEST);
//   glLineWidth(3);
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
//   gluLookAt(-3, 0.7, 0.3,
//           centerFlock[0]+cos(0)*(.3), centerFlock[1]+cos(0)*(.3), centerFlock[2]+cos(0)*(.3),
//           //centerFlock[0], centerFlock[1], centerFlock[2],
//           0, 1, 0);
// }
//
// void trailView(GLfloat centerFlock[3]) {
//   //t
//   gluLookAt(//-1.3, .8, -1.3,
//           0.3, 0.8, -5,
//           //centerFlock[0]+cos(0)*(.8), centerFlock[1]+cos(0)*(.8), centerFlock[2]+cos(0)*(.8),
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
//
// void addBoid() {
//   float randX, randY, randZ, deciX, deciY, deciZ;
//   randX = rand()%4;
//   randY = rand()%4;
//   randZ = rand()%4;
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
//   } else {
//     printf("To many birds! ! !");
//   }
//   numBoid = numBoid + 1;
// }
//
// void minusBoid(int numBoid) {
//   int index = rand()%numBoid+1;
//   printf("% d", index);
//   //delteBoid
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
// /*void framebuffer_resize(GLFWwindow *wind, int w, int h) {
//     glViewport(0, 0, w, h);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluOrtho2D(0.0, (double)w/RESIZE_FACTOR, (double)h/RESIZE_FACTOR, 0.0);
//     glMatrixMode(GL_MODELVIEW);
//     }*/
//
// void step(){
//   printf("___Step___ \n");
//   //printf("%f", goalVector);
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
//   case 'V' :
//     view = DEFAULT;
//     break;
//   case 't' :
//   case 'T' :
//     view = TRAILING;
//     break;
//   case 's':
//   case 'S' :
//     view = SIDE;
//     break;
//   default:
//     break;
//   }
//   //steering and speed
//   switch(action) {
//     case GLFW_RELEASE:
//       switch(key) {
//         case GLFW_KEY_UP:
//           upArw = true;
//           //printf("uparw");
//           break;
//         case GLFW_KEY_DOWN:
//           downArw = true;
//           break;
//         case GLFW_KEY_LEFT:
//           lArw = true;
//           break;
//         case GLFW_KEY_RIGHT:
//           rArw = true;
//           break;
//         //speed up
//         case 'u':
//           faster = true;
//           break;
//         //slow down
//         case 'd':
//           slower = true;
//           break;
//         case 'p':
//           pause = !pause;
//           break;
//         default:
//           break;
//       }
//       default:
//         break;
//     }
//     //general - step, pause, views, and add and minus boids
//     switch(action) {
//       case GLFW_RELEASE:
//         switch(key) {
//           case GLFW_KEY_SPACE:
//             if(pause == true){
//               stepBool = true;
//               step();
//             }
//             else {
//               printf("ERROR: Press 'p' for pause before trying to step the program!");
//             }
//             break;
//           case GLFW_KEY_KP_ADD:
//             addB = true;
//             break;
//           case GLFW_KEY_KP_SUBTRACT:
//             minusB = true;
//             break;
//           default:
//             break;
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
//     srand(time(NULL));
//
//     // Initialize the library
//   if (!glfwInit())
//     exit(EXIT_FAILURE);
//
//   // Create a window and its OpenGL context
//   window = glfwCreateWindow(850, 800, "Hello GL!", NULL, NULL);
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
//   //glfwMakeContextCurrent(window);
//   //glfwSetFramebufferSizeCallback(window, framebuffer_resize);
//
//   init();
//   // Loop until the user closes the window
//   while (!glfwWindowShouldClose(window)) {
//     if(pause == false || stepBool == true) {
//       //goal[2] += .0005;
//       //cenFlock[2] += .0005;
//        //*******setup**********//
//       //LIST
//       //push(&headd, &aa, dsize);
//       //printList(headi, printI);
//       // int e = valD(headi, 0, 4);
//       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//       glClearDepth(1.0);
//       glLoadIdentity();
//       if(view == DEFAULT) {
// defaultView(cenFlock);
//       } else if (view == SIDE) {
// sideView(cenFlock);
//       } else {
// trailView(cenFlock);
//       }
//       //bool dview = true, sideVw = false, tView = false;
//
//       //********update*********//
//       //spead, number of birds, weight adjustment
//
//       //*********draw*********//
//       draw_cube();
//       draw_tower();
//       glColor3f(1.0, 1.0, 0.0);
//       for(int i = 0; i < 3; i++) {
// goal[i] += velocity;
//         cenFlock[i] += velocity;
//       }
//       draw_boid(boid_vertices, cenFlock);
//       draw_boid(boid_vertices, goal);
//       for(int i = 1; i <= numBoid; i++){
//         temp[0] = valF(headx, i, numBoid) + iter*velocity;
// temp[1] = valF(heady, i, numBoid) + iter*velocity;
// temp[2] = valF(headz, i, numBoid) + iter*velocity;
// draw_boid(boid_vertices, temp);
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




void arrToMat2(GLfloat mat1[2][2], GLfloat arr[2], int size) {
  int i, j;
  int count = 0;
  for(i = 0; i < size; i++) {
    for(j = 0; j < size; j++) {
      mat1[i][j] = arr[count];
      count++;
    }
  }
}

void arrToMat3(GLfloat mat1[3][3], GLfloat arr[3], int size) {
  int i, j;
  int count = 0;
  for(i = 0; i < size; i++) {
    for(j = 0; j < size; j++) {
      mat1[i][j] = arr[count];
      count++;
    }
  }
}

void arrToMat4(GLfloat mat1[4][4], GLfloat arr[4], int size) {
  int i, j;
  int count = 0;
  for(i = 0; i < size; i++) {
    for(j = 0; j < size; j++) {
      mat1[i][j] = arr[count];
      count++;
    }
  }
}

void mattToArr(GLfloat arr[], GLfloat mat1[][], int size) {
  int i, j;
  int count = 0;
  for(i = 0; i < size; i++) {
    for(j = 0; j < size; j++) {
      arr[count] = mat1[i][j];
      count++;
    } //for
  } //for
}

//result is empty array, size is 4x4, !worry about 3x4, etc.
void multiFloat(GLfloat mat1[], GLfloat mat2[], GLfloat result[], int size) {
  GLfloat tot;
  int count = 0;
  int i, j, k;
  GLfloat matSize2Num1[2][2];
  GLfloat matSize2Num2[2][2];
  GLfloat matSize3Num1[3][3];
  GLfloat matSize3Num2[3][3];
  GLfloat matSize4Num1[4][4];
  GLfloat matSize4Num2[4][4];

  if(size ==2) {
    arrToMat(mat1, matSize2Num1, size);
    arrToMat(mat2, matSize2Num2, size);
    for(i = 0; i < size; i++) { //for each element in a column
      for(j = 0; j < size; j++) { //for each element in a row
	       tot = 0;
         for(k = 0; k < size; k++) {//add togther multiplied rows
           tot += matSize2Num2[i][k] * matSize2Num2[k][j];
         } //for
         result[count] = tot;
         count++;
       }
     }
   }
   else if(size ==3) {
     arrToMat(mat1, matSize3Num1, size);
     arrToMat(mat2, matSize3Num2, size);
     for(i = 0; i < size; i++) { //for each element in a column
       for(j = 0; j < size; j++) { //for each element in a row
         tot = 0;
         for(k = 0; k < size; k++) {//add togther multiplied rows
           tot += matSize3Num2[i][k] * matSize3Num2[k][j];
         } //for
         result[count] = tot;
         count++;
       }
     }
   }
   else if(size == 4) {
     arrToMat(mat1, matSize4Num1, size);
     arrToMat(mat2, matSize4Num2, size);
     for(i = 0; i < size; i++) { //for each element in a column
       for(j = 0; j < size; j++) { //for each element in a row
         tot = 0;
         for(k = 0; k < size; k++) {//add togther multiplied rows
           tot +=  matSize4Num1[i][k] * matSize4Num2[k][j];
         } //for
         result[count] = tot;
         count++;
       }
     }
   }
 } //multifloat

//vec2 cross product returns float
//  GLfloat vec2CrossProductRetFloat(vector2 vec1, vector2 vec2) {
//    GLfloat left = vec1.vec2Arr[0] * vec2.vec2Arr[1];
//    GLfloat right = vec2.vec2Arr[1] * vec2.vec2Arr[0];
//    return left - right;
//  }
//
//  //vec2 cross product returns 2d vector
//  vector2 vec2CrossProductRetVec2(vector2 vec1, vector2 vec2) {
//    GLfloat left = vec1.vec2Arr[0] * vec2.vec2Arr[1];
//    GLfloat right = vec2.vec2Arr[1] * vec2.vec2Arr[0];
//    return vec2(left, right);
//  }
//
// //vec3 cross pdocut returns 3d vector
// vector3 vec3CrossProductRetVec3(vector3 vec1, vector3 vec2){
//   GLfloat firstMult = vec1.vec3Arr[1] * vec2.vec3Arr[2] - vec1.vec3Arr[2]*vec2.vec3Arr[1];
//   GLfloat secondMult = vec1.vec3Arr[2] * vec2.vec3Arr[0] - vec1.vec3Arr[0]*vec2.vec3Arr[2];
//   GLfloat thirdMult = vec1.vec3Arr[0] * vec2.vec3Arr[1] - vec1.vec3Arr[1] * vec2.vec3Arr[0];
//   return vector3(firstMult, secondMult, thirdMult);
// }
//
// //vec3 dot product returns float
// GLfloat vec3DotProductGLfloat(vector3 vec1, vector3 vec2){
//     return vec1.vec3Arr[0]*vec2.vec3Arr[0]+vec1.vec3Arr[1]*vec2.vec3Arr[1]+
//     vec1.vec3Arr[2]*vec2.vec3Arr[2];
// }
//
// //mat4 translate, etc
// mat4 transf(vector3 v) {
//   return mat4(
//     1, 0, 0, 0,
//     0, 1, 0, 0,
//     0, 0, 1, 0,
//     0, 0, 0, 0,
//     v.vec3Arr[0], v.vec3Arr[1], v.vec3Arr[2], 2
//   );
// }
//
// mat4 rot8(vector3 v, GLfloat angle) {
//   v.normalizeVec3();
//   return mat4(
//
//   )
// }
