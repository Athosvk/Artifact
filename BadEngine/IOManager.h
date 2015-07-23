#pragma once
#include <vector>

namespace BadEngine
{
    class IOManager
    {
    public:
        static bool IOManager::tryReadBinaryToBuffer(std::vector<unsigned char>& a_Buffer, const std::string& a_FilePath);
    };
}