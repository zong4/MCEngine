#version 330 core

// Layouts
layout(location = 0) in vec3 aPos;

// Uniforms
uniform mat4 u_View;
uniform mat4 u_Projection;

// Outputs
out vec3 o_TexCoords;

// Main
void main()
{
    o_TexCoords = aPos;
    vec4 pos = u_Projection * mat4(mat3(u_View)) * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}
