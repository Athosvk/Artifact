#pragma once
#include "../Core/System.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace Artifact
{	
	/// <summary>
	/// Sent when the systems should start handling user input
	/// </summary>
	/// <seealso cref="Message" />
	class HandleInputMessage : public Message
    {

    };
	
	/// <summary>
	/// The system taking care of the user input regarding keyboard, mouse and other possible input devices
	/// </summary>
	/// <seealso cref="System" />
	class InputSystem : public System
    {
    private:		
		/// <summary>The keyboard state to keep track of</summary>
		Keyboard m_Keyboard;		
		/// <summary>The mouse state to keep track of</summary>
		Mouse m_Mouse;

    public:		
		/// <summary>Initializes a new instance of the <see cref="InputSystem"/> class.</summary>
		/// <param name="a_EntitySystem">The entity system to operate on</param>
		/// <param name="a_MessagingSystem">The messaging system to send messages through</param>
		InputSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem);
		
		/// <summary>Allows the system for registering itself to the messages it wants to listen to	</summary>
		virtual void registerListeners() override;
    private:		
		/// <summary>Processes the incoming events and updates the state of the input devices accordingly</summary>
		/// <param name="a_Events">The events to process </param>
		void processEvents(const std::vector<SDL_Event>& a_Events);
		
		/// <summary>Updates the input state of the input devices</summary>
		void updateInput();
    };
}