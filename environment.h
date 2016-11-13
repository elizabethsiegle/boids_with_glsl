#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#define X 2.5
#define Y 0
#define Z 2.5
#define TX .03
#define TY .2
#define TZ .03
enum {DEFAULT, TRAILING, SIDE}; // 0, 1, 2

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

#endif
