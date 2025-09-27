#version 330 core

// Layouts
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

// Uniforms
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

// Outputs
out vec3 o_FragPos;
out vec3 o_Normal;

void main()
{
    // Outputs
    o_FragPos = vec3(u_Model * vec4(aPos, 1.0));
    o_Normal = mat3(transpose(inverse(u_Model))) * aNormal;

    // Final vertex position
    gl_Position = u_Projection * u_View * vec4(o_FragPos, 1.0);
}
