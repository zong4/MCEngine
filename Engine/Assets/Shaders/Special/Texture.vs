#version 330 core

// Layouts
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;

// Uniforms
uniform mat4 u_Model;
layout(std140) uniform UniformBuffer0
{
    // Position
    mat4 u_View;
    mat4 u_Projection;

    // Light
    vec3 u_CameraPosition;
    vec3 u_DirectionalLightDirection;
    vec3 u_DirectionalLightColor;
};

// Outputs
out vec2 v_TexCoord;

// Main
void main()
{
    // Outputs
    v_TexCoord = aTexCoord;

    // Final vertex position
    gl_Position = u_Projection * u_View * u_Model * vec4(aPosition, 1.0);
}
