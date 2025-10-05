#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 u_Model;
uniform mat4 u_LightView;
uniform mat4 u_LightProjection;

void main() { gl_Position = u_LightProjection * u_LightView * u_Model * vec4(aPos, 1.0); }