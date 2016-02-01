#pragma once
#include <BadEngine/Core/Component.h>
#include <BadEngine/Input/Keycode.h>

#include "WeaponComponent.h"

class PlayerInputComponent : public BadEngine::Component
{
public:
    float MovementSpeed = 0.9f;
    BadEngine::KeyCode MoveUpKey;
    BadEngine::KeyCode MoveDownKey;
    BadEngine::KeyCode MoveLeftKey;
    BadEngine::KeyCode MoveRightKey;
    BadEngine::KeyCode FireKey;
    WeaponComponent* Weapon;

public:
    PlayerInputComponent(BadEngine::GameObject a_GameObject);
};

