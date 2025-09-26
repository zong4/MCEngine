#include "KeyCodeLibrary.hpp"

MCEngine::KeyCodeLibrary &MCEngine::KeyCodeLibrary::GetInstance()
{
    ENGINE_PROFILE_FUNCTION();

    static KeyCodeLibrary instance;
    return instance;
}

int MCEngine::KeyCodeLibrary::GetKeyAction(int keyCode) const
{
    ENGINE_PROFILE_FUNCTION();

    auto it = m_KeyStates.find(keyCode);
    if (it != m_KeyStates.end())
    {
        return it->second;
    }

    // Default action if keyCode not found
    return 0;
}

void MCEngine::KeyCodeLibrary::SetKeyAction(int keyCode, int action)
{
    ENGINE_PROFILE_FUNCTION();

    m_KeyStates[keyCode] = action;
}