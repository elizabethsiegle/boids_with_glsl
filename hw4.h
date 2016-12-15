#ifndef HW4_H
#define HW4_H
//#include "common.hpp"

GLuint make_bo(GLenum type, const void *buf, GLsizei buf_size);
void init();
void checkWeights(int i);
void render(int i);
void goalVec(GLfloat weight, int i);
void separate(GLfloat weight, int i);
void alignment(GLfloat weight, int i);
void cohesion(GLfloat weight, int i);
void initView();
void defaultView(GLfloat centerFlock[3]);
void sideView(GLfloat centerFlock[3]);
void trailView(GLfloat centerFlock[3]);
void reshape(GLFWwindow *w, int width, int height);
void framebuffer_resize(GLFWwindow *wind, int w, int h);
void step(GLfloat goal[3]);
void keyboard(GLFWwindow *w, int key, int scancode, int action, int mods);

#endif
