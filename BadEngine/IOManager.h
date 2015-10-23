#pragma once
#include <vector>

namespace BadEngine
{
    class IOManager
    {
    public:
        IOManager() = delete;
        ~IOManager() = delete;

        static bool IOManager::tryReadBinary(std::vector<unsigned char>& a_Buffer, const std::string& a_FilePath);
    };
}