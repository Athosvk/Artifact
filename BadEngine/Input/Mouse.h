#pragma once
#include <glm/glm.hpp>
#include <SDL2.0.3/SDL.h>
#include <vector>
#include <array>

#include "../Rendering/Camera2D.h"

namespace BadEngine
{
    enum class MouseButton
    {
        Right = SDL_BUTTON_RIGHT,
        Left = SDL_BUTTON_LEFT,
        Middle = SDL_BUTTON_MIDDLE
    };

    class Mouse
    {
    private:
        const static int NumberOfButtons = 3;
        static std::array<bool, NumberOfButtons> s_CurrentlyPressed;
        static std::array<bool, NumberOfButtons> s_PreviouslyPressed;

        glm::vec2 m_Position;
        glm::vec2 m_PreviousPosition;
        SDL_MouseMotionEvent m_CurrentMotion;
        std::vector<SDL_MouseButtonEvent> m_ButtonEvents;
        std::vector<SDL_MouseWheelEvent> m_ScrollEvents;
        const BadEngine::Camera2D& m_Camera;

    public:
        Mouse(const BadEngine::Camera2D& a_Camera);
        ~Mouse();
        Mouse& operator=(const Mouse& a_Other) = delete;

        glm::vec2 getScreenPosition() const;
        glm::vec2 getWorldPosition() const;
        void setPosition(glm::vec2 a_Position);
        void simulatePress();
        void process(SDL_MouseButtonEvent a_ButtonEvent);
        void process(SDL_MouseMotionEvent a_MotionEvent);
        void process(SDL_MouseWheelEvent a_ScrollEvent);
        void update();
        static bool isButtonPressed(MouseButton a_MouseButton);
        static bool isButtonDown(MouseButton a_MouseButton);

    private:
        void updatePosition();
        void updateButtonStates();
    };
}
