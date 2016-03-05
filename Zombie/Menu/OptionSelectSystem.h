#pragma once
#include <Artifact/Core/System.h>

class OptionComponent;

class OptionSelectSystem : public Artifact::System
{
private:
    OptionComponent* m_Selected;
    unsigned m_SelectedIndex = -1;

public:
    OptionSelectSystem(Artifact::EntitySystem& a_EntitySystem, Artifact::MessagingSystem& a_MessagingSystem);

    virtual void registerListeners() override;
private:
    void handleInput();
    void refreshSelectedOption();
    unsigned getOptionCount();
};
