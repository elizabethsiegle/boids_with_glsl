#include "list.c" //idk man, undef ref to valf, etc
#include "boid.c" //idk man, extern int numBoid??
#include "environment.h"
// #include "common.cpp"
#include "hw4.h"
int view = 0;
//********Globals*******//
//Velocity, acceleration and heads
Node *velx = NULL;
Node *vely = NULL;
Node *velz = NULL;
Node *posx = NULL;
Node *posy = NULL;
Node *posz = NULL;
Node *ax = NULL;
Node *ay = NULL;
Node *az = NULL;
Node *headx = NULL;
float weightSp = .0005; //will go up, down based on key press
GLfloat boid_vertices[4][3];
GLubyte boid_wireframe_indices[10] = {
  0, 1,
  1, 2,
  2, 0,
  0, 3,
  3, 1
};
//Sep, align and coh
unsigned dsize = sizeof(double);
unsigned fsize = sizeof(float);
GLfloat ali[3];//hw4
GLfloat sep[3];
GLfloat coh[3];
GLfloat gVec[3];
GLfloat acc[3];
GLfloat max[3] = {30, 30, 30};
GLfloat min[3] = {.1, .1, .1};
GLfloat direction[3];
GLfloat vel[3];
GLfloat target[3] = {.5, .5, .5};
GLfloat cToGm, midpt, rad = .1, maxSpeed = .5;
GLfloat tempS;
float speed = .0005;
bool addB = false, minusB = false;
bool slower = false, faster = false;
bool pause = false, stepBool = false;
//extern int numBoid; //comment, doesn't work--uncomment, undef ref valf
// //shadingGLfloat weight, int i
GLuint program, vao, vbo1, vbo2, vbo3, vbo4,  pos, col, ind, MV;

// GLuint make_bo(GLenum type, const void *buf, GLsizei buf_size) {
//     GLuint bufnum;
//     glGenBuffers(1, &bufnum);
//     glBindBuffer(type, bufnum);
//     glBufferData(type, buf_size, buf, GL_STATIC_DRAW);
//     return bufnum;
// }

GLfloat square(GLfloat s) {
    float sqr;
    sqr = s*s;
    return sqr;
}

void init() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glColor3f(0.0, 0.0, 0.0);
  glClearDepth(1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //gluPerpspective(where camera is places)
  gluPerspective(30, 1, 1, 20);
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
  //glClearColor(0.0, 0.0, 0.0, 1.0);
}

GLfloat dist(GLfloat x, GLfloat y, GLfloat z, GLfloat x2, GLfloat y2, GLfloat z2) {
  GLfloat distance;
  GLfloat f1 = x2-x;
  GLfloat f2 = y2 - y;
  GLfloat f3 = z2 - z;
  distance = sqrt(square(f1)+square(f2)+square(f3));
  return distance;
}

void norm(GLfloat vecs[]) {
   GLfloat m = sqrt(vecs[0]*vecs[0] + vecs[1]*vecs[1] + vecs[2]*vecs[2]);
   vecs[0] = vecs[0]/m;
   vecs[1] = vecs[1]/m;
   vecs[2] = vecs[2]/m;
   //return vecs;
}

GLfloat mag(GLfloat vecs[3]) {
  GLfloat mags;
  mags = sqrt(square(vecs[0])+square(vecs[1])+square(vecs[2]));
  return mags;
}

void goalVec(GLfloat weight, int i) {
  //1) Get updated target value if needed
  //2) Steer towards target, based off difference of current position?
  //gVec[0]=valF(posx, i, numBoid) + valF(velx, i, numBoid);
  //gVec[1]=valF(posy, i, numBoid) + valF(velx, i, numBoid);
  //gVec[2]=valF(posz, i, numBoid) + valF(velx, i, numBoid);

  target[2] += .00001;
  for(int j = 0; j < 3; j++) {
    gVec[j] = target[j];//-gVec[j];
  }
  norm(gVec);
  for(int h = 0; h < 3; h++) {
    gVec[h] *= speed;
    gVec[h] *= weight;
  }
}

void render(int i) {
  //*********draw*********/
  GLfloat theta;
  GLfloat preVec[3];
  GLfloat nextVec[3];
  GLfloat pos[3];
  //use acc + vel and vel in render
  if(pause == true) {
    for(int j = 0; j < 3; j++) {
      acc[j] = 0;
    } //for
  } //if
}

void separate(GLfloat weight, int i) {
  //Collision prevention
  GLfloat p[3];
  GLfloat pO[3];
  GLfloat D;
  GLfloat count = 0;
  GLfloat seperMin  = .07;
  p[0] = valF(posx, i); //numBoid as 3rd param
  p[1] = valF(posy, i);
  p[2] = valF(posz, i);

  for(int g = 1; g <= numBoid; g++) {
    pO[0] = valF(posx, g);
    pO[1] = valF(posy, g);
    pO[2] = valF(posz, g); //with numBoid
    D = dist(p[0], p[1], p[2], pO[0], pO[1], pO[2]);
    if(D < seperMin && D != 0){
    //sep x sepy sepz
      for(int l = 0; l < 3; l++) {
         sep[l] = p[l] - pO[l];
      } //for
      norm(sep);
      for(int h = 0; h < 3; h++){
        sep[h] /= D;
      }
      count++;
     }
   }
   if (count > 0) {
     for(int k = 1; k < 3; k++) {
       sep[k] /= count;
       //weight the vector
       sep[k] *= weight;
     }
   }
   else {
     for(int p = 1; p < 3; p++) {
       sep[p] = 0;
     }
   }
   GLfloat magSep = mag(sep);
   if (magSep > 0) {
     //Steering = Desired - Velocity
     norm(sep);
     for(int m = 1; m < 3; m++) {
       sep[m] = sep[m]-vel[m];
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

  p[0] = valF(posx, i);
  p[1] = valF(posy, i);
  p[2] = valF(posz, i);

  for(int g = 1; g <= numBoid; g++) {
     pO[0] = valF(posx, g);
     pO[1] = valF(posy, g);
     pO[2] = valF(posz, g);
     D = dist(p[0], p[1], p[2], pO[0], pO[1], pO[2]);
     if (D != 0 && D < neighSize) {
       VELO[0] += valF(velx, g);
       VELO[1] += valF(vely, g);
       VELO[2] += valF(velz, g);
       count++;
     }
  }
  VEL[0] = valF(velx, i);
  VEL[1] = valF(vely, i);
  VEL[2] = valF(velz, i);
  //Get average
  if(count > 0){
    for(int h = 0; h < 3; h++) {
      VELO[h] /= count;
    }
    //Steer = Desired - Velocity
    norm(VELO);
    for(int h = 0; h < 3; h++) {
      ali[h] = VELO[h] - VEL[h];
      ali[h] *= speed;
      //weight the vector
      ali[h] *= weight;
    }
  }
  else {
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

  p[0] = valF(posx, i);
  p[1] = valF(posy, i);
  p[2] = valF(posz, i);
  VEL[0] = valF(velx, i);
  VEL[1] = valF(vely, i);
  VEL[2] = valF(velz, i);

  for(int g = 1; g <= numBoid; g++) {
    pO[0] = valF(posx, g);
    pO[1] = valF(posy, g);
    pO[2] = valF(posz, g);
    D = dist(p[0], p[1], p[2], pO[0], pO[1], pO[2]);
    if (D != 0 && D < neighSize) {
       for(int k = 0; k < numBoid; k++) {
         coh[k] += pO[k];
       }
       count++;
     }
  }
  //Make local goal
  if (count > 0) {
    for(int h = 0; h < numBoid; h++) {
      coh[h] /= count;
      //local goal = coh[] currently
      coh[h] = coh[h] - p[h];
    }
    norm(coh);
    for(int k = 0; k < numBoid; k++) {
      coh[k] *= 2; //??Needed?
      coh[k] -= VEL[k];
      coh[k] *= speed;
      //weight the vector
      coh[k] *= weight;
    }
  }
  else {
    for(int j = 0; j < numBoid; j++) {
      coh[j] = 0;
    }
  }
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

void reshape(GLFWwindow *w, int width, int height){
  printf("Got a Reshape Event");
  printf(":\t width = %d height = %d\n", width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glFrustum(-1, 1, -1, 1, 0.4, 15);
  gluPerspective(30, 1, 1, 20);
  glMatrixMode(GL_MODELVIEW);
}

void framebuffer_resize(GLFWwindow *wind, int w, int h) {
  glViewport(0, 0, w, h);
}

//todo
void ownRotate(GLdouble a) {
  GLdouble s = a;
  GLdouble c[4][4];
  c[1][1] = c[3][3] = 1.0;
  c[0][0] = c[2][2] = cos(s);
  c[2][0] = sin(s);
  c[0][2] = -c[2][0];
  //mult??
  glMultMatrixd(*c);
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
    //temp[0] = valF(posx, i, numBoid);
    ///temp[1] = valF(posy, i, numBoid);
    //temp[2] = valF(posz, i, numBoid);
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
      } //if
      else {
        printf("target can not go any lower!");
      } //else
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
      } //else
      break;
    case 'P':
    case 'p':
      pause = !pause;
      if(pause == true) {
        tempS = speed;
        speed = 0;
      }
      else {
        speed = tempS;
      }
      break;
    default:
      break;
  }
}

int main(int argc, char **argv) {
  GLFWwindow* window;
  //GLfloat cenFlock[3] = {2, 2, 2};
  srand(time(NULL));
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
  glfwSetWindowSizeCallback(window, reshape);
  glfwSetKeyCallback(window, keyboard);
  //glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_resize);
  init();
  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window)) {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearDepth(1.0);
      glLoadIdentity();
      if(view == DEFAULT) {
	       defaultView(target);
      }
      else if (view == SIDE) {
	       sideView(target);
      }
      else {
	       trailView(target);
      }
      //********update and render*********//
      draw_cube();
      draw_tower();
      ///for every bird
      for(int i = 1;  i <= numBoid; i++){
        separate(1, i);
        alignment(1.5, i);
        cohesion(1.5, i);
        goalVec(.8, i);
        //acceleration = all 3 vecs add together
        for(int h = 0;  h < 3; h++){
            acc[h] = sep[h] + ali[h] + coh[h] + gVec[h];
            //acc[h] = sep[h] + ali[h] + coh[h];
        } //for
        render(i);
      } //for
       //*****end process*****//
       glfwSwapBuffers(window);
       glfwPollEvents();
       if(stepBool == true) {
         step(target);
       } //if
       stepBool = false;
     }//while
     glfwTerminate();
     exit(EXIT_SUCCESS);
}
