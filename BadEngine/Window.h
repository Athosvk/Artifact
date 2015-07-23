#pragma once
#include <SDL2.0.3/SDL.h>
#include <GL/glew.h>
#include <string>

namespace BadEngine
{
    enum WindowFlag
    {
        FullScreen = 1,
        Invisible = 2,
        Borderless = 4,
        All = 7
    };

    class Window
    {
    private:
        Uint32 m_CurrentFlags;
        SDL_Window* m_SDLWindow;
        int m_Width;
        int m_Height;
        std::string m_Name;
        static Window* s_Current;

    public:
        Window(int a_ScreenWidth, int a_ScreenHeight, unsigned int a_Flags, std::string a_Name);
        ~Window();
        Window(const Window& obj);
        void update();
        int getWidth() const;
        int getHeight() const;
        void init();
        static const Window* getCurrent();
    };
}