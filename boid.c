
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
  Point *hpos;
  Point *hvel;
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

  hpos = makePoint(randX, randY, randZ);
  hvel = makePoint(0.5, 0.5, 0.5); //vel, need to change
  headx= makeNode(*hpos, *hvel, numBoid);
  printf("boid added!");
  push(headx);
  numBoid += 1;
}

void minusBoid() {
  if(numBoid != 1){
  printf("boid taken away!");
  //int range = numBoid-1;
  int index = rand()%numBoid+1;
  printf("% d index \n", index);
  deleteNode(headx);
  numBoid--;
  } else {
    printf("No boids to delete! ! !");
  }
}
