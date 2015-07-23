#include <fstream>
#include <iostream>

#include "IOManager.h"
#include "ErrorHandler.h"

namespace BadEngine
{
    bool IOManager::tryReadBinaryToBuffer(std::vector<unsigned char>& a_Buffer, const std::string& a_FilePath)
    {
        std::ifstream file(a_FilePath, std::ios::binary);
        if(file.fail())
        {
            perror(a_FilePath.c_str());
            throwFatalError("Could not open file at " + a_FilePath);
            return false;
        }

        file.seekg(0, std::ios::end);
        int fileSize = static_cast<int>(file.tellg());
        file.seekg(0, std::ios::beg);

        fileSize -= static_cast<int>(file.tellg());

        a_Buffer.resize(fileSize);

        file.read((char *) a_Buffer.data(), fileSize);

        file.close();
        return true;
    }
}