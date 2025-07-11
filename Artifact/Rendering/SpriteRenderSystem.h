#pragma once
#include "../Core/System.h"
#include "../Rendering/SpriteBatch.h"

namespace Artifact
{
    class RenderMessage;
	
	/// <summary>
	/// Renders the sprites each frame
	/// </summary>
	/// <seealso cref="System" />
	class SpriteRenderSystem : public System
    {
    private:		
		/// <summary>The sprite batch to draw the Sprite Renderers with</summary>
		SpriteBatch m_SpriteBatch;		
		/// <summary>The currently active camera, containing the view matrix to be used</summary>
		ComponentHandle<Camera2D> m_CurrentCamera = ComponentHandle<Camera2D>::NullHandle;

    public:		
		/// <summary>Initializes a new instance of the <see cref="SpriteRenderSystem"/> class.</summary>
		/// <param name="a_EntitySystem">The entity system to retrieve the components to operate on</param>
		/// <param name="a_MessagingSystem">The messaging system to use for receiving and sending messages</param>
		SpriteRenderSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem);
		
		/// <summary>Allows for the system to register its listeners to the messagingsystem</summary>
		virtual void registerListeners() override;

    private:		
		/// <summary>Renders the sprites to the currently active backbuffer (screen)</summary>
		void renderSprites();
    };
}
