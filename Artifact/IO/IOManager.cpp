#include <fstream>

#include "IOManager.h"

namespace Artifact
{
    void IOManager::readBinary(std::vector<char>& a_Buffer, const std::string& a_FilePath)
    {
        auto fileStream = std::ifstream(a_FilePath, std::ios::binary);
        if(fileStream.fail())
        {
            perror(a_FilePath.c_str());
        }
        readFileStream(a_Buffer, fileStream);
        fileStream.close();
    }

    void IOManager::readText(std::vector<char>& a_Buffer, const std::string& a_FilePath)
    {
        auto fileStream = std::ifstream(a_FilePath);
        if(fileStream.fail())
        {
            perror(a_FilePath.c_str());
        }
        readFileStream(a_Buffer, fileStream);
        fileStream.close();
    }

    void IOManager::readFileStream(std::vector<char>& a_Buffer, std::ifstream& a_File)
    {
        a_File.seekg(0, std::ios::end);
        auto fileSize = a_File.tellg();
        //Subtract header size
        a_File.seekg(0, std::ios::beg);
        fileSize -= a_File.tellg();

        a_Buffer.resize(static_cast<unsigned int>(fileSize));

        a_File.read(a_Buffer.data(), fileSize);
    }
}