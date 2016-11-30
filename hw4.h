#ifndef HW4_H
#define HW4_H

GLuint make_bo(GLenum type, const void *buf, GLsizei buf_size);
void init();
void moveTarget(int i, float spW);
void separation();
void alignment();
void cohesion();
void seek();
void defaultView(GLfloat centerFlock[3]);
void sideView(GLfloat centerFlock[3]);
void trailView(GLfloat centerFlock[3]);
GLfloat normY(GLfloat x, GLfloat y, GLfloat z, GLfloat x2, GLfloat y2, GLfloat z2);
GLfloat normZ(GLfloat x, GLfloat y, GLfloat z, GLfloat x2, GLfloat y2, GLfloat z2);
GLfloat square(GLfloat s);
GLfloat dist(GLfloat x, GLfloat y, GLfloat z, GLfloat x2, GLfloat y2, GLfloat z2);
void reshape(GLFWwindow *w, int width, int height);
void normalize(int i);
void step(GLfloat goal[3]);
void keyboard(GLFWwindow *w, int key, int scancode, int action, int mods);
void render();
#endif
