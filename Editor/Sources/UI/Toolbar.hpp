#pragma once

#include "pch.hpp"

namespace MCEditor
{

enum class EditorState
{
    Edit = 0,
    Play,
    Simulate
};

class Toolbar
{
public:
    Toolbar();
    ~Toolbar() = default;

public:
    void OnImGuiRender();

private:
    EditorState m_State = EditorState::Edit;
    std::shared_ptr<MCEngine::Texture2D> m_PlayButtonIcon;
    std::shared_ptr<MCEngine::Texture2D> m_StopButtonIcon;

private:
    void OnScenePlay();
    void OnSceneStop();
};

} // namespace MCEditor