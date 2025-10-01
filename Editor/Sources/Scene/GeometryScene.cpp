#include "GeometryScene.hpp"

MCEditor::GeometryScene::GeometryScene()
{
    entt::entity cubes =
        MCEngine::EntityFactory::CreateCube(m_Registry, "Cubes", MCEngine::TransformComponent(),
                                            MCEngine::ShaderLibrary::GetInstance().GetShader("Geometry"));
}

void MCEditor::GeometryScene::RenderReally(MCEngine::CameraComponent &camera) const
{
    ENGINE_PROFILE_FUNCTION();

    MCEngine::RendererCommand::DisableFaceCulling();
    auto &&shader = MCEngine::ShaderLibrary::GetInstance().GetShader("Geometry");
    shader->Bind();

    shader->SetUniformFloat("u_Magnitude", m_Magnitude);

    auto &&meshView = m_Registry.view<MCEngine::TransformComponent, MCEngine::MeshRendererComponent>();
    for (auto &&entity : meshView)
    {
        auto &&[transform, mesh] = meshView.get<MCEngine::TransformComponent, MCEngine::MeshRendererComponent>(entity);

        shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());
        mesh.GetMaterial().Bind(shader, "u_Material");

        mesh.GetVAOPtr()->Render(MCEngine::RendererType::Triangles);
    }

    shader->Unbind();
    MCEngine::RendererCommand::EnableFaceCulling();
}
