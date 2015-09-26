#include <GL/glew.h>

#include "Window.h"
#include "ErrorHandler.h"

namespace BadEngine
{
    Window::Window(int a_Width, int a_Height, Uint32 a_Flags, std::string a_Name)
        : m_CurrentFlags(SDL_WINDOW_OPENGL),
        m_Width(a_Width),
        m_Height(a_Height),
        m_Name(a_Name)
    {
        if((a_Flags & WindowFlag::FullScreen) == WindowFlag::FullScreen)
        {
            m_CurrentFlags |= SDL_WindowFlags::SDL_WINDOW_FULLSCREEN;
        }
        if((a_Flags & WindowFlag::Borderless) == WindowFlag::Borderless)
        {
            m_CurrentFlags |= SDL_WindowFlags::SDL_WINDOW_BORDERLESS;
        }
        if((a_Flags & WindowFlag::Invisible) == WindowFlag::Invisible)
        {
            m_CurrentFlags |= SDL_WindowFlags::SDL_WINDOW_HIDDEN;
        }

        initialiseSDLWindow();
    }

    Window::~Window()
    {
        SDL_GL_DeleteContext(m_GLContext);
        SDL_DestroyWindow(m_SDLWindow);
    }

    void Window::initialiseSDLWindow()
    {
        m_SDLWindow = SDL_CreateWindow(m_Name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width, m_Height, m_CurrentFlags);
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

    int Window::getWidth() const
    {
        return m_Width;
    }

    int Window::getHeight() const
    {
        return m_Height;
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
}