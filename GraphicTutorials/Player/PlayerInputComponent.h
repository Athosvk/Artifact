#pragma once
#include <BadEngine/Core/Component.h>
#include <BadEngine/Input/Keycode.h>

class PlayerInputComponent : public BadEngine::Component
{
public:
    BadEngine::KeyCode FireKey;
    BadEngine::KeyCode MoveForwardKey;
    BadEngine::KeyCode MoveBackwardKey;
    BadEngine::KeyCode MoveLeftKey;
    BadEngine::KeyCode MoveRightKey;

public:
    PlayerInputComponent(BadEngine::GameObject a_GameObject);
};

