#pragma once
#include <SDL/SDL.h>
#include <string>

#include "../Color.h"

namespace Artifact
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
        static int s_Width;
        static int s_Height;

        Uint32 m_CurrentFlags = SDL_WINDOW_OPENGL;
        SDL_Window* m_SDLWindow;
        SDL_GLContext m_GLContext;
        std::string m_Name;

    public:
        Window(int a_ScreenWidth, int a_ScreenHeight, unsigned int a_Flags, const std::string& a_Name);
        ~Window();

        Window& operator=(const Window& a_Other) = delete;

        static int getWidth();
        static int getHeight();
        void clear() const;
        void renderCurrentFrame() const;
        void setBackgroundColor(Color a_Color);
    private:
        void initialiseSDLWindow();
        void initialiseGL() const;
    };
}