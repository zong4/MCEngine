#version 330 core

// Output
out vec4 FragColor;

// Uniforms
uniform vec4 u_ObjectColor;
uniform vec3 u_ViewPos;
uniform vec3 u_LightPos;
uniform vec4 u_LightColor;

// Inputs
in vec3 o_FragPos;
in vec3 o_Normal;

void main()
{
    // Ambient
    float ambientStrength = 0.3;
    vec4 ambient = ambientStrength * u_LightColor;

    // Diffuse
    float diffuseStrength = 1.0;
    vec3 norm = normalize(o_Normal);
    vec3 lightDir = normalize(u_LightPos - o_FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = vec4(diffuseStrength * diff * u_LightColor);

    // Specular
    float specularStrength = 1.0;
    vec3 viewDir = normalize(u_ViewPos - o_FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32); // shininess = 32
    vec4 specular = vec4(specularStrength * spec * u_LightColor);

    // Final color
    vec4 result = (ambient + diffuse + specular) * u_ObjectColor;
    FragColor = vec4(result.rgb, u_ObjectColor.a);
}
