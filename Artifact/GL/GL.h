#pragma once
#include <string>

namespace Artifact
{
    class GL
    {
    public:
        GL() = delete;
        ~GL() = delete;

        static std::string getErrorString();
        static std::string getErrorString(GLenum a_ErrorCode);
    };
}