#pragma once

#include "KeyEvent.hpp"

namespace MCEngine
{

class KeyCodeLibrary
{
public:
    static KeyCodeLibrary &GetInstance();

    int GetKeyAction(int keyCode) const;
    void SetKeyAction(int keyCode, int action);

private:
    std::unordered_map<int, int> m_KeyStates;

private:
    KeyCodeLibrary() = default;
    ~KeyCodeLibrary() = default;
};

} // namespace MCEngine