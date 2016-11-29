#version 150

in vec4 vPos1;
in vec4 vPos2;
in vec4 vCol;
flat out vec4 col;
uniform mat4 m;
unfirom float t;

void main() {
     vec4 p0s = vPos2 + (vPos2 - vPos1) * t;
     gl_Position = m * p0s;
     col = vCol;
}
