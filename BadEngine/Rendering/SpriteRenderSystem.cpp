#include "SpriteRenderSystem.h"
#include "SpriteRenderer.h"
#include "../Core/EntitySystem.h"

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
            break;
        default:
            break;
        }
    }

    void SpriteRenderSystem::renderSprites(EntitySystem& a_EntitySystem)
    {
        for(auto sprite : a_EntitySystem.getComponentsOfType<SpriteRenderer>())
        {
            //auto transform = *sprite->getComponent<Transform>();
            //auto destinationRectangle = Rectangle(transform.getPosition(), sprite->Width, sprite->Height);
            //m_SpriteBatch.draw(sprite->Texture, destinationRectangle, sprite->Color, sprite->UVRectangle, sprite->Depth);
        }
    }
}