#pragma once
#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include <vector>
#include <array>

#include "../Rendering/Camera2D.h"

namespace Artifact
{
    enum class EMouseButton
    {
        Right = SDL_BUTTON_RIGHT,
        Left = SDL_BUTTON_LEFT,
        Middle = SDL_BUTTON_MIDDLE
    };

    class Mouse
    {
    private:
        const static int ButtonCount = 4;
        static std::array<bool, ButtonCount> s_CurrentlyPressed;
        static std::array<bool, ButtonCount> s_PreviouslyPressed;
        static glm::vec2 s_Position;
        static ComponentHandle<Camera2D> s_CurrentCamera;

        SDL_MouseMotionEvent m_CurrentMotion;
        std::vector<SDL_MouseButtonEvent> m_ButtonEvents;
        std::vector<SDL_MouseWheelEvent> m_ScrollEvents;

    public:
        Mouse& operator=(const Mouse& a_Other) = delete;

        void process(SDL_MouseButtonEvent a_ButtonEvent);
        void process(SDL_MouseMotionEvent a_MotionEvent);
        void process(SDL_MouseWheelEvent a_ScrollEvent);
        void update();
        void onCameraChange(ComponentHandle<Camera2D> a_NewCamera);
        static bool isButtonPressed(EMouseButton a_MouseButton);
        static bool isButtonDown(EMouseButton a_MouseButton);
        static glm::vec2 getScreenPosition();
        static glm::vec2 getWorldPosition();

    private:
        void updatePosition();
        void updateButtonStates();
    };
}
