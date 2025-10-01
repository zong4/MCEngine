#include "SampleScene.hpp"

MCEditor::SampleScene::SampleScene()
{
    entt::entity m_Light = MCEngine::EntityFactory::CreateDirectionalLight(m_Registry, "DirectionalLight");

    MCEngine::EntityFactory::CreateCube(m_Registry, "Cube");
}

void MCEditor::SampleScene::RenderShadowMapReally() const {}

void MCEditor::SampleScene::RenderReally(MCEngine::CameraComponent &camera) const {}
