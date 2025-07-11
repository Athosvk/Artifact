#pragma once
#include <SDL/SDL.h>
#include <vector>

#include "Keycode.h"

namespace Artifact
{
    class Keyboard
    {
    private:		
		/// <summary>The received keyboard events to process later on</summary>
		std::vector<SDL_KeyboardEvent> m_KeyboardEvents;

		/// <summary>The array of keys containing whether it was pressed during the previous frame</summary>
		static bool m_PreviouslyPressed[SDL_NUM_SCANCODES];
		/// <summary>The array of keys containing whether it was pressed during the current frame</summary>
        static bool m_CurrentlyPressed[SDL_NUM_SCANCODES];

    public:		
		/// <summary>Initializes a new instance of the <see cref="Keyboard"/> class.</summary>
		Keyboard();
		
		/// <summary>Processes the specified keyboard event.</summary>
		/// <param name="a_KeyboardEvent">The keyboard event to process</param>
		void process(const SDL_KeyboardEvent& a_KeyboardEvent);		

		/// <summary>Updates the state of the keyboard based on the submitted keyboard events</summary>
		void update();
		
		/// <summary>Determines whether the specified key was not pressed in the previous frame and is pressed in the current</summary>
		/// <param name="a_KeyCode">The keycode of the key to check</param>
		/// <returns>Whether the given key is being pressed</returns>
		static bool isPressed(const KeyCode& a_KeyCode);
		
		/// <summary>Determines whether the specified key is currently being pressed, regardless of whether it was pressed in the previous frame</summary>
		/// <param name="a_KeyCode">The keycode of the key to check</param>
		/// <returns>Whether the given key is being held down</returns>
		static bool isDown(const KeyCode& a_KeyCode);
		
		/// <summary>Determines whether the specified key was pressed in the previous frame and is no longer pressed in the current frame</summary>
		/// <param name="a_KeyCode">The keycode of the key to check for</param>
		/// <returns>Whether the given was released during the previous frame</returns>
		static bool isReleased(const KeyCode& a_KeyCode);
		
		/// <summary>Clears the state of the input</summary>
		static void clear();

    private:		
		/// <summary>Clears the state of the keys in the previous frame</summary>
		static void clearPrevious();
		
		/// <summary>Clears the state of the keys in the current frame</summary>
		static void clearCurrent();
		
		/// <summary>Updates the state of the keys based on the submitted keyboard events</summary>
		void updateKeystate();
    };
}