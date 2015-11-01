#pragma once
#include <vector>

namespace BadEngine
{
    class IOManager
    {
    public:
        IOManager() = delete;
        ~IOManager() = delete;

        static void readBinary(std::vector<unsigned char>& a_Buffer, const std::string& a_FilePath);
        static void readText(std::vector<char>& a_Buffer, const std::string& a_FilePath);
    };
}