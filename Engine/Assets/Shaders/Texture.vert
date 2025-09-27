#version 330 core

// Layouts
layout(location = 0) in vec3 aPos;

// Uniforms
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

// Outputs

// Main
void main()
{
    // Final vertex position
    gl_Position = u_Projection * u_View * u_Model * vec4(aPos, 1.0);
}
