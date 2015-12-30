#pragma once
#include <BadEngine/Core/Component.h>
#include <BadEngine/Input/Keycode.h>

class PlayerInputComponent : public BadEngine::Component
{
public:
    BadEngine::KeyCode MoveUpKey;
    BadEngine::KeyCode MoveDownKey;
    BadEngine::KeyCode MoveLeftKey;
    BadEngine::KeyCode MoveRightKey;
    BadEngine::KeyCode FireKey;

public:
    PlayerInputComponent(BadEngine::GameObject a_GameObject);
};

