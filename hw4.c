//hw4
//hw4
//start with simple
//add header file after
#include "common.hpp"
#include "list.h"
// #include "list.c" //???
#include "boid.h"
#include "environment.h"
// #include "LAB3.hpp"
//#include "initshader.hpp"
#include "mats.hpp"
#include "vecs.hpp"

extern int numBoid;

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
struct node *headx = NULL;
struct node *heady = NULL;
struct node *headz = NULL;
unsigned dsize = sizeof(double);
unsigned bsize = sizeof(bool);
unsigned isize = sizeof(int);
unsigned fsize = sizeof(float);

GLuint make_bo(GLenum type, const void *buf, GLsizei buf_size) {
    GLuint bufnum;
    glGenBuffers(1, &bufnum);
    glBindBuffer(type, bufnum);
    glBufferData(type, buf_size, buf, GL_STATIC_DRAW);
    return bufnum;
}
GLubyte boid_wireframe_indices[10] = {
  0, 1,
  1, 2,
  2, 0,
  0, 3,
  3, 1
};
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
