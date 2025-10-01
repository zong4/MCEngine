#version 330 core

// Layouts
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;

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

// Shadow
uniform mat4 u_LightView;
uniform mat4 u_LightProjection;

// Outputs
out VS_OUT
{
    // Light
    vec3 GlobalPosition;
    vec3 Normal;
    vec3 CameraPosition;
    vec3 DirectionalLightDirection;
    vec3 DirectionalLightColor;

    // Shadow
    vec4 LightSpacePosition;
}
vs_out;

void main()
{
    // Light
    vs_out.GlobalPosition = vec3(u_Model * vec4(aPosition, 1.0));
    vs_out.Normal = normalize(mat3(transpose(inverse(u_Model))) * aNormal);
    vs_out.CameraPosition = u_CameraPosition;
    vs_out.DirectionalLightDirection = u_DirectionalLightDirection;
    vs_out.DirectionalLightColor = u_DirectionalLightColor;

    // Shadow
    vs_out.LightSpacePosition = u_LightProjection * u_LightView * vec4(vs_out.GlobalPosition, 1.0);

    // Final vertex position
    gl_Position = u_Projection * u_View * vec4(vs_out.GlobalPosition, 1.0);
}
