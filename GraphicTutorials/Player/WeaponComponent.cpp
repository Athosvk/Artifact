#include "WeaponComponent.h"

WeaponComponent::WeaponComponent(BadEngine::GameObject a_GameObject)
    : BadEngine::Component(a_GameObject)
{
}

void WeaponComponent::reload()
{
    m_BulletsLeft = m_ClipSize;
}
