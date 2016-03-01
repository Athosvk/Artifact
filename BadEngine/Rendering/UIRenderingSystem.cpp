#include "UIRenderingSystem.h"
#include "RenderMessage.h"
#include "../Core/EntitySystem.h"
#include "TextComponent.h"
#include "../Transform.h"

namespace BadEngine
{
    UIRenderingSystem::UIRenderingSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem)
        : System(a_EntitySystem, a_MessagingSystem)
    {
    }

    void UIRenderingSystem::registerListeners()
    {
        m_MessagingSystem.registerListener<RenderMessage>([this](const Message*)
        {
            renderUI();
        });
    }

    void UIRenderingSystem::renderUI()
    {
        const auto ViewMatrix = glm::mat4(1.0f);
        m_SpriteBatch.begin(&ViewMatrix);
        for(auto text : m_EntitySystem.getComponentsOfType<TextComponent>())
        {
            auto position = text->getComponent<Transform>()->getPosition();
            text->Font->draw(m_SpriteBatch, text->Text.c_str(), position, glm::vec2(text->Scaling), 
                text->Depth, text->Color, text->Justification);
        }
        m_SpriteBatch.end();
    }
}
