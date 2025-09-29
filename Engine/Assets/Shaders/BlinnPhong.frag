#version 330 core

struct Material
{
    vec4 ObjectColor;
    float AmbientStrength;
    float DiffuseStrength;
    float SpecularStrength;
    float Shininess;
};

struct DirectionalLight
{
    vec3 Direction;
    vec3 Color;
};

struct PointLight
{
    vec3 Position;
    vec3 Color;

    float Constant;
    float Linear;
    float Quadratic;
};

struct SpotLight
{
    vec3 Position;
    vec3 Direction;
    vec3 Color;

    float Constant;
    float Linear;
    float Quadratic;

    float CutOff;
    float OuterCutOff;
};

// Output
out vec4 FragColor;

// Uniforms
uniform vec3 u_ViewPos;
uniform Material u_Material;
uniform DirectionalLight u_DirectionalLight;
uniform PointLight u_PointLight;
uniform SpotLight u_SpotLight;
uniform samplerCube u_Skybox;

// Inputs
in vec3 o_GlobalPosistion;
in vec3 o_Normal;

// Function prototypes
vec3 CalcDirectionalLight(DirectionalLight light, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 viewDir);
float CalDiffuseFactor(vec3 lightDir, vec3 normal);
float CalSpecularFactor(vec3 lightDir, vec3 viewDir, vec3 normal, float shininess);

// Main
void main()
{
    vec3 viewDir = normalize(u_ViewPos - o_GlobalPosistion);

    // Light
    vec3 resultLight = vec3(0.0);
    // resultLight += CalcDirectionalLight(u_DirectionalLight, viewDir);
    resultLight += CalcPointLight(u_PointLight, viewDir);
    resultLight += CalcSpotLight(u_SpotLight, viewDir);

    // Skybox
    vec3 resultSkybox = vec3(0.0);
    resultSkybox += texture(u_Skybox, reflect(-viewDir, normalize(o_Normal))).rgb * u_Material.SpecularStrength;
    // resultSkybox += texture(u_Skybox, refract(-viewDir, normalize(o_Normal), 1.00 / 1.52)).rgb * 0.5;

    FragColor = vec4(resultLight + resultSkybox, u_Material.ObjectColor.a);
}

vec3 CalcDirectionalLight(DirectionalLight light, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.Direction);
    float diff = CalDiffuseFactor(lightDir, o_Normal);
    float spec = CalSpecularFactor(lightDir, viewDir, o_Normal, u_Material.Shininess);

    return (u_Material.AmbientStrength * u_Material.ObjectColor.rgb +
            u_Material.DiffuseStrength * diff * u_Material.ObjectColor.rgb + u_Material.SpecularStrength * spec) *
           light.Color;
}

vec3 CalcPointLight(PointLight light, vec3 viewDir)
{
    vec3 lightDir = normalize(light.Position - o_GlobalPosistion);

    float diff = CalDiffuseFactor(lightDir, o_Normal);
    float spec = CalSpecularFactor(lightDir, viewDir, o_Normal, u_Material.Shininess);

    // Attenuation
    float distance = length(light.Position - o_GlobalPosistion);
    float attenuation = 1.0 / (light.Constant + light.Linear * distance + light.Quadratic * (distance * distance));

    return (u_Material.AmbientStrength * u_Material.ObjectColor.rgb +
            u_Material.DiffuseStrength * diff * u_Material.ObjectColor.rgb + u_Material.SpecularStrength * spec) *
           light.Color * attenuation;
}

vec3 CalcSpotLight(SpotLight light, vec3 viewDir)
{
    vec3 lightDir = normalize(light.Position - o_GlobalPosistion);

    float diff = CalDiffuseFactor(lightDir, o_Normal);
    float spec = CalSpecularFactor(lightDir, viewDir, o_Normal, u_Material.Shininess);

    // Attenuation
    float distance = length(light.Position - o_GlobalPosistion);
    float attenuation = 1.0 / (light.Constant + light.Linear * distance + light.Quadratic * (distance * distance));

    // Spotlight intensity
    float theta = dot(lightDir, normalize(-light.Direction));
    float epsilon = light.CutOff - light.OuterCutOff;
    float intensity = clamp((theta - light.OuterCutOff) / epsilon, 0.0, 1.0);

    return (u_Material.AmbientStrength * u_Material.ObjectColor.rgb +
            u_Material.DiffuseStrength * diff * u_Material.ObjectColor.rgb + u_Material.SpecularStrength * spec) *
           light.Color * attenuation * intensity;
}

float CalDiffuseFactor(vec3 lightDir, vec3 normal) { return max(dot(normal, lightDir), 0.0); }
float CalSpecularFactor(vec3 lightDir, vec3 viewDir, vec3 normal, float shininess)
{
    vec3 halfwayDir = normalize(lightDir + viewDir);
    return pow(max(dot(normal, halfwayDir), 0.0), shininess);
}