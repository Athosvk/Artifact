#pragma once
#include <string>

class GL
{
public:
    GL();
    ~GL();

    static std::string getErrorString();
    static std::string getErrorString(GLenum a_ErrorCode);
};