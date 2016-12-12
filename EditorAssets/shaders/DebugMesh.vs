#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 inColor;
out vec4 outColor;
uniform mat4 transform;
uniform mat4 meshTransform;
void main(){
   gl_Position = transform * meshTransform *vec4(position, 1.0);
   outColor = inColor;
}
