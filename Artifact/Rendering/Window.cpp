#include <GL/glew.h>

#include "Window.h"
#include "..\ErrorHandler.h"
#include "..\GL/GL.h"

namespace Artifact
{
    int Window::s_Width;
    int Window::s_Height;

    Window::Window(int a_Width, int a_Height, unsigned int a_Flags, const std::string& a_Name) :
        m_Name(a_Name)
    {
        if((a_Flags & EWindowFlag::FullScreen) == EWindowFlag::FullScreen)
        {
            m_CurrentFlags |= SDL_WindowFlags::SDL_WINDOW_FULLSCREEN;
        }
        if((a_Flags & EWindowFlag::Borderless) == EWindowFlag::Borderless)
        {
            m_CurrentFlags |= SDL_WindowFlags::SDL_WINDOW_BORDERLESS;
        }
        if((a_Flags & EWindowFlag::Invisible) == EWindowFlag::Invisible)
        {
            m_CurrentFlags |= SDL_WindowFlags::SDL_WINDOW_HIDDEN;
        }
        s_Width = a_Width;
        s_Height = a_Height;

        initialiseSDLWindow();
        initialiseGL();
    }

	Window::~Window()
    {
        SDL_GL_DeleteContext(m_GLContext);
        SDL_DestroyWindow(m_SDLWindow);
    }

    void Window::initialiseSDLWindow()
    {
        SDL_Init(SDL_INIT_EVERYTHING);

        m_SDLWindow = SDL_CreateWindow(m_Name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, s_Width, s_Height, m_CurrentFlags);
        if(m_SDLWindow == nullptr)
        {
            throwFatalError("Could not initialize SDL window");
        }

        m_GLContext = SDL_GL_CreateContext(m_SDLWindow);
        if(m_GLContext == nullptr)
        {
            throwFatalError("SDL_GL context could not be created");
        }
    }

    int Window::getWidth()
    {
        return s_Width;
    }

    int Window::getHeight()
    {
        return s_Height;
    }

    void Window::clear() const
    {
        glClearDepth(1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::renderCurrentFrame() const
    {
        SDL_GL_SwapWindow(m_SDLWindow);
    }

    void Window::setBackgroundColor(Color a_Color)
    {
        glClearColor(a_Color.R, a_Color.G, a_Color.B, a_Color.A);
    }

    void Window::initialiseGL() const
    {
        auto initCode = glewInit();
        if(initCode != GLEW_OK)
        {
            throwFatalError("Could not init glew, error: " + GL::getErrorString(initCode));
        }

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetSwapInterval(1);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
}