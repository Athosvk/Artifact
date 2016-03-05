#pragma once
#include <vector>

namespace Artifact
{
    class IOManager
    {
    public:
        IOManager() = delete;
        ~IOManager() = delete;

        static void readBinary(std::vector<char>& a_Buffer, const std::string& a_FilePath);
        static void readText(std::vector<char>& a_Buffer, const std::string& a_FilePath);

    private:
        static void readFileStream(std::vector<char>& a_Buffer, std::ifstream& a_File);
    };
}