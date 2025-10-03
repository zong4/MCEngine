#include "FullScene.hpp"

MCEditor::FullScene::FullScene() : MCEngine::Scene()
{
    ENGINE_PROFILE_FUNCTION();

    // 2D
    {
        Add2DObject("02BG",
                    MCEngine::TransformComponent(glm::vec3(-3.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(4.0f)),
                    MCEngine::SpriteRendererComponent(MCEngine::VAOLibrary::GetInstance().GetVAO("Square"),
                                                      glm::vec4(0.2f, 0.8f, 0.3f, 1.0f),
                                                      MCEngine::TextureLibrary::GetInstance().GetTexture2D("02BG")));
    }

    // 3D
    {
        MCEngine::Entity cubes = AddEmptyEntity("Cubes");
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                MCEngine::Entity cubeEntity =
                    Add3DObject("Cube", MCEngine::TransformComponent(glm::vec3(i * 1.0f, 0.0f, j * 1.0f)));

                cubeEntity.GetComponent<MCEngine::RelationshipComponent>().SetParent(cubes);
                cubes.GetComponent<MCEngine::RelationshipComponent>().AddChild(cubeEntity);
            }
        }

        Add3DObject("Cube", MCEngine::TransformComponent(glm::vec3(2.0f, 2.0f, 2.0f)));

        // Default light
        {
            m_Light =
                AddLight("DirectionalLight",
                         MCEngine::TransformComponent(glm::vec3(3.0f), glm::vec3(-50.0f, 0.0f, 0.0f), glm::vec3(0.5f)),
                         MCEngine::LightComponent(MCEngine::LightType::Directional, glm::vec3(1.0f, 0.0f, 0.0f)));
            m_Light.AddComponent<MCEngine::MeshRendererComponent>(MCEngine::VAOLibrary::GetInstance().GetVAO("Cube"));
        }
        {
            MCEngine::Entity light = AddLight("PointLight", MCEngine::TransformComponent(glm::vec3(0.0f, 0.8f, 0.0f)),
                                              MCEngine::LightComponent(MCEngine::LightType::Point));
            light.AddComponent<MCEngine::MeshRendererComponent>(MCEngine::VAOLibrary::GetInstance().GetVAO("Cube"));
        }
        {
            MCEngine::Entity light = AddLight("SpotLight", MCEngine::TransformComponent(glm::vec3(0.0f, 3.0f, 3.0f)),
                                              MCEngine::LightComponent(MCEngine::LightType::Spot));
            light.AddComponent<MCEngine::MeshRendererComponent>(MCEngine::VAOLibrary::GetInstance().GetVAO("Cube"));
        }

        // Skybox
        {
            MCEngine::Entity skybox = AddEmptyEntity("Skybox");
            skybox.AddComponent<MCEngine::SkyboxComponent>(
                MCEngine::TextureLibrary::GetInstance().GetTextureCube("Skybox"));
        }
    }
}

void MCEditor::FullScene::RenderShadowMapReally() const
{
    ENGINE_PROFILE_FUNCTION();

    auto &&shader = MCEngine::ShaderLibrary::GetInstance().GetShader("ShadowMap");
    shader->Bind();

    shader->SetUniformMat4("u_LightView", m_Light.GetComponent<MCEngine::TransformComponent>().GetViewMatrix());
    shader->SetUniformMat4("u_LightProjection", glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 20.0f));

    auto &&meshView = m_Registry.view<MCEngine::TransformComponent, MCEngine::MeshRendererComponent>();
    for (auto &&entity : meshView)
    {
        auto &&[transform, mesh] = meshView.get<MCEngine::TransformComponent, MCEngine::MeshRendererComponent>(entity);

        // transform
        shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());

        // mesh
        mesh.GetVAOPtr()->Render(MCEngine::RendererType::Triangles);
    }
    shader->Unbind();
}

void MCEditor::FullScene::RenderReally() const
{
    ENGINE_PROFILE_FUNCTION();

    // 3D
    {
        auto &&shader = MCEngine::ShaderLibrary::GetInstance().GetShader("BlinnPhong");
        shader->Bind();

        shader->SetUniformInt("u_ShadowMap", 0);
        m_ShadowMapPtr->GetTexturePtr()->Bind(0);

        shader->SetUniformMat4("u_LightView", m_Light.GetComponent<MCEngine::TransformComponent>().GetViewMatrix());
        shader->SetUniformMat4("u_LightProjection", glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 20.0f));

        // Light
        auto &&lightView = m_Registry.view<MCEngine::TransformComponent, MCEngine::LightComponent>();
        for (auto &&entity : lightView)
        {
            auto &&[transform, light] = lightView.get<MCEngine::TransformComponent, MCEngine::LightComponent>(entity);

            if (light.GetType() == MCEngine::LightType::Directional)
            {
                MCEngine::UniformBufferLibrary::GetInstance().UpdateUniformBuffer(
                    "UniformBuffer0",
                    {{glm::value_ptr(glm::normalize(-transform.GetPosition())), sizeof(glm::vec3),
                      sizeof(glm::mat4) + sizeof(glm::mat4) + sizeof(glm::vec4)},
                     {glm::value_ptr(light.GetColor() * light.GetIntensity()), sizeof(glm::vec3),
                      sizeof(glm::mat4) + sizeof(glm::mat4) + sizeof(glm::vec4) + sizeof(glm::vec4)}});
            }
            else if (light.GetType() == MCEngine::LightType::Point)
            {
                shader->SetUniformVec3("u_PointLight.Position", transform.GetPosition());
                shader->SetUniformVec3("u_PointLight.Color", light.GetColor() * light.GetIntensity());
                shader->SetUniformFloat("u_PointLight.Constant", light.GetConstant());
                shader->SetUniformFloat("u_PointLight.Linear", light.GetLinear());
                shader->SetUniformFloat("u_PointLight.Quadratic", light.GetQuadratic());
            }
            else if (light.GetType() == MCEngine::LightType::Spot)
            {
                shader->SetUniformVec3("u_SpotLight.Position", transform.GetPosition());
                shader->SetUniformVec3("u_SpotLight.Direction", -transform.GetUp());
                shader->SetUniformVec3("u_SpotLight.Color", light.GetColor() * light.GetIntensity());
                shader->SetUniformFloat("u_SpotLight.Constant", light.GetConstant());
                shader->SetUniformFloat("u_SpotLight.Linear", light.GetLinear());
                shader->SetUniformFloat("u_SpotLight.Quadratic", light.GetQuadratic());
                shader->SetUniformFloat("u_SpotLight.CutOff", glm::cos(glm::radians(light.GetCutOff())));
                shader->SetUniformFloat("u_SpotLight.OuterCutOff", glm::cos(glm::radians(light.GetOuterCutOff())));
            }
        }

        auto &&meshView = m_Registry.view<MCEngine::TransformComponent, MCEngine::MeshRendererComponent>();
        for (auto &&entity : meshView)
        {
            auto &&[transform, mesh] =
                meshView.get<MCEngine::TransformComponent, MCEngine::MeshRendererComponent>(entity);

            shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());
            mesh.GetMaterial().Bind(shader, "u_Material");

            mesh.GetVAOPtr()->Render();
        }

        shader->Unbind();
    }

    // Skybox
    {
        MCEngine::RendererCommand::DisableDepthTest();
        auto &&shader = MCEngine::ShaderLibrary::GetInstance().GetShader("Skybox");
        shader->Bind();

        auto &&skyboxView = m_Registry.view<MCEngine::SkyboxComponent>();
        for (auto &&entity : skyboxView)
        {
            auto &&skybox = skyboxView.get<MCEngine::SkyboxComponent>(entity);

            shader->SetUniformInt("u_Skybox", 0);
            skybox.GetTextureCubePtr()->Bind(0);

            MCEngine::VAOLibrary::GetInstance().GetVAO("Skybox")->Render();
        }

        shader->Unbind();
        MCEngine::RendererCommand::EnableDepthTest();
    }
}
