#version 330 core

// Layouts
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;

// Uniforms
layout(std140) uniform UniformBuffer0
{
    mat4 u_View;
    mat4 u_Projection;
    vec3 u_CameraPosition;
};

// Outputs
out VS_OUT
{
    vec3 Position;
    vec3 Normal;
    vec3 CameraPosition;
}
vs_out;

void main()
{
    vs_out.Position = aPosition;
    vs_out.Normal = aNormal;
    vs_out.CameraPosition = u_CameraPosition;
    gl_Position = u_Projection * u_View * vec4(vs_out.Position, 1.0);
}
