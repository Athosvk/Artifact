#include <fstream>

#include "IOManager.h"
#include "..\ErrorHandler.h"

namespace BadEngine
{
    void IOManager::readBinary(std::vector<char>& a_Buffer, const std::string& a_FilePath)
    {
        auto file = std::ifstream(a_FilePath, std::ios::binary);
        if(file.fail())
        {
            perror(a_FilePath.c_str());
            throwFatalError("Could not open file at " + a_FilePath);
        }

        file.seekg(0, std::ios::end);
        auto fileSize = file.tellg();
        //Subtract header size
        file.seekg(0, std::ios::beg);
        fileSize -= file.tellg();

        a_Buffer.resize(fileSize);

        file.read(a_Buffer.data(), fileSize);
        file.close();
    }

    void IOManager::readText(std::vector<char>& a_Buffer, const std::string& a_FilePath)
    {
        auto file = std::ifstream(a_FilePath);
        if(file.fail())
        {
            perror(a_FilePath.c_str());
            throwFatalError("Could not open file at " + a_FilePath);
        }

        file.seekg(0, std::ios::end);
        auto fileSize = file.tellg();
        //Subtract header size
        file.seekg(0, std::ios::beg);
        fileSize -= file.tellg();

        a_Buffer.resize(fileSize);

        file.read(a_Buffer.data(), fileSize);
        file.close();
    }
}