#include <iostream>
#include <string>

#include "ImageLoader.h"
#include "PicoPNG.h"
#include "IOManager.h"
#include "../ErrorHandler.h"

namespace Artifact
{
    std::unique_ptr<GLTexture> ImageLoader::loadPNG(const std::string& a_FilePath)
    {
        std::vector<char> fileData;
        IOManager::readBinary(fileData, a_FilePath);

        unsigned long width;
        unsigned long height;
        std::vector<unsigned char> output;

        auto errorCode = decodePNG(output, width, height, reinterpret_cast<unsigned char*>(fileData.data()), fileData.size());

        if(errorCode != 0)
        {
            throwFatalError("PNG decoding failed with error " + std::to_string(errorCode));
        }

        auto texture = std::make_unique<GLTexture>(static_cast<float>(width), static_cast<float>(height));
        texture->uploadData(output);
        return texture;
    }
}