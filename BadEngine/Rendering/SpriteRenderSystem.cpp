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
    }

    void SpriteRenderSystem::renderSprites(const glm::mat4* a_ViewMatrix)
    {
        m_SpriteBatch.begin(a_ViewMatrix);
        for(auto sprite : m_EntitySystem.getComponentsOfType<SpriteRenderer>())
        {
            auto transform = *sprite->getComponent<Transform>();
            auto destinationRectangle = Rectangle(transform.getPosition(), sprite->Width, sprite->Height);
            m_SpriteBatch.draw(sprite->getTexture(), destinationRectangle, sprite->Color, sprite->UVRectangle, sprite->Depth);
        }
        m_SpriteBatch.end();
    }
}