#include "SceneSerializer.hpp"

YAML::Emitter &operator<<(YAML::Emitter &out, const glm::vec3 &v)
{
    out << YAML::Flow;
    out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
    return out;
}

YAML::Emitter &operator<<(YAML::Emitter &out, const glm::vec4 &v)
{
    out << YAML::Flow;
    out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
    return out;
}

void MCEngine::SceneSerializer::Serialize(const std::shared_ptr<Scene> &scene, const std::string &filepath)
{
    ENGINE_PROFILE_FUNCTION();

    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "Scene" << YAML::Value << scene->GetName();
    out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

    auto &registry = scene->GetRegistry();
    for (auto entityID : registry.view<entt::entity>())
    {
        if (entityID == entt::null)
            return;

        if (!registry.get<MCEngine::RelationshipComponent>(entityID).GetParent())
        {
            MCEngine::Entity entity = MCEngine::Entity(entityID, &registry);
            SerializeEntity(out, entity);
        }
    }

    out << YAML::EndSeq;
    out << YAML::EndMap;
    std::ofstream fout(filepath);
    fout << out.c_str();
}

bool MCEngine::SceneSerializer::Deserialize(std::shared_ptr<Scene> scene, const std::string &filepath)
{
    ENGINE_PROFILE_FUNCTION();

    std::ifstream stream(filepath);
    std::stringstream strStream;
    strStream << stream.rdbuf();

    YAML::Node data = YAML::Load(strStream.str());
    if (!data["Scene"])
        return false;

    std::string sceneName = data["Scene"].as<std::string>();
    scene->SetName(sceneName);
    LOG_ENGINE_INFO("Deserializing scene: " + sceneName);

    auto entities = data["Entities"];
    if (entities)
    {
        for (auto entity : entities)
        {
            DeserializeEntity(scene, entity);
        }
    }
    return true;
}

void MCEngine::SceneSerializer::SerializeEntity(YAML::Emitter &out, MCEngine::Entity entity)
{
    ENGINE_PROFILE_FUNCTION();

    out << YAML::BeginMap;
    out << YAML::Key << "Entity" << YAML::Value << static_cast<uint32_t>(entity.GetHandle());

    if (entity.HasComponent<MCEngine::TagComponent>())
    {
        out << YAML::Key << "TagComponent";
        out << YAML::BeginMap;

        auto &tagComponent = entity.GetComponent<MCEngine::TagComponent>();
        out << YAML::Key << "Tag" << YAML::Value << tagComponent.GetTag();

        out << YAML::EndMap;
    }

    if (entity.HasComponent<MCEngine::TransformComponent>())
    {
        out << YAML::Key << "TransformComponent";
        out << YAML::BeginMap;

        auto &transformComponent = entity.GetComponent<MCEngine::TransformComponent>();
        out << YAML::Key << "Position" << YAML::Value << transformComponent.GetPosition();
        out << YAML::Key << "Rotation" << YAML::Value << transformComponent.GetRotation();
        out << YAML::Key << "Scale" << YAML::Value << transformComponent.GetScale();

        out << YAML::EndMap;
    }

    if (entity.HasComponent<MCEngine::CameraComponent>())
    {
        out << YAML::Key << "CameraComponent";
        out << YAML::BeginMap;

        auto &cameraComponent = entity.GetComponent<MCEngine::CameraComponent>();
        out << YAML::Key << "Type" << YAML::Value << (int)cameraComponent.GetType();
        out << YAML::Key << "Width" << YAML::Value << cameraComponent.GetWidth();
        out << YAML::Key << "Height" << YAML::Value << cameraComponent.GetHeight();
        out << YAML::Key << "Scale" << YAML::Value << cameraComponent.GetScale();
        out << YAML::Key << "FOV" << YAML::Value << cameraComponent.GetFOV();
        out << YAML::Key << "NearClip" << YAML::Value << cameraComponent.GetNearClip();
        out << YAML::Key << "FarClip" << YAML::Value << cameraComponent.GetFarClip();

        out << YAML::EndMap;
    }

    if (entity.HasComponent<MCEngine::SpriteRendererComponent>())
    {
        out << YAML::Key << "SpriteRendererComponent";
        out << YAML::BeginMap;

        auto &spriteRendererComponent = entity.GetComponent<MCEngine::SpriteRendererComponent>();
        out << YAML::Key << "VAO" << YAML::Value
            << MCEngine::VAOLibrary::GetInstance().GetName(spriteRendererComponent.GetVAOPtr());
        out << YAML::Key << "Color" << YAML::Value << spriteRendererComponent.GetColor();
        out << YAML::Key << "Texture" << YAML::Value
            << MCEngine::TextureLibrary::GetInstance().GetName(spriteRendererComponent.GetTexturePtr());

        out << YAML::EndMap;
    }

    if (entity.HasComponent<MCEngine::MeshRendererComponent>())
    {
        out << YAML::Key << "MeshRendererComponent";
        out << YAML::BeginMap;

        auto &meshRendererComponent = entity.GetComponent<MCEngine::MeshRendererComponent>();
        out << YAML::Key << "VAO" << YAML::Value
            << MCEngine::VAOLibrary::GetInstance().GetName(meshRendererComponent.GetVAOPtr());

        out << YAML::Key << "Material";
        out << YAML::BeginMap;
        out << YAML::Key << "Color" << YAML::Value << meshRendererComponent.GetMaterial().GetColor();
        out << YAML::Key << "AmbientStrength" << YAML::Value
            << meshRendererComponent.GetMaterial().GetAmbientStrength();
        out << YAML::Key << "DiffuseStrength" << YAML::Value
            << meshRendererComponent.GetMaterial().GetDiffuseStrength();
        out << YAML::Key << "SpecularStrength" << YAML::Value
            << meshRendererComponent.GetMaterial().GetSpecularStrength();
        out << YAML::Key << "Shininess" << YAML::Value << meshRendererComponent.GetMaterial().GetShininess();
        out << YAML::EndMap;

        out << YAML::Key << "Shader" << YAML::Value
            << MCEngine::ShaderLibrary::GetInstance().GetName(meshRendererComponent.GetShaderPtr());

        out << YAML::EndMap;
    }

    if (entity.HasComponent<MCEngine::LightComponent>())
    {
        out << YAML::Key << "LightComponent";
        out << YAML::BeginMap;

        auto &lightComponent = entity.GetComponent<MCEngine::LightComponent>();
        out << YAML::Key << "Type" << YAML::Value << (int)lightComponent.GetType();
        out << YAML::Key << "Color" << YAML::Value << lightComponent.GetColor();
        out << YAML::Key << "Intensity" << YAML::Value << lightComponent.GetIntensity();
        out << YAML::Key << "Constant" << YAML::Value << lightComponent.GetConstant();
        out << YAML::Key << "Linear" << YAML::Value << lightComponent.GetLinear();
        out << YAML::Key << "Quadratic" << YAML::Value << lightComponent.GetQuadratic();
        out << YAML::Key << "InnerAngle" << YAML::Value << lightComponent.GetInnerAngle();
        out << YAML::Key << "OuterAngle" << YAML::Value << lightComponent.GetOuterAngle();

        out << YAML::EndMap;
    }

    if (entity.HasComponent<MCEngine::SkyboxComponent>())
    {
        out << YAML::Key << "SkyboxComponent";
        out << YAML::BeginMap;

        auto &skyboxComponent = entity.GetComponent<MCEngine::SkyboxComponent>();
        out << YAML::Key << "Texture" << YAML::Value
            << MCEngine::TextureLibrary::GetInstance().GetName(skyboxComponent.GetTextureCube());

        out << YAML::EndMap;
    }

    if (entity.HasComponent<MCEngine::RelationshipComponent>())
    {
        out << YAML::Key << "RelationshipComponent";
        out << YAML::BeginMap;

        out << YAML::Key << "Children" << YAML::Value << YAML::BeginSeq;
        auto &relationshipComponent = entity.GetComponent<MCEngine::RelationshipComponent>();
        for (auto child : relationshipComponent.GetChildren())
            SerializeEntity(out, child);
        out << YAML::EndSeq;

        out << YAML::EndMap;
    }

    out << YAML::EndMap;
}

MCEngine::Entity MCEngine::SceneSerializer::DeserializeEntity(std::shared_ptr<Scene> scene, YAML::Node &entity)
{
    uint32_t uuid = entity["Entity"].as<uint32_t>();

    std::string name;
    auto tagComponentData = entity["TagComponent"];
    if (tagComponentData)
    {
        name = tagComponentData["Tag"].as<std::string>();
    }
    Entity deserializedEntity = scene->AddEmptyEntity(name);
    LOG_ENGINE_TRACE("Deserialized entity with ID = " + std::to_string(uuid) + ", name = " + name);

    const auto &transformComponentData = entity["TransformComponent"];
    if (transformComponentData)
    {
        auto &transformComponent = deserializedEntity.GetComponent<TransformComponent>();
        transformComponent.SetPosition(transformComponentData["Position"].as<glm::vec3>());
        transformComponent.SetRotation(transformComponentData["Rotation"].as<glm::vec3>());
        transformComponent.SetScale(transformComponentData["Scale"].as<glm::vec3>());
    }

    const auto &cameraComponentData = entity["CameraComponent"];
    if (cameraComponentData)
    {
        auto &cameraComponent =
            deserializedEntity.AddComponent<CameraComponent>((CameraType)cameraComponentData["Type"].as<int>());
        cameraComponent.Resize(cameraComponentData["Width"].as<float>(), cameraComponentData["Height"].as<float>());
        cameraComponent.SetScale(cameraComponentData["Scale"].as<float>());
        cameraComponent.SetFOV(cameraComponentData["FOV"].as<float>());
        cameraComponent.SetNearClip(cameraComponentData["NearClip"].as<float>());
        cameraComponent.SetFarClip(cameraComponentData["FarClip"].as<float>());

        // todo
        scene->SetMainCamera(deserializedEntity);
    }

    const auto &spriteRendererComponentData = entity["SpriteRendererComponent"];
    if (spriteRendererComponentData)
    {
        auto &spriteRendererComponent = deserializedEntity.AddComponent<SpriteRendererComponent>(
            MCEngine::VAOLibrary::GetInstance().GetVAO(spriteRendererComponentData["VAO"].as<std::string>()));
        spriteRendererComponent.SetColor(spriteRendererComponentData["Color"].as<glm::vec4>());
        spriteRendererComponent.SetTexturePtr(MCEngine::TextureLibrary::GetInstance().GetTexture2D(
            spriteRendererComponentData["Texture"].as<std::string>()));
    }

    const auto &meshRendererComponentData = entity["MeshRendererComponent"];
    if (meshRendererComponentData)
    {
        auto &meshRendererComponent = deserializedEntity.AddComponent<MeshRendererComponent>(
            MCEngine::VAOLibrary::GetInstance().GetVAO(meshRendererComponentData["VAO"].as<std::string>()));
        const auto &materialData = meshRendererComponentData["Material"];
        if (materialData)
        {
            auto &material = meshRendererComponent.GetMaterial();
            material.SetColor(materialData["Color"].as<glm::vec4>());
            material.SetAmbientStrength(materialData["AmbientStrength"].as<float>());
            material.SetDiffuseStrength(materialData["DiffuseStrength"].as<float>());
            material.SetSpecularStrength(materialData["SpecularStrength"].as<float>());
            material.SetShininess(materialData["Shininess"].as<float>());
        }
        meshRendererComponent.SetShaderPtr(
            MCEngine::ShaderLibrary::GetInstance().GetShader(meshRendererComponentData["Shader"].as<std::string>()));
    }

    const auto &lightComponentData = entity["LightComponent"];
    if (lightComponentData)
    {
        auto &lightComponent =
            deserializedEntity.AddComponent<LightComponent>((LightType)lightComponentData["Type"].as<int>());
        lightComponent.SetColor(lightComponentData["Color"].as<glm::vec3>());
        lightComponent.SetIntensity(lightComponentData["Intensity"].as<float>());
        lightComponent.SetAttenuation(lightComponentData["Constant"].as<float>(),
                                      lightComponentData["Linear"].as<float>(),
                                      lightComponentData["Quadratic"].as<float>());
        lightComponent.SetAngles(lightComponentData["InnerAngle"].as<float>(),
                                 lightComponentData["OuterAngle"].as<float>());

        // todo
        if (lightComponent.GetType() == LightType::Directional)
            scene->SetMainLight(deserializedEntity);
    }

    const auto &skyboxComponentData = entity["SkyboxComponent"];
    if (skyboxComponentData)
    {
        auto &skyboxComponent = deserializedEntity.AddComponent<SkyboxComponent>(
            MCEngine::TextureLibrary::GetInstance().GetTextureCube(skyboxComponentData["Texture"].as<std::string>()));
    }

    const auto &relationshipComponentData = entity["RelationshipComponent"];
    if (relationshipComponentData)
    {
        for (auto child : relationshipComponentData["Children"])
        {
            Entity childEntity = DeserializeEntity(scene, child);
            if (childEntity)
            {
                deserializedEntity.GetComponent<RelationshipComponent>().AddChild(childEntity);
                childEntity.GetComponent<RelationshipComponent>().SetParent(deserializedEntity);
            }
        }
    }

    return deserializedEntity;
}