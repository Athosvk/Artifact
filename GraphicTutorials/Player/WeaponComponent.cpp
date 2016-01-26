#include <BadEngine/Core/EntitySystem.h>

#include "WeaponComponent.h"

WeaponComponent::WeaponComponent(BadEngine::GameObject a_GameObject)
    : BadEngine::Component(a_GameObject)
{
    FireDelayTimer = addComponent<TimerComponent>();
}