//Lab 03
//start with simple
//add header file after
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "LAB3.hpp"
//#include "lab3.h"
#ifdef __APPLE__
#include <GLFW/glfw3.h>
//#include <GL/glu.h>
#else
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#endif

void init(){
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor3f(0.0, 0.0, 1.0);
  glClearDepth(1.0);
  //glEnable(GL_CULL);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glOrtho(-1, 2, -1, 2, 1, -1);
  //glFrustum(-2, 2, -2, 3, -1, 2);
  gluPerspective(150, 1, 1, 15);
  glEnable(GL_DEPTH_TEST);
}

void drawGround() {
  //for(int i = 0; i < n; i += 3)
  //glDrawArrays(GL_LINE_LOOP, i, 3);
  //front face
    glBegin(GL_LINE_LOOP);

    glVertex3f(-.5*2, -.5*2, 0);
    glVertex3f(-.5*2, .5*2, 0);
    glVertex3f(.5*2, .5*2, 0);
    glVertex3f(.5*2, -.5*2, 0);

    glEnd();

    //top
    glBegin(GL_LINE_LOOP);

    glVertex3f(-.5*2, .5*2, 0);
    glVertex3f(.5*2, .5*2, 0);
    glVertex3f(.5*2, .5*2, -1*2);
    glVertex3f(-.5*2, .5*2, -1*2);

    glEnd();

    //bottom
    glBegin(GL_LINE_LOOP);

    glVertex3f(-.5*2, -.5*2, 0);
    glVertex3f(-.5*2, -.5*2, -1*2);
    glVertex3f(.5*2, -.5*2, -1*2);
    glVertex3f(.5*2, -.5*2, 0);

    glEnd();

    //left
    glBegin(GL_LINE_LOOP);

    glVertex3f(-.5*2, .5*2, 0);
    glVertex3f(-.5*2, .5*2, -1*2);
    glVertex3f(-.5*2, -.5*2, -1*2);
    glVertex3f(-.5*2, -.5*2, 0);

    glEnd();

    //right
    glBegin(GL_LINE_LOOP);

    glVertex3f(.5*2, .5*2, 0);
    glVertex3f(.5*2, -.5*2, 0);
    glVertex3f(.5*2, -.5*2, -1*2);
    glVertex3f(.5*2, .5*2, -1*2);

    glEnd();

    //back
    glBegin(GL_LINE_LOOP);

    glVertex3f(.5*2, .5*2, -1*2);
    glVertex3f(.5*2, -.5*2, -1*2);
    glVertex3f(-.5*2, -.5*2, -1*2);
    glVertex3f(-.5*2, .5*2, -1*2);

    glEnd();
}

int main(int argc, char **argv) {
  GLFWwindow* window;
  GLfloat *Matrix;//len=16
  GLfloat e[3] = {1, .3, 2};
  GLfloat cv[3] = {0, 0, 0};
  GLfloat uv[3] = {0, 1, 0};

  //glEnable(GL_DEPTH_TEST);

  if (!glfwInit()){
    exit(EXIT_FAILURE);
  }

  /*create windowed mode window*/
  window = glfwCreateWindow(400, 400, "help", NULL, NULL);
  if(!window){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwSetWindowPos(window, 100, 100);

  glfwMakeContextCurrent(window);

  init();

  /* loop thru til window close */
  while (!glfwWindowShouldClose(window)){
    //if(glfwGetWindow
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, Matrix);
    //int s = 0;
    //for(s = 0; s < 16; s++){
    //printf("%f", Matrix[s]);
    //}
    //printf("\n");
    //gluLookAt(1, .3, 2, 0, 0, 0, 0, 1, 0);
    // glGetFloatv(GL_MODELVIEW_MATRIX, Matrix);
    //printf("%f \n", Matrix[16]);
    glLookAtf(Matrix, e, cv, uv);
    glLoadMatrixf(Matrix);
    //glTranslatef(0, 0, 0);
    //rotatef(Matrix, 15, 15, 15);
    glLoadMatrixf(Matrix);
    drawGround();

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();
  exit(EXIT_SUCCESS);
}
