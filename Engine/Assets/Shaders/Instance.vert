#version 330 core

// Layouts
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;

// Uniforms
uniform mat4 u_Models[25];
layout(std140) uniform MainCamera
{
    vec3 u_Position;
    mat4 u_View;
    mat4 u_Projection;
};

// Outputs
out VS_OUT
{
    vec3 GlobalPosition;
    vec3 Normal;
    vec3 CameraPosition;
}
vs_out;

void main()
{
    // Outputs
    vs_out.GlobalPosition = vec3(u_Models[gl_InstanceID] * vec4(aPosition, 1.0));
    vs_out.Normal = normalize(mat3(transpose(inverse(u_Models[gl_InstanceID]))) * aNormal);
    vs_out.CameraPosition = u_Position;
    // vs_out.DirectionalLightDirection = u_DirectionalLightDirection;
    // vs_out.DirectionalLightColor = u_DirectionalLightColor;

    // Final vertex position
    gl_Position = u_Projection * u_View * vec4(vs_out.GlobalPosition, 1.0);
}
