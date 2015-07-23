#include <iostream>

#include "ImageLoader.h"
#include "PicoPNG.h"
#include "IOManager.h"
#include "ErrorHandler.h"

namespace BadEngine
{
    GLTexture ImageLoader::loadPNG(const std::string& a_FilePath)
    {
        GLTexture texture = {};

        std::vector<unsigned char> output;
        std::vector<unsigned char> fileData;

        IOManager::tryReadBinaryToBuffer(fileData, a_FilePath);

        unsigned long width;
        unsigned long height;

        int errorCode = decodePNG(output, width, height, fileData.data(), fileData.size());

        if(errorCode != 0)
        {
            throwFatalError("PNG decoding failed with error " + std::to_string(errorCode));
        }

        texture.width = static_cast<float>(width);
        texture.height = static_cast<float>(height);

        glGenTextures(1, &texture.id);
        glBindTexture(GL_TEXTURE_2D, texture.id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, output.data());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        return texture;
    }
}