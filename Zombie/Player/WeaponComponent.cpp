#include <Artifact/Core/EntitySystem.h>

#include "WeaponComponent.h"

WeaponComponent::WeaponComponent(Artifact::GameObject a_GameObject)
    : Artifact::Component(a_GameObject)
{
    FireDelayTimer = addComponent<TimerComponent>();
}