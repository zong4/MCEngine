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
    float ambientStrength = 0.1;
    vec4 ambient = ambientStrength * u_LightColor;

    // Diffuse
    vec3 norm = normalize(o_Normal);
    vec3 lightDir = normalize(u_LightPos - o_FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = vec4(diff * u_LightColor.rgb, 1.0);

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_ViewPos - o_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // 32 = shininess
    vec4 specular = vec4(specularStrength * spec * u_LightColor.rgb, 1.0);

    // Set fragment color
    vec4 result = (ambient + diffuse + specular) * u_ObjectColor;
    FragColor = result;
}
