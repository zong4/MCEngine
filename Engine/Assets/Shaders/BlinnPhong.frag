#version 330 core

// Output
out vec4 FragColor;

// Object Uniforms
uniform vec4 u_ObjectColor;
// Camera Uniforms
uniform vec3 u_ViewPos;
// Light Uniforms
uniform vec3 u_LightPos;
uniform vec4 u_LightColor;
// Shader Uniforms
uniform float u_AmbientStrength;
uniform float u_DiffuseStrength;
uniform float u_SpecularStrength;
uniform int u_Shininess;

// Inputs
in vec3 o_FragPos;
in vec3 o_Normal;

void main()
{
    // Ambient
    vec4 ambient = u_AmbientStrength * u_LightColor;

    // Diffuse
    vec3 norm = normalize(o_Normal);
    vec3 lightDir = normalize(u_LightPos - o_FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = vec4(u_DiffuseStrength * diff * u_LightColor);

    // Specular
    vec3 viewDir = normalize(u_ViewPos - o_FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), u_Shininess);
    vec4 specular = vec4(u_SpecularStrength * spec * u_LightColor);

    // Final color
    vec4 result = (ambient + diffuse + specular) * u_ObjectColor;
    FragColor = vec4(result.rgb, u_ObjectColor.a);
}
