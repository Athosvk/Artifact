#pragma once
#include <memory>

#include "../GL/GLTexture.h"

namespace Artifact
{
	/// <summary>
	/// Interface for loading images from disks
	/// </summary>
	class ImageLoader
    {
    public:
		/// <summary>Initializes a new instance of the <see cref="ImageLoader"/> class.</summary>
		ImageLoader() = delete;

		/// <summary>Finalizes an instance of the <see cref="ImageLoader"/> class.</summary>
		~ImageLoader() = delete;
		
		/// <summary>Loads the the specified PNG format image from disk</summary>
		/// <param name="a_FilePath">The file path to the PNG image</param>
		/// <returns>A pointer to the PNG image loaded into memory</returns>
		static std::unique_ptr<GLTexture> loadPNG(const std::string& a_FilePath);
    };
}