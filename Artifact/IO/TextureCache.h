#pragma once
#include <map>
#include <memory>
#include <string>

#include "..\GL/GLTexture.h"

namespace Artifact
{	
	/// <summary>
	/// Provides a cache storage for textures, so that textures are only loaded once into memory
	/// </summary>
	class TextureCache
    {
    private:		
		/// <summary>The underlying datastructure for storing the cached textures</summary>
		std::map<const std::string, std::unique_ptr<GLTexture>> m_TextureMap;

    public:		
		/// <summary>Gets the texture.</summary>
		/// <param name="a_FilePath">The a_ file path.</param>
		/// <returns></returns>
		GLTexture* getTexture(const std::string& a_FilePath);
		
		/// <summary>Places the specified texture into the cache</summary>
		/// <param name="a_FilePath">The filepath of the texture</param>
		/// <param name="a_Texture">The texture to cache</param>
		void cacheTexture(const std::string& a_FilePath, std::unique_ptr<GLTexture> a_Texture);
    };
}