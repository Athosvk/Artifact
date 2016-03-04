#pragma once
#include <Artifact/Delegate.h>
#include <Artifact/Core/Component.h>

class OptionComponent : public Artifact::Component
{
public:
    Artifact::Delegate<void()> OnSelect;
    Artifact::Delegate<void()> OnPress;
    Artifact::Delegate<void()> OnDeselect;
    unsigned Index = 0;

    OptionComponent(Artifact::GameObject a_GameObject);
};

