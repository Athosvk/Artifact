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
    }

    void SpriteRenderSystem::registerListeners()
    {
        m_MessagingSystem.registerListener<RenderMessage>([=](const Message* a_RenderMessage)
        {
            renderSprites(static_cast<const RenderMessage*>(a_RenderMessage));
        });
    }

    void SpriteRenderSystem::renderSprites(const RenderMessage* a_Message)
    {
        m_SpriteBatch.begin(a_Message->getViewMatrix());
        for(auto sprite : m_EntitySystem.getComponentsOfType<SpriteRenderer>())
        {
            auto transform = sprite->getComponent<Transform>();
            auto destinationRectangle = Rectangle(transform->getPosition(), sprite->Width, sprite->Height);
            m_SpriteBatch.draw(sprite->getTexture(), destinationRectangle, transform->getRotation(), destinationRectangle.getPosition(), 
                               sprite->Color, sprite->UVRectangle, sprite->Depth);
        }
        m_SpriteBatch.end();
    }
}