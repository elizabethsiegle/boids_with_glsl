
#include "common.hpp"
#include "boid.h"
#include "list.h"
extern GLubyte boid_wireframe_indices[10];
extern unsigned fsize;
extern struct node *heady;
extern struct node *headz;
extern struct node *headx;
int numBoid = 0;
void draw_boid(GLfloat pos[3]) {
  GLfloat boid_vertices[4][3];
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
  randX = rand()%2;
  randY = rand()%2;
  randZ = rand()%2;
  deciX = ((rand()%999999));
  deciY = ((rand()%999999));
  deciZ = ((rand()%999999));
  deciX /= 1000000;
  deciY /= 1000000;
  deciZ /= 1000000;
  randX += deciX;
  randY += deciY;
  randZ += deciZ;
  printf("boid added!");
  push(&headx, &randX, fsize);
  push(&heady, &randY, fsize);
  push(&headz, &randZ, fsize);
  numBoid += 1;
}

void minusBoid() {
  if(numBoid != 1){
  printf("boid taken away!");
  //int range = numBoid-1;
  int index = rand()%numBoid+1;
  printf("% d index \n", index);
  deleteNode(&headx, index, numBoid);
  deleteNode(&heady, index, numBoid);
  deleteNode(&headz, index, numBoid);
  numBoid--;
  } else {
    printf("No boids to delete! ! !");
  }
}

//start with simple
//add header file after
// #include <stdlib.h>
// #include <stdio.h>
// #include <math.h>
// #include <time.h>
// #include <stdbool.h>
// #ifdef __APPLE__
// #include <GLFW/glfw3.h>
// #include <GL/glu.h>
// #else
// #include <GLFW/glfw3.h>
// #include <GL/glu.h>
// #endif
// #include "list.c"
// #include "boid.h"
// #include "environment.h"
// int view = 0;
// //********Globals*******//
// //Velocity, acceleration and heads
// Node *velx = NULL;
// Node *vely = NULL;
// Node *velz = NULL;
// Node *ax = NULL;
// Node *ay = NULL;
// Node *az = NULL;
// float weightSp = .0005; //will go up, down based on key press
//
// //Sep, align and coh
// Node *allx = NULL;
// Node *ally = NULL;
// Node *allz = NULL;
// Node *sepx = NULL;
// Node *sepy = NULL;
// Node *sepz = NULL;
// Node *cox = NULL;
// Node *coy = NULL;
// Node *coz = NULL;
//
// unsigned dsize = sizeof(double);
// unsigned bsize = sizeof(bool);
// unsigned isize = sizeof(int);
//
// GLfloat max[3] = {30, 30, 30};
// GLfloat min[3] = {.1, .1, .1};
// GLfloat direction[3];
// GLfloat vel[3];
// GLfloat target[3] = {.5, .5, .5};
// GLfloat cToGm, midpt, rad = .1;
// bool addB = false, minusB = false;
// bool slower = false, faster = false;
// bool pause = false, stepBool = false;
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
// void moveTarget(int i, float spW){
//     //x, y, z
//     vel[0]=valF(headx, i, numBoid);
//     vel[1]=valF(heady, i, numBoid);
//     vel[2]=valF(headz, i, numBoid);
//     for(int j = 0; j < 3; j++) {
//       vel[j] = target[j]-vel[j];
//       if(!pause) {
//         vel[j] *= weightSp;
//       }
//       else {
//         vel[j] *= 0;
//       }
//       // printf("%f", weightSp);
//       // printf("\n");
//     }
// }
//
// void separation() {
//   //Method checks for nearby boids and steers away
//   //collision function
//   //checks for all boids so that they don't collide
//   //array of boids with x, y, z's for all
//   //GLfloat seper  = .08;
//   //for(int i = 1; i <= numBoid; i++){
//   //  addF(&headx, i, numBoid, seper);
//   //}
// }
//
// void alignment() {
//   // For every nearby boid in the system, calculate the average velocity
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
//   // For the average location (i.e. center) of all nearby boids, calculate steering vector towards that location
// }
//
// void seek() {
//   //minus goal-currentPos
//   //normalize?
//   //
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
// GLfloat normX(GLfloat x, GLfloat y, GLfloat z, GLfloat x2, GLfloat y2, GLfloat z2) {
//   GLfloat mag = sqrt(x*x2 + y*y2 + z*z2);
//   x = x2/mag;
//   return x;
// }
//
// GLfloat normY(GLfloat x, GLfloat y, GLfloat z, GLfloat x2, GLfloat y2, GLfloat z2) {
//   GLfloat mag = sqrt(x*x2 + y*y2 + z*z2);
//   y = y2/mag;
//   return y;
// }
//
//
// GLfloat normZ(GLfloat x, GLfloat y, GLfloat z, GLfloat x2, GLfloat y2, GLfloat z2) {
//   GLfloat mag = sqrt(x*x2 + y*y2 + z*z2);
//   z = z2/mag;
//   return z;
// }
//
//
// GLfloat square(GLfloat s) {
//     float sqr;
//     sqr = s*s;
//     return sqr;
// }
//
// GLfloat dist(GLfloat x, GLfloat y, GLfloat z, GLfloat x2, GLfloat y2, GLfloat z2) {
//   GLfloat distance;
//   distance = sqrt(square(x2-x)+square(y2-y)+square(z2-z));
//   return distance;
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
// void normalize(int i) {
//    GLfloat xu = valF(headx, i, numBoid);
//    GLfloat yu = valF(heady, i, numBoid);
//    GLfloat zu = valF(headz, i, numBoid);
//    GLfloat m = 1/sqrt(xu*xu + yu*yu + zu*zu);
//    multiF(&headx, i, numBoid, m);
//    multiF(&heady, i, numBoid, m);
//    multiF(&headz, i, numBoid, m);
// }
//
// void step(GLfloat goal[3]){
//   printf("\n___Step___ \n");
//   printf("Goal");
//   for(int i = 0; i < 3; i++) {
//     printf("%f ", goal[i]);
//    }
//   printf("/n");
//   GLfloat temp[3];
//
//   for(int i = 1; i <= numBoid; i++) {
//     printf("curent pos of");
//     printf("%d ", i);
//     temp[0] = valF(headx, i, numBoid);
//     temp[1] = valF(heady, i, numBoid);
//     temp[2] = valF(headz, i, numBoid);
//     for(int j = 0; j < 3; j++) {
//       printf(" %f ", temp[j]);
//     }
//     printf("\n");
//   }
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
//   break;
//   default:
//   break;
//   }
//    //steering and speed
//    //general - step, pause, views, and add and minus boids
//    switch(action) {
//      case GLFW_PRESS:
//         switch(key) {
// 	case GLFW_KEY_ENTER:
//            addBoid();
//         break;
//         case GLFW_KEY_END:
//          minusBoid();
//         break;
//         case GLFW_KEY_SPACE:
// 	       stepBool = true;
//         break;
//
//         case GLFW_KEY_UP:
// 	  target[1] += .1;
//         break;
//         case GLFW_KEY_DOWN:
// 	  if(target[1] > .05) {
// 	    target[1] -= .1;
// 	  } else {
// 	    printf("target can not go any lower!");
// 	  }
//         break;
//         case GLFW_KEY_LEFT:
// 	  target[0] += .1;
//         break;
//         case GLFW_KEY_RIGHT:
// 	  target[0] -= .1;
//         break;
//         //speed up
//         case 'U':
//         case 'u':
//           weightSp+=0.0002;
// 	  //given plus or minus x value calulate y value
//         break;
//         //slow down
//         case 'D':
//         case 'd':
//           if(weightSp > 0) {
//             weightSp-=0.0002;
//           }
//           else {
//             weightSp = .000100;
//           }
//         break;
//         case 'P':
//         case 'p':
//           pause = !pause;
//         break;
//         default:
//           break;
//       }
//         default:
//         break;
//      }
// }
//
// void render() {
//   //*********draw*********//
//   float mult;
//   draw_cube();
//   draw_tower();
//   GLfloat temp[3];
//   for(int i = 1; i <= numBoid; i++){
//     if(!pause) {
//       mult = weightSp;
//     }
//     else {
//       mult = 0;
//     }
//     moveTarget(i, mult);
//     temp[0] = valF(headx, i, numBoid) + vel[0];
//     temp[1] = valF(heady, i, numBoid) + vel[1];
//     temp[2] = valF(headz, i, numBoid) + vel[2];
//     draw_boid(temp);
//     printf("%d", i);
//     printf("\n");
//     printf("%d", headx);
//     printf("\n");
//     //update values
//     addF(&headx, i, numBoid, vel[0]);
//     addF(&heady, i, numBoid, vel[1]);
//     addF(&headz, i, numBoid, vel[2]);
//     } //for
//   }
//
// int main(int argc, char **argv) {
//   GLFWwindow* window;
//
//   glColor3f(1.0, 1.0, 0.0);
//   //GLfloat cenFlock[3] = {target[0]-rad, target[1], target[2]};
//   //GLfloat cenFlock[3] = {2, 2, 2};
//   srand(time(NULL));
//
//   // Initialize the library
//   if (!glfwInit()) {
//     exit(EXIT_FAILURE);
//   }
//   // Create a window and its OpenGL context
//   window = glfwCreateWindow(850, 800, "hw3!", NULL, NULL);
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
//     // if(!pause) {
//       //goal[2] += .0005;
//       //cenFlock[2] += .0005;
//       //*******setup**********//
//       //LIST
//       //push(&headd, &aa, dsize);
//       //printList(headi, printI);
//       // int e = valD(headi, 0, 4);
//       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//       glClearDepth(1.0);
//       glLoadIdentity();
//       if(view == DEFAULT) {
// 	       defaultView(target);
//       } else if (view == SIDE) {
// 	       sideView(target);
//       } else {
// 	       trailView(target);
//       }
//       //bool dview = true, sideVw = false, tView = false;
//
//       //********update*********//
//       //spead, number of birds, weight adjustment
//       render();
//       //seperate();
//       //allignment();
//       //cohesion();
//
//
//       //*****end process*****//
//       glfwSwapBuffers(window);
//       glfwPollEvents();
//       // if(stepBool == true) {
//       //   step(target);
//       // }
//       //stepBool = false;
//
//       //print
//       /*for(int h = 1; h <= numBoid; h++) {
//        printf("curent pos of");
//        printf("%d ", h);
//        temp[0] = valF(headx, h, numBoid);
//        temp[1] = valF(heady, h, numBoid);
//        temp[2] = valF(headz, h, numBoid);
//        for(int l = 0; l < 3; l++) {
//            printf(" %f ", temp[l]);
//        }
//        printf("\n");
//        }*/
//     //  } //if statement
//     //  else {
//     //    printf("why");
//     //  }
//   }//while
//
//   glfwTerminate();
//   exit(EXIT_SUCCESS);
// }
//
//
// // #include "boid.h"
// // GLfloat cube_vertices[][3] = {
// //   {-1*X, -Y, Z},
// //   {-X, Y,  Z},
// //   {X,  Y,  Z},
// //   {X, -Y,  Z},
// //   {-X,-Y, -Z},
// //   {-X, Y, -Z},
// //   {X,  Y, -Z},
// //   {X, -Y, -Z}
// // };
// //
// // GLfloat boid_vertices[][3] = {
// //   {BX, BY+.1, BZ},
// //   {BX, BY+.1, BZ-.05},
// //   {BX-.05, BY+.15, BZ-.025},
// //   {BX+.05, BY+.15, BZ-.025},
// // };
// //
// //
// // GLfloat cube_colors[][3] ={
// //   {1.0,0.0,0.0},
// //   {0.0,0.0,0.0},
// //   {1.0,0.0,0.0},
// //   {1.0,1.0,0.0},
// //   {0.0,1.0,0.0},
// //   {0.0,1.0,0.0},
// //   {0.0,0.0,1.0},
// //   {1.0,0.0,1.0},
// //   {1.0,1.0,1.0},
// //   {0.0,1.0,1.0},
// // };
// //
// // GLubyte cube_indices[24] = {
// //   0,3,2,1,
// //   2,3,7,6,
// //   0,4,7,3,
// //   1,2,6,5,
// //   4,5,6,7,
// //   0,1,5,4
// // };
// //
// // GLubyte cube_wireframe_indices[48] = {
// //   0, 1,
// //   1, 2,
// //   2, 3,
// //   3, 0,
// //   6, 5,
// //   5, 1,
// //   1, 2,
// //   2, 6,
// //   7, 4,
// //   4, 5,
// //   5, 6,
// //   6, 7,
// //   7, 3,
// //   3, 0,
// //   0, 4,
// //   4, 7,
// //   4, 0,
// //   0, 1,
// //   1, 5,
// //   5, 4,
// //   3, 7,
// //   7, 6,
// //   6, 2,
// //   2, 3
// // };
// //
// // GLubyte boid_wireframe_indices[10] = {
// //   0, 1,
// //   1, 2,
// //   2, 0,
// //   0, 3,
// //   3, 1
// // };
// //
// //
// // void draw_cube() {
// //   glEnableClientState(GL_COLOR_ARRAY);
// //   glEnableClientState(GL_VERTEX_ARRAY);
// //   glVertexPointer(3, GL_FLOAT, 0, cube_vertices);
// //   glColorPointer(3, GL_FLOAT, 0, cube_colors);
// //   glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cube_indices);
// //   glDisableClientState(GL_COLOR_ARRAY);
// //   glDisableClientState(GL_VERTEX_ARRAY);
// // }
// //
// // void draw_wireframe_cube() {
// //   glEnableClientState(GL_VERTEX_ARRAY);
// //   glVertexPointer(3, GL_FLOAT, 0, cube_vertices);
// //   glColor3f(1,1,1);
// //   glDrawElements(GL_LINES, 48, GL_UNSIGNED_BYTE, cube_wireframe_indices);
// //   glDisableClientState(GL_VERTEX_ARRAY);
// // }
// //
// // void draw_boid() {
// //   glEnableClientState(GL_VERTEX_ARRAY);
// //   glVertexPointer(3, GL_FLOAT, 0, boid_vertices);
// //   glColor3f(1,1,1); //white
// //   glDrawElements(GL_LINES, 10, GL_UNSIGNED_BYTE, boid_wireframe_indices);
// //   glDisableClientState(GL_VERTEX_ARRAY);
// // }
// //
// // //TODO
// // void draw_boids() {
// //   int i;
// //   for(i = 1; i <= NUMBOIDS; i++) {
// //     draw_boid();
// //   }
// // }
// //
// // void init() {
// //   // Set the clear color to black
// //   glClearColor(0.0, 0.0, 0.0, 1.0);
// //   glColor3f(1.0, 1.0, 0.0);
// //   glClearDepth(1.0);
// //   glMatrixMode(GL_PROJECTION);
// //   glLoadIdentity();
// //   glFrustum(-1, 1, -1, 1, 1.1, 15);
// //   glMatrixMode(GL_MODELVIEW);
// //   glEnable(GL_DEPTH_TEST);
// //   //glShadeModel(GL_FLAT);
// // }
// //
// //
// // void draw_cube_wireframe(){
// //   glDisableClientState(GL_COLOR_ARRAY);
// //   glVertexPointer(3, GL_FLOAT, 0, cube_vertices);
// // }
// //
// // void reshape(GLFWwindow *w, int width, int height){
// //   printf("Got a Reshape Event");
// //   printf(":\t width = %d height = %d\n", width, height);
// //   glMatrixMode(GL_PROJECTION);
// //   glLoadIdentity();
// //   glFrustum(-1, 1, -1, 1, 0.4, 2);
// //   glMatrixMode(GL_MODELVIEW);
// //
// //   // Set the new viewport size
// //   glViewport(0, 0, width, height);
// // }
// //
// // int main(int argc, char **argv) {
// //     GLFWwindow* window;
// //
// //     // Initialize the library
// //   if (!glfwInit())
// //     exit(EXIT_FAILURE);
// //
// //   // Create a window and its OpenGL context
// //   window = glfwCreateWindow(850, 800, "boid", NULL, NULL);
// //   if (!window){
// //     glfwTerminate();
// //     exit(EXIT_FAILURE);
// //   }
// //
// //   glfwSetWindowPos(window, 100, 100);
// //   // Make the window's context current
// //   glfwMakeContextCurrent(window);
// //
// //  // Assign reshape() to be the function called whenever
// //  // a reshape event occurs
// //   glfwSetWindowSizeCallback(window, reshape);
// //
// //   init();
// //   // Loop until the user closes the window
// //   while (!glfwWindowShouldClose(window)) {
// //     // clear to background color
// //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// //     glClearDepth(1.0);
// //     glMatrixMode(GL_MODELVIEW);
// //     glLoadIdentity();
// //     gluLookAt(1, 1, 1, 0.5, 0.5 ,0.5, 0, 1, 0);
// //     draw_cube();
// //     draw_wireframe_cube();
// //     draw_boids();
// //     glfwSwapBuffers(window);
// //
// //     // Poll for and process events
// //     glfwPollEvents();
// //   }
// //
// //   glfwTerminate();
// //   exit(EXIT_SUCCESS);
// // }
