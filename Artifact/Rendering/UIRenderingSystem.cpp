#include "UIRenderingSystem.h"
#include "RenderMessage.h"
#include "../Core/EntitySystem.h"
#include "TextComponent.h"
#include "../Transform.h"
#include "SpriteRenderer.h"

namespace Artifact
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
        m_SpriteBatch.begin(getCurrentCamera()->getProjectionMatrix());
        for(auto text : m_EntitySystem.getComponentsOfType<TextComponent>())
        {
            auto position = text->getComponent<Transform>()->getPosition();
            text->Font->draw(m_SpriteBatch, text->Text.c_str(), position, 
                glm::vec2(text->Scaling * static_cast<float>(1.0f / Camera2D::PixelsPerMeter)),
                text->Depth, text->Color, text->Justification);
        }
        m_SpriteBatch.end();
    }

    Camera2D* UIRenderingSystem::getCurrentCamera() const
    {
        return m_EntitySystem.getComponentsOfType<Camera2D>()[0];
    }
}
