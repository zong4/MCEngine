#include "KeyCodeLibrary.hpp"

MCEngine::KeyCodeLibrary &MCEngine::KeyCodeLibrary::GetInstanceRef()
{
    static KeyCodeLibrary instance;
    return instance;
}

bool MCEngine::KeyCodeLibrary::IsKeyDown(int keyCode) const
{
    ENGINE_PROFILE_FUNCTION();

    auto it = m_KeyStateMap.find(keyCode);
    if (it != m_KeyStateMap.end())
    {
        return it->second == 1 || it->second == 2;
    }
    return false;
}

int MCEngine::KeyCodeLibrary::GetKeyAction(int keyCode) const
{
    ENGINE_PROFILE_FUNCTION();

    auto it = m_KeyStateMap.find(keyCode);
    if (it != m_KeyStateMap.end())
    {
        return it->second;
    }
    return 0;
}