#include "Scene3D.hpp"

#include "Camera/OrthoCamera.hpp"
#include "ECS/Component/BasicComponent.hpp"
#include "ECS/Component/RendererComponent.hpp"

MCEngine::Scene3D::Scene3D()
{
    ENGINE_PROFILE_FUNCTION();

    m_MainCamera = m_Registry.create();
    m_Registry.emplace<TransformComponent>(m_MainCamera, TransformComponent(glm::vec3(0.0f, 0.0f, 0.0f)));
    m_Registry.emplace<CameraComponent>(m_MainCamera, CameraComponent(std::make_shared<OrthoCamera>(
                                                          glm::vec3(16.0f, 9.0f, 10.0f), glm::vec3(0.0f, 0.0f, 1.0f))));

    // Default light
    m_Light = m_Registry.create();
    m_Registry.emplace<TransformComponent>(m_Light, TransformComponent(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f)));
    m_Registry.emplace<LightComponent>(m_Light, LightComponent(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f));
}

void MCEngine::Scene3D::Render() const
{
    ENGINE_PROFILE_FUNCTION();

    auto &&cameraComp = m_Registry.get<CameraComponent>(m_MainCamera);
    auto &&cameraPtr = cameraComp.CameraPtr;

    // Render 3D
    {
        auto &&shader = ShaderLibrary::GetInstance().GetShader("BlinnPhong");
        shader->Bind();

        // Camera
        shader->SetUniformVec3("u_ViewPos", cameraPtr->GetPosition());
        shader->SetUniformMat4("u_View", cameraPtr->GetView());
        shader->SetUniformMat4("u_Projection", cameraPtr->GetProjection());

        // Light
        shader->SetUniformVec3("u_LightPos", m_Registry.get<TransformComponent>(m_Light).Position);
        shader->SetUniformVec4("u_LightColor", m_Registry.get<LightComponent>(m_Light).Color);

        auto meshView = m_Registry.view<TransformComponent, MeshRendererComponent>();
        for (auto entity : meshView)
        {
            auto &&[transform, mesh] = meshView.get<TransformComponent, MeshRendererComponent>(entity);

            // Transform component
            shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());

            // Mesh component
            shader->SetUniformVec4("u_ObjectColor", mesh.Color);

            RendererAPI::GetInstance().DrawQuad(mesh.VAOPtr);
        }

        shader->Unbind();
    }
}
