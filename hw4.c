#include "common.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <cmath>
#include <vector>
#include <map>
#include "mats.hpp"
#include "boid.h"
#include "environment.h"
#include "funLib.hpp"
//#include <glm/gtx/type_ptr.hpp>

//********Globals*******//
//extern int numBoid; //add, subtract
//GLint numBoids = 500; //for arr
//Boid *boids = new Boid[numBoids];
GLfloat Matrix[16], MatrixPerp[16], matRot[16];
GLfloat ali[3];
GLfloat sep[3];
GLfloat coh[3];
GLfloat gVec[3];
GLfloat acc[3];
GLfloat target[3] = {.5, .5, .5};
GLfloat cToGm, midpt, rad = .1, maxSpeed = .5, flapCounter = 0, tempS, speed = .0005, zoom = -1;
GLfloat aliW = 1, cohW = 1, sepW = 3, goalW = .7;
bool addB = false, minusB = false, slower = false, faster = false, pause = false, stepBool = false;
int view = 0, countBoid = 0;
float lightAngle = 0.0;
GLfloat light_position[] = { 10.0, 0.0, 10.0, 0.0 };
//shading
GLuint idx_vbo, program, vao, vbo1, vbo2, vbo3, vbo4, pos, col, ind, normal, MV, modelview, proj, lite;

/* int numBoid = 0;
GLfloat flap[200], posx[200], posy[200], posz[200], velx[200], vely[200], velz[200];
GLubyte boid_wireframe_indices[10] = {
  0, 1,
  1, 2,
  2, 0,
  0, 3,
  3, 1
};
GLfloat boid_vertices[4][3];*/
GLuint make_bo(GLenum type, const void *buf, GLsizei buf_size) {
    GLuint bufnum;
    glGenBuffers(1, &bufnum);
    glBindBuffer(type, bufnum);
    glBufferData(type, buf_size, buf, GL_STATIC_DRAW);
    return bufnum;
}
void print_mat(glm::mat4 mat) {
    for(unsigned int i = 0; i < 4; i++) {
        for(unsigned int j = 0; j < 4; j++) {
            printf("%f", mat[j][i]);
        }
        printf("\n");
    }
}
void setLight() {
  // glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_SMOOTH);
  // Moving light
  GLfloat light_diffuse[] = {1.0, 0.8, 0.0, 1.0};
  GLfloat light_specular[] = {1.0, 0.8, 0.0, 1.0};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  // Still light
  GLfloat light1_ambient[] = { 0.4, 1.0, 1.0 };
  GLfloat light1_diffuse[] = { 0.3, 0.4, 0.3, 1.0 };
  GLfloat light1_position[] = { -10.0, 17.0, 7.0, 2.0 };
  glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
  // Enable light setting
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glRotatef(lightAngle, 0.0, 1.0,0);
glTranslatef(light_position[0],light_position[1],light_position[2]);
glLightfv(GL_LIGHT0, GL_POSITION, light_position);
glTranslatef(-light_position[0],-light_position[1],-light_position[2]);
glPopMatrix();
}

void display() {
  glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();


 // Display and rotate the light source around the centered object
 glPushMatrix();
 glRotatef(lightAngle, 0.0, 1.0,0);
 glTranslatef(light_position[0],light_position[1],light_position[2]);
 glLightfv(GL_LIGHT0, GL_POSITION, light_position);
 glTranslatef(-light_position[0],-light_position[1],-light_position[2]);
 glPopMatrix();
}
void init() {
  // glEnable(GL_DEPTH_TEST);
  //glShadeModel(GL_FLAT);
  // glClearColor(0.0, 0.0, 0.0, 0.0);
  // glColor3f(1.0, 1.0, 1.0);
  // glClearDepth(1.0);
  // glMatrixMode(GL_PROJECTION);
  // glLoadIdentity();
  // //gluPerpspective(where camera is placed)
  // glGetFloatv(GL_PROJECTION_MATRIX, MatrixPerp);
  // glperp(MatrixPerp, 30, 1, 1, 20);
  // glLoadMatrixf(MatrixPerp);
  //
  //   glMatrixMode(GL_MODELVIEW);
  //   glEnable(GL_DEPTH_TEST);
  //glEnable(GL_LIGHTING);
  //glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING); //????
  glEnable(GL_LIGHT0); //hmm hmm ponder
  glEnable(GL_DEPTH_TEST);
  vbo1 = make_bo(GL_ARRAY_BUFFER, boid_vertices, sizeof(boid_vertices));
  idx_vbo = make_bo(GL_ELEMENT_ARRAY_BUFFER, boid_wireframe_indices, sizeof(boid_wireframe_indices));
  glGenVertexArrays(1, &vao); //boid vao
  glBindVertexArray(vao);
  program = initshader("phong_vs.glsl", "phong_fs.glsl");
  glUseProgram(program);
  //vbo1 = make_bo(GL_ARRAY_BUFFER, boid_vertices, sizeof(boid_vertices)* sizeof(GLfloat));

  //glGenBuffers(1, &vbo1);
  glBindBuffer(GL_ARRAY_BUFFER, vbo1);
  pos = glGetAttribLocation(program, "vPosition");
  glEnableVertexAttribArray(pos);
  //MAYBEH HERE
  glVertexAttribPointer(pos, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);
  //glBindBuffer(GL_ARRAY_BUFFER, vbo2);
  normal = glGetAttribLocation(program, "vNormal");
  glEnableVertexAttribArray(normal);
  //MAYBE HERE
  glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

  modelview = glGetUniformLocation(program, "ModelView");
  glEnableVertexAttribArray(modelview); //add back?
  glVertexAttribPointer(modelview, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
  proj = glGetUniformLocation(program, "Projection");
  glEnableVertexAttribArray(proj); //add back test!
  glVertexAttribPointer(proj, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  lite = glGetUniformLocation(program, "LightPosition");
  glEnableVertexAttribArray(lite);
  glVertexAttribPointer(lite, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  //glClearColor(0.0, 0.0, 0.0, 0.0);
  setLight();

  //OLD STUFF
  //gluPerpspective(where camera is places)
  //glGetFloatv(GL_PROJECTION_MATRIX, MatrixPerp);
  //glperp(MatrixPerp, 30, 1, 1, 20);
  //glperp(ProjectionMat, 30, 1, 1, 20);
  //glLoadMatrixf(ProjectionMat);
  //
  // glMatrixMode(GL_MODELVIEW);
  // //glLoadMatrixf(ModelViewMat);
  // glEnable(GL_DEPTH_TEST);
  // glLineWidth(3);
  // glShadeModel(GL_SMOOTH);

  //Initialize the vertex position attribute from the vertex shader
  // col = glGetAttribLocation(program, "vCol");
  // MV = glGetUniformLocation(program, "finalview");
  // //create, init buffer obj
  // vbo2 = make_bo(GL_ARRAY_BUFFER, cube_vertices, sizeof(cube_vertices));
  // vbo3 = make_bo(GL_ARRAY_BUFFER, tower_vertices, sizeof(tower_vertices));
  // vbo4 = make_bo(GL_ELEMENT_ARRAY_BUFFER, cube_indices, sizeof(cube_indices));

  //glEnableVertexAttribArray(pos);
  //glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  //glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*) 0);
  //glEnableVertexAttribArray(col);
  //glVertexAttribPointer(col, 4, GL_FLOAT, GL_FALSE, 0, NULL);
  //glVertexAttribPointer(col, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  //glVertexAttribPointer(col, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  //boid

  // pos = glGetAttribLocation(program, "p0s");
  // glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
  // //ed
  // glBindBuffer(GL_ARRAY_BUFFER, vbo2);
  // col = glGetAttribLocation(program, "vColor");
  // glEnableVertexAttribArray(col);
  // glVertexAttribPointer(col, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);
  // MV = glGetUniformLocation(program, "m");
  // //glClearColor(0.0, 0.0, 0.0, 1.0);
  // glClearColor(1.0, 1.0, 1.0, 1.0);
}



void checkWeights(int i){
  GLfloat D, pos[3], posO[3], addSep, addGoal;
  pos[0] = posx[i] + velx[i];
  pos[1] = posy[i] + vely[i];
  pos[2] = posz[i] + velz[i];

  if(countBoid == numBoid) {
    sepW += (addSep/numBoid);
    goalW += (addGoal/numBoid);
    countBoid = 1;
  }

  for(int g = 0;  g < numBoid; g++){
    posO[0] = posx[g] + velx[g];
    posO[1] = posy[g] + vely[g];
    posO[2] = posz[g] + velz[g];
    D = dist(pos[0], pos[1], pos[2], posO[0], posO[1], posO[2]);
    if(D < .05) {
      if(sepW < 10) {
	addSep+=.5;
      }
    }
  }

  D = dist(pos[0], pos[1], pos[2], target[0], target[1], target[2]);
  if(D > .5) {
    if(goalW > .5) {
      addGoal -= .002;
    }
  }

  countBoid++;
}

void angleRot(GLfloat pos1[], GLfloat pos2[]) {

}

void getTurnCord(GLfloat prev[], GLfloat next[]) {
  //use target

}

void render(int i) {
  //*********draw*********//
  GLfloat theta;
  GLfloat preVec[3];
  GLfloat nextVec[3];
  GLfloat pos[3];

  //use acc + vel and vel in render

  //acc
  //get heading angle if L/R

  if(pause) {
    for(int j = 0; j < 3; j++) {
      acc[j] = 0;
    }
  }

  //get previous vector
  preVec[0] = velx[i];
  preVec[1] = vely[i];
  preVec[2] = velz[i];
  //Get the next vector
  nextVec[0] = velx[i] + acc[0];
  nextVec[1] = vely[i] + acc[1];
  nextVec[2] = velz[i] + acc[2];
  //Calculate the next position by adding next to pos
  pos[0] = posx[i] + nextVec[0];
  pos[1] = posy[i] + nextVec[1];
  pos[2] = posz[i] + nextVec[2];

  //theta = asin(mag(nextVec)/mag(preVec));
  theta = 30;

  //glGetFloatv(GL_MODELVIEW_MATRIX, matRot);
  //matTranslatef(matRot, pos[0], pos[1], pos[2]);
  //rotatef(matRot, theta, 0, 1, 0);
  //matTranslatef(matRot, -pos[0], -pos[1], -pos[2]);

  //glPushMatrix();
  //glTranslatef(pos[0], pos[1], pos[2]);
  //glRotatef(theta, 0, 1, 0);
  //glTranslatef(-pos[0], -pos[1], -pos[2]);
  flapCounter = flap[i];
  if(flapCounter == 399) {
    flap[i] = 1;
  }
  if(flapCounter <= 200) {
    draw_boid(pos);
  } else if(flapCounter > 200) {
    draw_boidFlap(pos);
  }
  if(pause != true) {
    flap[i] += 1;
  }
  //glLoadMatrixf(matRot);
  //glLoadMatrixf(Matrix);
  //glPopMatrix();

  //update values
  velx[i] += acc[0];
  vely[i] += acc[1];
  velz[i] += acc[2];
}

void goalVec(GLfloat weight, int i) {
  GLfloat curPos[3];
  GLfloat D;
  curPos[0] = posx[i] + velx[i];
  curPos[1] = posy[i] + vely[i];
  curPos[2] = posz[i] + velz[i];

  //increment target so that goal moves
  target[2] += .000027;

  //get distance
  D = dist(curPos[0], curPos[1], curPos[2], target[0], target[1], target[2]);
  //set to targert
  if(D > .01){
    for(int j = 0; j < 3; j++) {
      gVec[j] = target[j] - curPos[j];
    }
    norm(gVec);
    //multiply by speed
    for(int h = 0; h < 3; h++) {
      gVec[h] *= speed;
      gVec[h] *= weight;
    }
  } else {
    for(int k = 0; k < 3; k++) {
      gVec[k] = 0;
    }
  }
}

void separate(GLfloat weight, int i) {
  //Collision prevention
  GLfloat p[3];
  GLfloat pO[3];
  GLfloat VEL[3];
  GLfloat D;
  GLfloat diffPos[3];
  GLfloat count = 0;
  GLfloat seperMin  = .075;
  p[0] = posx[i];//+ valF(velx, i, numBoid);
  p[1] = posy[i];//+ valF(vely, i, numBoid);
  p[2] = posz[i];//+ valF(velz, i, numBoid);

  for(int g = 0; g < numBoid; g++) {
    pO[0] = posx[g];// + valF(velx, g, numBoid);
    pO[1] = posy[g];// + valF(vely, g, numBoid);
    pO[2] = posz[g];// + valF(velz, g, numBoid);
    D = dist(p[0], p[1], p[2], pO[0], pO[1], pO[2]);
    if(D < seperMin && D != 0) {
      for(int l = 0; l < 3; l++) {
         diffPos[l] = p[l] - pO[l];
      }
      norm(sep);
      for(int h = 0; h < 3; h++) {
	diffPos[h] /= D;
	sep[h] += diffPos[h];
      }
      count++;
     }
   }

   if (count > 0) {
     for(int k = 1; k < 3; k++) {
       sep[k] /= count;
       sep[k] *= weight;
     }
   } else {
     for(int p = 1; p < 3; p++) {
       sep[p] = 0;
     }
   }

   VEL[0] = velx[i];
   VEL[1] = vely[i];
   VEL[2] = velz[i];

   GLfloat magSep = mag(sep);
   if (magSep > 0) {
     norm(sep);
     for(int m = 1; m < 3; m++) {
       sep[m] = sep[m]-VEL[m];
       sep[m] *= speed;
     }
   }
}

void alignment(GLfloat weight, int i) {
  //Get average velocity for a boid based off all other boids
  GLfloat neighSize = .1;
  GLfloat p[3];
  GLfloat pO[3];
  GLfloat VELO[3];
  GLfloat VEL[3];
  GLfloat D;
  GLfloat count = 0;

  p[0] = posx[i];//+ valF(velx, i, numBoid);
  p[1] = posy[i];//+ valF(vely, i, numBoid);
  p[2] = posz[i];//+ valF(velz, i, numBoid);

  for(int g = 0; g < numBoid; g++) {
     pO[0] = posx[g];// + valF(velx, g, numBoid);
     pO[1] = posy[g];// + valF(vely, g, numBoid);
     pO[2] = posz[g];// + valF(velz, g, numBoid);
     D = dist(p[0], p[1], p[2], pO[0], pO[1], pO[2]);
     if (D != 0 && D < neighSize) {
       VELO[0] += velx[g];
       VELO[1] += vely[g];
       VELO[2] += velz[g];
       count++;
    }
  }

  VEL[0] = velx[i];
  VEL[1] = vely[i];
  VEL[2] = velz[i];

  //Get average
  if(count > 0){
    for(int h = 0; h < 3; h++) {
       VELO[h] /= count;
     }
     norm(VELO);
     for(int h = 0; h < 3; h++) {
	ali[h] = VELO[h] - VEL[h];
	ali[h] *= speed;
	//weight the vector
	ali[h] *= weight;
     }
   } else {
     for(int j = 0; j < 3; j++) {
       ali[j] = 0;
     }
  }
}

void cohesion(GLfloat weight, int i) {
  //Cohesion based off of average positions
  GLfloat neighSize = .1;
  GLfloat p[3];
  GLfloat pO[3];
  GLfloat VEL[3];
  GLfloat D;
  GLfloat count = 0;

  p[0] = posx[i];//+ valF(velx, i, numBoid);
  p[1] = posy[i];//+ valF(vely, i, numBoid);
  p[2] = posz[i];//+ valF(velz, i, numBoid);
  VEL[0] = velx[i];//+ valF(velx, i, numBoid);
  VEL[1] = vely[i];//+ valF(vely, i, numBoid);
  VEL[2] = velz[i];//+ valF(velz, i, numBoid);

  for(int g = 0; g < numBoid; g++) {
    pO[0] = posx[g];
    pO[1] = posy[g];
    pO[2] = posz[g];
    D = dist(p[0], p[1], p[2], pO[0], pO[1], pO[2]);
    if (D != 0 && D < neighSize) {
       for(int k = 0; k < 3; k++) {
	 coh[k] += pO[k];
       }
       count++;
     }
  }

   //Make local goal
   if (count > 0) {
      for(int h = 0; h < 3; h++) {
	coh[h] /= count;
        //local goal = coh[] currently
        coh[h] = coh[h] - p[h];
      }
      norm(coh);
      for(int k = 0; k < 3; k++) {
	coh[k] -= VEL[k];
        coh[k] *= speed;
	//weight the vector
	coh[k] *= weight;
      }
   } else {
       for(int j = 0; j < 3; j++) {
	 coh[j] = 0;
      }
   }
}

void defaultView(GLfloat centerFlock[3]) {//v
  //glm::vec3 eye = glm::vec3(0.0, 6.0, 0.0);
  //glm::vec3 center = glm::vec3(0.0, 0.0, 0.0);
  //glm::vec3 up = glm::vec3(0, 0, 1);

  //view_mat = glm::lookAt(eye, center, up);

  GLfloat one[3] = {-1.3, .8, zoom};//-1.3
  GLfloat two[3] = {centerFlock[0], centerFlock[1], centerFlock[2]};
  GLfloat three[3] = {0, 1, 0};
  glLookAtf(Matrix, one, two, three);
}

void sideView(GLfloat centerFlock[3]) {//s
  GLfloat szoom = zoom+1.3, c = .3;
  GLfloat one[3] = {-3, 0.4, szoom};//.3
  GLfloat two[3] = {centerFlock[0]+c, centerFlock[1]+c, centerFlock[2]+c};
  GLfloat three[3] = {0, 1, 0};
  glLookAtf(Matrix, one, two, three);
}

void trailView(GLfloat centerFlock[3]) {//t

  GLfloat tzoom = zoom - 1, c1 = .8, c2 = .1;
  GLfloat one[3] = {-.8, .8, tzoom};//-2
  GLfloat two[3] = {centerFlock[0]+c1, centerFlock[1]+c2, centerFlock[2]+c1};
  GLfloat three[3] = {0, 1, 0};
  glLookAtf(Matrix, one, two, three);
}

void reshape(GLFWwindow *w, int width, int height){
  printf("Got a Reshape Event");
  printf(":\t width = %d height = %d\n", width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glGetFloatv(GL_PROJECTION_MATRIX, MatrixPerp);
  glperp(MatrixPerp, 30, 1, 1, 20);
  glLoadMatrixf(MatrixPerp);
  glMatrixMode(GL_MODELVIEW);
}

void framebuffer_resize(GLFWwindow *wind, int w, int h) {
    glViewport(0, 0, w, h);
 }

void step(GLfloat goal[3]){
  printf("\n___Step___ \n");
  printf("Goal");
  for(int k = 0; k < 3; k++) {
    printf("%f ", goal[k]);
   }
  printf("/n");
  GLfloat temp[3];

  for(int i = 0; i < numBoid; i++) {
    printf("curent pos of");
    printf("%d ", i);
    temp[0] = posx[i];
    temp[1] = posy[i];
    temp[2] = posz[i];
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

	//Position Control
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
	  target[0] -= .1;
        break;
        case GLFW_KEY_RIGHT:
	  target[0] += .1;
        break;

        //Pace control
        case 'U':
        case 'u':
          speed += 0.0002;
        break;
        //slow down
        case 'D':
        case 'd':
          if(speed > 0.0003) {
            speed -= 0.0002;
          }
          else {
            speed = 0.0003;
          }
        break;
	case 'I':
        case 'i':
          zoom += 1;
        break;
        case 'O':
        case 'o':
          zoom -= 1;
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

int main(int argc, char **argv) {
  GLFWwindow* window;
  srand(time(NULL));

  glm::mat4 model_mat = glm::mat4(1.0);
  print_mat(model_mat);
  glm::mat4 view_mat = glm::mat4(1.0);
  print_mat(view_mat);
  glm::mat4 project_mat = glm::mat4(1.0);
  glm::vec3 eye = glm::vec3(-1.3, .8, -1.3);
  glm::vec3 center = glm::vec3(target[0], target[1], target[2]);
  glm::vec3 up = glm::vec3(0, 1, 0);

  view_mat = glm::lookAt(eye, center, up);
  project_mat = glm::perspective(45 * M_PI / 180.0, 1.0, 0.9, 6.0);
  print_mat(project_mat);
  // Initialize the library
  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }
  // Create a window and its OpenGL context
  window = glfwCreateWindow(850, 800, "hw4!", NULL, NULL);
  if (!window) {
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
  //glfwSetWindowSizeCallback(window, reshape);
  glfwSetKeyCallback(window, keyboard);
  //glfwSetFramebufferSizeCallback(window, framebuffer_resize);
  boid_vertices[0][0] = (target[0]);
  boid_vertices[0][1] = (target[1]+.05);
  boid_vertices[0][2] = (target[2]);
  boid_vertices[1][0] = (target[0]);
  boid_vertices[1][1] = (target[1]+.05);
  boid_vertices[1][2] = (target[2]-.025);
  boid_vertices[2][0] = (target[0]-.025);
  boid_vertices[2][1] = (target[1]+.075);
  boid_vertices[2][2] = (target[2]-.0125);
  boid_vertices[3][0] = (target[0]+.025);
  boid_vertices[3][1] = (target[1]+.075);
  boid_vertices[3][2] = (target[2]-.0125);

  glewExperimental = GL_TRUE;
  glewInit();
  init();
  while(!glfwWindowShouldClose(window)) {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      //model_mat = glm::rotate(angle, glm::vec3(0.0, 1.0, 0.0));
      //angle += 0.01;
      glm::mat4 modelview_mat = view_mat * model_mat;
      glUniformMatrix4fv(modelview, 1, GL_FALSE, glm::value_ptr(modelview_mat));
      glUniformMatrix4fv(proj, 1, GL_FALSE, glm::value_ptr(project_mat));
      glBindVertexArray(vao);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx_vbo);

      glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_BYTE, (void*) 0);
      //render();
      glfwSwapBuffers(window);
      glfwPollEvents();
    // Loop until the user closes the window

    //OLD WHILE
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo1);
    // glGetFloatv(GL_MODELVIEW_MATRIX, Matrix);
    /*if(view == DEFAULT) {
      defaultView(target);
    }
    else if (view == SIDE) {
      sideView(target);
    }
    else {
      trailView(target);
    }*/
    //glLoadMatrixf(Matrix);
    //********update and render*********//
    //draw_cube();
    //draw_tower();
    //for every bird
    //for(int i = 0;  i < numBoid; i++){
      //if not pause
    //  if(pause != true) {
        //checkWeights(i);
    //    separate(sepW, i);
    //    alignment(aliW, i);
	  //    cohesion(cohW, i);
	//      goalVec(goalW, i);
        //acceleration = all 3 vecs add together
    //    for(int h = 0;  h < 3; h++) {
    //      acc[h] = sep[h] + ali[h] + coh[h] + gVec[h];
	  //    } //for
    //  }
    //  render(i);
    //}
    //printf("\n %f sep", sepW);
    //printf("\n %f goal", goalW);
    //draw_goalBoid(target);
    //*****end process*****//
    glfwSwapBuffers(window);
    glfwPollEvents();
    //if(stepBool == true) {
    //  step(target);
    //}
    //stepBool = false;
  }//while
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
