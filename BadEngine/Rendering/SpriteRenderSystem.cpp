#include "SpriteRenderSystem.h"
#include "SpriteRenderer.h"
#include "../Core/EntitySystem.h"
#include "../Transform.h"
#include "RenderMessage.h"

namespace BadEngine
{
    SpriteRenderSystem::SpriteRenderSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem)
        : System(a_EntitySystem, a_MessagingSystem)
    {
        auto cameras = m_EntitySystem.getComponentsOfType<Camera2D>();
        if(!cameras.empty())
        {
            m_CurrentCamera = cameras[0];
        }
    }

    void SpriteRenderSystem::registerListeners()
    {
        m_MessagingSystem.registerListener<RenderMessage>([this](const Message* a_RenderMessage)
        {
            renderSprites(static_cast<const RenderMessage*>(a_RenderMessage));
        });
        m_MessagingSystem.registerListener<OnCameraChangedMessage>([this](const Message* a_Message)
        {
            m_CurrentCamera = static_cast<const OnCameraChangedMessage*>(a_Message)->getNewCamera();
        });
    }

    void SpriteRenderSystem::renderSprites(const RenderMessage* a_Message)
    {
        m_SpriteBatch.begin(&m_CurrentCamera->getViewProjection());
        for(auto sprite : m_EntitySystem.getComponentsOfType<SpriteRenderer>())
        {
            auto transform = sprite->getComponent<Transform>();
            auto dimensions = glm::vec2(sprite->Width, sprite->Height);
            auto destinationRectangle = Rectangle(transform->getPosition() - dimensions * 0.5f, dimensions.x, dimensions.y);

            if(transform->getRotation() > 0.0f || transform->getRotation() < 0.0f)
            {
                m_SpriteBatch.draw(sprite->getTexture(), destinationRectangle, transform->getRotation(), destinationRectangle.getPosition(),
                                   sprite->Color, sprite->UVRectangle, sprite->Depth);
            }
            else
            {
                m_SpriteBatch.draw(sprite->getTexture(), destinationRectangle, sprite->Color, sprite->UVRectangle, sprite->Depth);
            }
        }
        m_SpriteBatch.end();
    }
}