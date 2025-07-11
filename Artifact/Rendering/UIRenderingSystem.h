#pragma once
#include "SpriteFont.h"
#include "../Core/System.h"
#include "SpriteBatch.h"

namespace Artifact
{	
	/// <summary>
	/// Renders the UI elements, such as text, to the screen, while disregarding the camera view matrix
	/// </summary>
	/// <seealso cref="System" />
	class UIRenderingSystem : public System
    {
    private:		
		/// <summary>The sprite batch to draw the UI elements to the screen</summary>
		SpriteBatch m_SpriteBatch;

    public:		
		/// <summary>Initializes a new instance of the <see cref="UIRenderingSystem"/> class.</summary>
		/// <param name="a_EntitySystem">The entity system to retrieve the components to operate on</param>
		/// <param name="a_MessagingSystem">The messaging system to use for receiving and sending messages</param>
		UIRenderingSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem);

		/// <summary>Allows for the system to register its listeners to the messagingsystem</summary>
        virtual void registerListeners() override;
    private:		
		/// <summary>Renders the UI.</summary>
		void renderUI();
		
		/// <summary>Gets the currently active camera</summary>
		/// <returns>The currently active camera</returns>
		ComponentHandle<Camera2D> getCurrentCamera() const;
    };
}
