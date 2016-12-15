#ifndef BOID_H
#define BOID_H
#include "common.hpp"
int numBoid = 0;
GLfloat boid_vertices[4][3];

GLfloat flap[200], posx[200], posy[200], posz[200], velx[200], vely[200], velz[200];

GLubyte boid_wireframe_indices[10] = {
  0, 1,
  1, 2,
  2, 0,
  0, 3,
  3, 1
};

void draw_goalBoid(GLfloat pos[3]) {
  /*boid_vertices[0][0] = (pos[0]);
  boid_vertices[0][1] = (pos[1]+.05);
  boid_vertices[0][2] = (pos[2]);
  boid_vertices[1][0] = (pos[0]);
  boid_vertices[1][1] = (pos[1]+.05);
  boid_vertices[1][2] = (pos[2]-.025);
  boid_vertices[2][0] = (pos[0]-.025);
  boid_vertices[2][1] = (pos[1]+.075);
  boid_vertices[2][2] = (pos[2]-.0125);
  boid_vertices[3][0] = (pos[0]+.025);
  boid_vertices[3][1] = (pos[1]+.075);
  boid_vertices[3][2] = (pos[2]-.0125);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, boid_vertices);
  glColor3f(1, 0, 0);
  glDrawElements(GL_LINES, 10, GL_UNSIGNED_BYTE, boid_wireframe_indices);
  glDisableClientState(GL_VERTEX_ARRAY);*/
}

void draw_boid(GLfloat pos[3]) {
  /*boid_vertices[0][0] = (pos[0]);
  boid_vertices[0][1] = (pos[1]+.05);
  boid_vertices[0][2] = (pos[2]);

  boid_vertices[1][0] = (pos[0]);
  boid_vertices[1][1] = (pos[1]+.05);
  boid_vertices[1][2] = (pos[2]-.025);

  boid_vertices[2][0] = (pos[0]-.025);
  boid_vertices[2][1] = (pos[1]+.075);
  boid_vertices[2][2] = (pos[2]-.0125);

  boid_vertices[3][0] = (pos[0]+.025);
  boid_vertices[3][1] = (pos[1]+.075);
  boid_vertices[3][2] = (pos[2]-.0125);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, boid_vertices);
  glColor3f(1, 1, 1);
  glDrawElements(GL_LINES, 10, GL_UNSIGNED_BYTE, boid_wireframe_indices);
  glDisableClientState(GL_VERTEX_ARRAY);*/
}

void draw_boidFlap(GLfloat pos[3]) {
  //origin
  /*boid_vertices[0][0] = pos[0];
  boid_vertices[0][1] = pos[1]+.05;
  boid_vertices[0][2] = pos[2];
  //body rod
  boid_vertices[1][0] = pos[0];
  boid_vertices[1][1] = pos[1]+.05;
  boid_vertices[1][2] = pos[2]-.025;
  //
  boid_vertices[2][0] = pos[0]-.025;
  boid_vertices[2][1] = pos[1]+.06;
  boid_vertices[2][2] = pos[2]-.0125;

  boid_vertices[3][0] = pos[0]+.025;
  boid_vertices[3][1] = pos[1]+.06;
  boid_vertices[3][2] = pos[2]-.0125;
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, boid_vertices);
  glColor3f(1, 1, 1);
  glDrawElements(GL_LINES, 10, GL_UNSIGNED_BYTE, boid_wireframe_indices);
  glDisableClientState(GL_VERTEX_ARRAY);*/
}

void addBoid() {
  //add on to end of array
  //Incriment

  float randX, randY, randZ, deciX, deciY, deciZ, fIndex;
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

  posx[numBoid] = randX;
  posy[numBoid] = randY;
  posz[numBoid] = randZ;

  //intialize lists to be zero
  GLfloat Zero = 0;

  velx[numBoid] = 0;
  vely[numBoid] = 0;
  velz[numBoid] = 0;

  //flap state
  fIndex = rand()%399;
  flap[numBoid] = fIndex;
  numBoid++;

}

void minusBoid() {
  if(numBoid >= 1){
  printf("boid taken away!");
  //int index = rand()%numBoid+1;
  int index = rand()%numBoid;
  printf("% d index \n", index);

  posx[index] = posx[numBoid-1];
  posy[index] = posy[numBoid-1];
  posz[index] = posz[numBoid-1];

  velx[index] = velx[numBoid-1];
  vely[index] = vely[numBoid-1];
  velz[index] = velz[numBoid-1];

  flap[index] = flap[numBoid-1];

  numBoid--;

  } else {
    printf("No boids to delete! ! !");
  }
}

#endif
