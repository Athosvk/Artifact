#include <GL/glew.h>

#include "GL.h"

namespace Artifact
{
    std::string GL::getErrorString()
    {
        auto error = glGetError();
        return getErrorString(error);
    }

    std::string GL::getErrorString(GLenum a_ErrorCode)
    {
        return std::string(reinterpret_cast<const char*>(glewGetErrorString(a_ErrorCode)));
    }
}
