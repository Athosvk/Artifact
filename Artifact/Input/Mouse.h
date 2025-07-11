#pragma once
#include <SDL/SDL.h>
#include <vector>
#include <array>

#include "../Rendering/Camera2D.h"

namespace Artifact
{	
	/// <summary>
	/// THe possible mouse buttons of which you can check whether they are being pressed
	/// </summary>
	enum class EMouseButton
    {		
		/// <summary>The right mouse button, button 2</summary>
		Right = SDL_BUTTON_RIGHT,		
		/// <summary>The left mouse button, button 1</summary>
		Left = SDL_BUTTON_LEFT,		
		/// <summary>The middle mouse button, the scroll wheel/button 3</summary>
		Middle = SDL_BUTTON_MIDDLE
    };
	
	/// <summary>
	/// Representation of a mouse as input device, to query for button presses
	/// </summary>
	class Mouse
    {
    private:		
		/// <summary>The amount of buttons that can be queried</summary>
		const static int ButtonCount = 4;
		/// <summary>The state of the mouse buttons during the current frame </summary>
		static std::array<bool, ButtonCount> s_CurrentlyPressed;
		/// <summary>The state of the mouse buttons during the previous frame </summary>
		static std::array<bool, ButtonCount> s_PreviouslyPressed;
		/// <summary>The relative position of the mouse</summary>
        static glm::vec2 s_Position;
		/// <summary>The handle to the active camera</summary>
        static ComponentHandle<Camera2D> s_CurrentCamera;		
		/// <summary>The last received motion event of the mouse</summary>
		SDL_MouseMotionEvent m_CurrentMotion;		
		/// <summary>The button events received during this frame</summary>
		std::vector<SDL_MouseButtonEvent> m_ButtonEvents;		
		/// <summary>The scroll events received during this frame</summary>
		std::vector<SDL_MouseWheelEvent> m_ScrollEvents;

    public:		
		/// <summary>Assigns the given value to this isntance</summary>
		/// <param name="a_Other">The instance to assign to this instance</param>
		/// <returns>This instance</returns>
		Mouse& operator=(const Mouse& a_Other) = delete;
		
		/// <summary>Processes the specified button event</summary>
		/// <param name="a_ButtonEvent">The button event to process</param>
		void process(SDL_MouseButtonEvent a_ButtonEvent);
		
		/// <summary>Processes the specified motion event.</summary>
		/// <param name="a_MotionEvent">The motion event to process</param>
		void process(SDL_MouseMotionEvent a_MotionEvent);
		
		/// <summary>Processes the specified scroll event.</summary>
		/// <param name="a_ScrollEvent">The scroll event to process</param>
		void process(SDL_MouseWheelEvent a_ScrollEvent) const;
		
		/// <summary>Process the events so that they are translated to state changes</summary>
		void update();
		
		/// <summary>Called when the camera has changed</summary>
		/// <param name="a_NewCamera">The new active camera</param>
		void onCameraChange(ComponentHandle<Camera2D> a_NewCamera) const;
		
		/// <summary>
		/// Determines whether the specified mousebutton is being pressed during this frame and was not during the previous
		/// </summary>
		/// <param name="a_MouseButton">The button to check</param>
		/// <returns>Whether the specified button was pressed</returns>
		static bool isButtonPressed(EMouseButton a_MouseButton);
		
		/// <summary>
		/// Determines whether the specified mousebutton is being held down, regardless of whether it was during the previous frame
		/// </summary>
		/// <param name="a_MouseButton">The button to check</param>
		/// <returns>Whether the specfiied button is being held down</returns>
		static bool isButtonDown(EMouseButton a_MouseButton);
		
		/// <summary>Gets the screen position of the cursor</summary>
		/// <returns>The cursor's position in screenspace</returns>
		static glm::vec2 getScreenPosition();
		
		/// <summary>Gets the world position of the cursor</summary>
		/// <returns>The cursor's position in worldspace</returns>
		static glm::vec2 getWorldPosition();

    private:		
		/// <summary>Updates the position of the mouse based on the motion events</summary>
		void updatePosition() const;
		
		/// <summary>Updates the button states based on the button events</summary>
		void updateButtonStates();
    };
}
