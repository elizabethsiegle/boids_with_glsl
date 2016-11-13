#version 150

in vec4 vCol;
in vec4 vPos;

out vec4 fragCol;

uniform mat4 finalView;

void main() {
     vec4 finalVec = finalView*(vPos);
     gl_Position = finalVec; //vPos?
     fragCol = vCol;
}