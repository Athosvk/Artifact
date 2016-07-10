#pragma once
#include <SDL/SDL.h>
#include <string>

#include "../Color.h"

namespace Artifact
{	
	/// <summary>
	/// 
	/// </summary>
	enum EWindowFlag
    {		
		/// <summary>No windowflags</summary>
		None = 0,		
		/// <summary>Render in full screen mode</summary>
		FullScreen = 1,		
		/// <summary>Invisible window</summary>
		Invisible = 2,		
		/// <summary>Bordereless window</summary>
		Borderless = 4,		
		/// <summary>Enable all window flags</summary>
		All = 7
    };

    class Window
    {
    private:
		/// <summary>The width of the window</summary>
		static int s_Width;
		/// <summary>The height of the window</summary>
		static int s_Height;
		
		/// <summary>The SDL flags that are currently active</summary>
		Uint32 m_CurrentFlags = SDL_WINDOW_OPENGL;		
		/// <summary>The SDL window</summary>
		SDL_Window* m_SDLWindow;		
		/// <summary>The active OpenGL context</summary>
		SDL_GLContext m_GLContext;		
		/// <summary>The name of the window, displayed at the top</summary>
		std::string m_Name;
		
    public:		
		/// <summary>Initializes a new instance of the <see cref="Window"/> class.</summary>
		/// <param name="a_ScreenWidth">Width of the a_ screen.</param>
		/// <param name="a_ScreenHeight">Height of the a_ screen.</param>
		/// <param name="a_Flags">The a_ flags.</param>
		/// <param name="a_Name">Name of the a_.</param>
		Window(int a_ScreenWidth, int a_ScreenHeight, unsigned int a_Flags, const std::string& a_Name);

		/// <summary>Finalizes an instance of the <see cref="Window"/> class.</summary>
		~Window();
		
		/// <summary>Assigns a window instance</summary>
		/// <param name="a_Other">The window instance to assign to this</param>
		/// <returns>The new window, created from assignment</returns>
		Window& operator=(const Window& a_Other) = delete;
		
		/// <summary>Gets the width</summary>
		/// <returns>The window's width</returns>
		static int getWidth();
		
		/// <summary>Gets the height</summary>
		/// <returns>The window's height</returns>
		static int getHeight();
		
		/// <summary>Clears the window, using the background color</summary>
		void clear() const;
		
		/// <summary>Swaps the front and backbuffer, to display the new frame</summary>
		void renderCurrentFrame() const;
		
		/// <summary>Sets the color of the background</summary>
		/// <param name="a_Color">The new color</param>
		void setBackgroundColor(Color a_Color);
    private:		
		/// <summary>Initialises the SDL window</summary>
		void initialiseSDLWindow();
		
		/// <summary>Initialises OpenGL to draw using it</summary>
		void initialiseGL() const;
    };
}