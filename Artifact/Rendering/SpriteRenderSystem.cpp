#include "SpriteRenderSystem.h"
#include "SpriteRenderer.h"
#include "../Core/EntitySystem.h"
#include "../Transform.h"
#include "RenderMessage.h"

namespace Artifact
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
        m_MessagingSystem.registerListener<RenderMessage>([this](const Message*)
        {
            renderSprites();
        });
        m_MessagingSystem.registerListener<OnCameraChangedMessage>([this](const Message* a_Message)
        {
            m_CurrentCamera = static_cast<const OnCameraChangedMessage*>(a_Message)->getNewCamera();
        });
    }

    void SpriteRenderSystem::renderSprites()
    {
        m_SpriteBatch.begin(m_CurrentCamera->getViewProjection(), ESpriteSortMode::BackToFront);
        for(auto sprite : m_EntitySystem.getComponentsOfType<SpriteRenderer>())
        {
			if(sprite->isEnabled())
			{
				auto transform = sprite->getComponent<Transform>();
				auto dimensions = glm::vec2(sprite->Width, sprite->Height);
				auto destinationRectangle = Rectangle(transform->getPosition() - dimensions * sprite->Pivot,
					dimensions.x, dimensions.y);

				if(transform->getRotation() > 0.0f || transform->getRotation() < 0.0f)
				{
					m_SpriteBatch.draw(sprite->getTexture(), destinationRectangle, transform->getRotation(),
						destinationRectangle.getPosition(), sprite->Color, sprite->UVRectangle, sprite->Depth);
				}
				else
				{
					m_SpriteBatch.draw(sprite->getTexture(), destinationRectangle, sprite->Color, sprite->UVRectangle,
						sprite->Depth);
				}
			}
        }
        m_SpriteBatch.end();
    }
}