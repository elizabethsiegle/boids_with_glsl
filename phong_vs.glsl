#version 150

in vec4 vPosition;
in vec3 vNormal;

out vec3 fN;
out vec3 fE;
out vec3 fL;

uniform mat4 ModelView;
uniform vec4 LightPosition;
uniform mat4 Projection;

void main() {
    fN = (ModelView*vec4(vNormal, 0.0)).xyz;
    fE = -((ModelView*vPosition).xyz);
    fL = LightPosition.xyz;
    if(LightPosition.w != 0.0) {
        fL = LightPosition.xyz-vPosition.xyz;
    }
    gl_Position = Projection*ModelView*vPosition;
}
