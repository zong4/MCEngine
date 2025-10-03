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

static void SerializeEntity(YAML::Emitter &out, MCEngine::Entity entity)
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

void MCEngine::SceneSerializer::Serialize(const std::string &filepath)
{
    ENGINE_PROFILE_FUNCTION();

    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "Scene" << YAML::Value << "Untitled";
    out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

    auto &registry = m_Scene->GetRegistry();
    for (auto entityID : registry.view<entt::entity>())
    {
        if (entityID == entt::null)
            return;
        MCEngine::Entity entity = MCEngine::Entity(entityID, &registry);
        SerializeEntity(out, entity);
    }

    out << YAML::EndSeq;
    out << YAML::EndMap;

    std::ofstream fout(filepath);
    fout << out.c_str();
}

MCEngine::Entity MCEngine::SceneSerializer::DeserializeEntity(YAML::Node &entity)
{
    uint32_t uuid = entity["Entity"].as<uint32_t>();

    std::string name;
    auto tagComponentData = entity["TagComponent"];
    if (tagComponentData)
    {
        name = tagComponentData["Tag"].as<std::string>();
    }
    Entity deserializedEntity = m_Scene->AddEmptyEntity(name);
    LOG_ENGINE_TRACE("Deserialized entity with ID = " + std::to_string(uuid) + ", name = " + name);

    auto transformComponentData = entity["TransformComponent"];
    if (transformComponentData)
    {
        auto &transformComponent = deserializedEntity.GetComponent<TransformComponent>();
        transformComponent.SetPosition(transformComponentData["Position"].as<glm::vec3>());
        transformComponent.SetRotation(transformComponentData["Rotation"].as<glm::vec3>());
        transformComponent.SetScale(transformComponentData["Scale"].as<glm::vec3>());
    }

    auto cameraComponentData = entity["CameraComponent"];
    if (cameraComponentData)
    {
        auto &cameraComponent =
            deserializedEntity.AddComponent<CameraComponent>((CameraType)cameraComponentData["Type"].as<int>());
        cameraComponent.Resize(cameraComponentData["Width"].as<float>(), cameraComponentData["Height"].as<float>());
        cameraComponent.SetScale(cameraComponentData["Scale"].as<float>());
        cameraComponent.SetFOV(cameraComponentData["FOV"].as<float>());
        cameraComponent.SetNearClip(cameraComponentData["NearClip"].as<float>());
        cameraComponent.SetFarClip(cameraComponentData["FarClip"].as<float>());
    }

    auto spriteRendererComponentData = entity["SpriteRendererComponent"];
    if (spriteRendererComponentData)
    {
        auto &spriteRendererComponent = deserializedEntity.AddComponent<SpriteRendererComponent>(
            MCEngine::VAOLibrary::GetInstance().GetVAO(spriteRendererComponentData["VAO"].as<std::string>()));
        spriteRendererComponent.SetColor(spriteRendererComponentData["Color"].as<glm::vec4>());
        spriteRendererComponent.SetTexturePtr(MCEngine::TextureLibrary::GetInstance().GetTexture2D(
            spriteRendererComponentData["Texture"].as<std::string>()));
    }

    auto relationshipComponentData = entity["RelationshipComponent"];
    if (relationshipComponentData)
    {
        for (auto child : relationshipComponentData["Children"])
        {
            Entity childEntity = DeserializeEntity(child);
            if (childEntity)
            {
                deserializedEntity.GetComponent<RelationshipComponent>().AddChild(childEntity);
                childEntity.GetComponent<RelationshipComponent>().SetParent(deserializedEntity);
            }
        }
    }

    return deserializedEntity;
}

bool MCEngine::SceneSerializer::Deserialize(const std::string &filepath)
{
    ENGINE_PROFILE_FUNCTION();

    std::ifstream stream(filepath);
    std::stringstream strStream;
    strStream << stream.rdbuf();

    YAML::Node data = YAML::Load(strStream.str());
    if (!data["Scene"])
        return false;

    std::string sceneName = data["Scene"].as<std::string>();
    LOG_ENGINE_INFO("Deserializing scene: " + sceneName);

    auto entities = data["Entities"];
    if (entities)
    {
        for (auto entity : entities)
        {
            DeserializeEntity(entity);
        }
    }

    return true;
}