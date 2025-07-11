#pragma once
#include "TextureCache.h"
#include "ResourceCache.h"
#include "../Rendering/SpriteFont.h"
#include "../Audio/Sound.h"

namespace Artifact
{	
	/// <summary>
	/// Provides an interface to the resource caches for textures, fonts and sounds
	/// </summary>
	class ResourceManager
    {
    private:
		/// <summary>
		/// The cache that contains already loaded textures
		/// </summary>
        static TextureCache s_TextureCache;
		/// <summary>
		/// The cache that contains already loaded fonts
		/// </summary>
        static ResourceCache<SpriteFont> s_FontCache;
		/// <summary>
		/// The cache that contains already loaded sounds
		/// </summary>
        static ResourceCache<Sound> s_SoundCache;

    public:		
		/// <summary>Initializes a new instance of the <see cref="ResourceManager"/> class.</summary>
		ResourceManager() = delete;
		
		/// <summary>Finalizes an instance of the <see cref="ResourceManager"/> class.</summary>
		~ResourceManager() = delete;
		
		/// <summary>Initializes a new instance of the <see cref="ResourceManager"/> class.</summary>
		/// <param name="a_ResourceManager">The resource manager to copy</param>
		ResourceManager(const ResourceManager& a_ResourceManager) = delete;
		
		/// <summary>Gets the texture at the specified filepath</summary>
		/// <param name="a_FilePath">The filepath to the texture</param>
		/// <returns>A handle to the specified texture</returns>
		static GLTexture* getTexture(const std::string& a_FilePath);
		
		/// <summary>Gets the font at the specified filepath</summary>
		/// <param name="a_FilePath">The filepath to the font</param>
		/// <returns>A handle to the specified font</returns>
		static SpriteFont* getFont(const std::string& a_FilePath);
		
		/// <summary>Gets the sound at the specified filepath</summary>
		/// <param name="a_FilePath">The filepath to the sound</param>
		/// <returns>A handle to the specified sound</returns>
		static Sound* getSound(const std::string& a_FilePath);
    };
}