#pragma once
#include <SDL2.0.3/SDL.h>
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
        Uint32 m_CurrentFlags = SDL_WINDOW_OPENGL;
        SDL_Window* m_SDLWindow;
        SDL_GLContext m_GLContext;
        int m_Width;
        int m_Height;
        std::string m_Name;

    public:
        Window(int a_ScreenWidth, int a_ScreenHeight, unsigned int a_Flags, std::string a_Name);
        ~Window();

        Window& operator=(const Window& a_Other) = delete;

        int getWidth() const;
        int getHeight() const;
        void clear() const;
        void renderCurrentFrame() const;
        void initialiseSDLWindow();
        void initialiseGL() const;
    };
}