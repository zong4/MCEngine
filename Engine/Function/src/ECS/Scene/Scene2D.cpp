#include "Scene2D.hpp"

#include "Camera/OrthoCamera.hpp"
#include "ECS/Component/BasicComponent.hpp"
#include "ECS/Component/RendererComponent.hpp"

MCEngine::Scene2D::Scene2D()
{
    ENGINE_PROFILE_FUNCTION();

    m_MainCamera = m_Registry.create();
    m_Registry.emplace<TransformComponent>(m_MainCamera, TransformComponent(glm::vec3(0.0f, 0.0f, 0.0f)));
    m_Registry.emplace<CameraComponent>(m_MainCamera, CameraComponent(std::make_shared<OrthoCamera>(
                                                          glm::vec3(16.0f, 9.0f, 10.0f), glm::vec3(0.0f, 0.0f, 1.0f))));
}

void MCEngine::Scene2D::Render() const
{
    ENGINE_PROFILE_FUNCTION();

    auto &&cameraComp = m_Registry.get<CameraComponent>(m_MainCamera);
    auto &&cameraPtr = cameraComp.CameraPtr;

    // Render 2D
    {
        auto &&shader = ShaderLibrary::GetInstance().GetShader("Texture");
        shader->Bind();

        shader->SetUniformMat4("u_View", cameraPtr->GetView());
        shader->SetUniformMat4("u_Projection", cameraPtr->GetProjection());

        auto &&spriteView = m_Registry.view<TransformComponent, SpriteRendererComponent>();
        for (auto entity : spriteView)
        {
            auto &&[transform, sprite] = spriteView.get<TransformComponent, SpriteRendererComponent>(entity);

            // Transform component
            shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());

            // Sprite component
            shader->SetUniformVec4("u_Color", sprite.Color);
            shader->SetUniformInt("u_Texture", 0);
            sprite.TexturePtr->Bind(0);

            RendererAPI::GetInstance().DrawQuad(sprite.VAOPtr);
        }

        shader->Unbind();
    }
}
