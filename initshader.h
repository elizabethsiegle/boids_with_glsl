#ifndef INIT_SHADER_H
#define INIT_SHADER_H

GLuint initshader(const char* vShaderFile, const char* fShaderFile);
GLuint make_bo(GLenum type, const void *buf, GLsizei buf_size);

#endif
