#include <string>

#include <Artifact/Input/Keyboard.h>
#include <Artifact/Input/InputSystem.h>
#include <Artifact/Core/EntitySystem.h>

#include "OptionSelectSystem.h"
#include "OptionComponent.h"

OptionSelectSystem::OptionSelectSystem(Artifact::EntitySystem& a_EntitySystem, 
    Artifact::MessagingSystem& a_MessagingSystem)
    : System(a_EntitySystem, a_MessagingSystem)
{
}

void OptionSelectSystem::registerListeners()
{
    m_MessagingSystem.registerListener<Artifact::HandleInputMessage>([this](const Artifact::Message*)
    {
        handleInput();
    });
}

void OptionSelectSystem::handleInput()
{
    if(m_SelectedIndex == -1)
    {
        m_SelectedIndex = 0;
        refreshSelectedOption();
        m_Selected->OnSelect();
    }

    if(Artifact::Keyboard::isPressed(Artifact::KeyCode::Down))
    {
        m_Selected->OnDeselect();
        m_SelectedIndex = (m_SelectedIndex + 1) % getOptionCount();
        refreshSelectedOption();
        m_Selected->OnSelect();
    }
    else if(Artifact::Keyboard::isPressed(Artifact::KeyCode::Up))
    {
        m_Selected->OnDeselect();
        m_SelectedIndex = (m_SelectedIndex - 1) % getOptionCount();
        refreshSelectedOption();
        m_Selected->OnSelect();
    }
    if(Artifact::Keyboard::isPressed(Artifact::KeyCode::Return))
    {
        m_Selected->OnPress();
    }
}

void OptionSelectSystem::refreshSelectedOption()
{
    for(auto option : m_EntitySystem.getComponentsOfType<OptionComponent>())
    {
        if(option->Index == m_SelectedIndex)
        {
            m_Selected = option;
        }
    }
    if(m_Selected == nullptr)
    {
        throw std::logic_error("Invalid option index " + std::to_string(m_SelectedIndex));
    }
}

unsigned OptionSelectSystem::getOptionCount()
{
    return m_EntitySystem.getComponentsOfType<OptionComponent>().size();
}
