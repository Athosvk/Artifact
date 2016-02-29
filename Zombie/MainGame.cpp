#include <BadEngine/StopWatch.h>
#include <iostream>

#include "MainGame.h"
#include "MainWorld.h"

MainGame::MainGame() : Game(1024, 768, 0, "GameEngine")
{
    m_Window.setBackgroundColor(BadEngine::Color(30, 30, 30, 255));
    printf(" *** OpenGL version: %s *** \n You need at least version %5.2f to run the game. \n", 
           reinterpret_cast<const char*>(glGetString(GL_VERSION)), m_OpenGLVersion);
    loadWorld<MainWorld>();
}
