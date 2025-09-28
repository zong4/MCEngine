#pragma once

#include "KeyEvent.hpp"

namespace MCEngine
{

class KeyCodeLibrary
{
public:
    static KeyCodeLibrary &GetInstance();

    bool IsKeyDown(int keyCode) const;
    int GetKeyAction(int keyCode) const;
    void SetKeyAction(int keyCode, int action) { m_KeyStateMap[keyCode] = action; }

private:
    std::unordered_map<int, int> m_KeyStateMap;

private:
    KeyCodeLibrary() = default;
    ~KeyCodeLibrary() = default;
};

} // namespace MCEngine