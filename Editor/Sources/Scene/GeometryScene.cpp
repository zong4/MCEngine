#include "GeometryScene.hpp"

MCEditor::GeometryScene::GeometryScene()
{
    entt::entity cubes = MCEngine::EntityFactory::CreateCube(m_Registry, "Cubes");
}

void MCEditor::GeometryScene::Render(MCEngine::CameraComponent &camera) const
{
    ENGINE_PROFILE_FUNCTION();

    MCEngine::Scene::Render(camera);

    MCEngine::RendererCommand::DisableFaceCulling();
    auto &&shader = MCEngine::ShaderLibrary::GetInstance().GetShader("Geometry");
    shader->Bind();

    shader->SetUniformFloat("u_Magnitude", m_Magnitude);

    auto &&meshView = m_Registry.view<MCEngine::TransformComponent, MCEngine::MeshRendererComponent>();
    for (auto entity : meshView)
    {
        auto &&[transform, mesh] = meshView.get<MCEngine::TransformComponent, MCEngine::MeshRendererComponent>(entity);

        shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());
        shader->SetUniformMaterial("u_Material", mesh.GetMaterial());

        mesh.GetVAOPtr()->Render(MCEngine::RendererType::Triangles);
    }

    shader->Unbind();
    MCEngine::RendererCommand::EnableFaceCulling();
}
