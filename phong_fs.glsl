#version 150

out vec4 fColor;
//per-fragment interpolated values from vertex shader
in vec3 fN;
in vec3 fL;
in vec3 fE;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform mat4 ModelView;
uniform vec4 LightPosition;
uniform float Shininess;

void main() {
    vec3 N = normalize(fN);
    vec3 E = normalize(fE);
    vec3 L = normalize(fL);
    vec3 H = normalize(L+E);
    vec4 ambient = AmbientProduct;
    //Shininess = 0.4; //! sure
    float Kd = max(dot(L, N), 0.0);
    vec4 diffuse = Kd * DiffuseProduct;
    float Ks = pow(max(dot(N, H), 0.0), Shininess);
    //float Ks = pow(max(dot(R, E), 0.0), Shininess); //full Phong
    vec4 specular = Ks * SpecularProduct;

    //discard specular highlight if vertex !facing light
    if(dot(L, N) < 0.0) {
        specular = vec4(0.0, 0.0, 0.0, 1.0);
    }
    fColor = ambient + diffuse + specular;
    fColor.a = 1.0;
}
