#include <SDL/SDL.h>
#include <iostream>
#include <string>

#include "ErrorHandler.h"

namespace Artifact
{
    void throwFatalError(std::string a_ErrorMessage)
    {
        std::cout << a_ErrorMessage << std::endl;
        std::cout << "Enter any key to continue...";
        char tmp;
        std::cin >> tmp;
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}