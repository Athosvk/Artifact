#include "Window.h"
#include "ErrorHandler.h"

namespace BadEngine
{
    Window* Window::s_Current = nullptr;

    Window::~Window()
    {

    }

    Window::Window(const Window& a_Other)
    {
        s_Current = this;
        m_Height = a_Other.m_Height;
        m_Width = a_Other.m_Width;
        m_Name = a_Other.m_Name;
        m_CurrentFlags = a_Other.m_CurrentFlags;
    }

    Window::Window(int a_Width, int a_Height, Uint32 a_Flags, std::string a_Name)
        : m_Width(a_Width),
        m_Height(a_Height),
        m_Name(a_Name),
        m_CurrentFlags(SDL_WINDOW_OPENGL)
    {
        s_Current = this;

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
    }

    void Window::init()
    {
        m_SDLWindow = SDL_CreateWindow(m_Name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width, m_Height, m_CurrentFlags);
        if(m_SDLWindow == nullptr)
        {
            throwFatalError("Could not initialize SDL window");
        }

        SDL_GLContext glContext = SDL_GL_CreateContext(m_SDLWindow);
        if(glContext == nullptr)
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

    void Window::update()
    {
        SDL_GL_SwapWindow(m_SDLWindow);
    }

    const Window* Window::getCurrent()
    {
        return s_Current;
    }
}