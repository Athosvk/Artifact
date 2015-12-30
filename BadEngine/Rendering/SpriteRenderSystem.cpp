#include "SpriteRenderSystem.h"
#include "SpriteRenderer.h"
#include "../Core/EntitySystem.h"
#include "../Transform.h"
#include "RenderMessage.h"

namespace BadEngine
{
    SpriteRenderSystem::SpriteRenderSystem(EntitySystem& a_EntitySystem)
        : System(a_EntitySystem)
    {
    }

    void SpriteRenderSystem::sendMessage(const Message* a_Message)
    {
        switch(a_Message->getType())
        {
        case EMessageType::Render: 
            renderSprites(static_cast<const RenderMessage*>(a_Message)->getViewMatrix());
            break;
        default:
            break;
        }
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