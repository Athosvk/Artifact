#pragma once
#include <unordered_map>
#include <memory>

namespace Artifact
{
	/// <summary>
	/// Provides a cache storage for the specified TResourceType, so that loads have only to be executed once
	/// </summary>
	template<typename TResourceType>
    class ResourceCache
    {
    private:		
		/// <summary>The underlying cache datastructure</summary>
		std::unordered_map<std::string, std::unique_ptr<TResourceType>> m_Cache;

    public:		
		/// <summary>Emplaces the specified resource under the specified name</summary>
		/// <param name="a_Name">Name of the resource to place, to identify the resource with</param>
		/// <param name="a_Resource">The resource to place into the cache</param>
		/// <returns>A handle to the emplaced resource</returns>
		TResourceType* emplace(const std::string& a_Name, std::unique_ptr<TResourceType> a_Resource)
        {
            auto resourceHandle = a_Resource.get();
            m_Cache.emplace(a_Name, std::move(a_Resource));
            return resourceHandle;
        }
		
		/// <summary>Tries to retrieve the resource, returns true if the resource is in the cache, else returns false</summary>
		/// <param name="a_Name">Name of the resource to find</param>
		/// <param name="a_ResourceHandle">A handle to the resource, as out parameter. Value remains if value was not found in the cache</param>
		/// <returns>Whether the resource was in the cache or not</returns>
		bool tryGetResource(const std::string& a_Name, TResourceType*& a_ResourceHandle)
        {
            auto iterator = m_Cache.find(a_Name);
            if(iterator != m_Cache.end())
            {
                a_ResourceHandle = iterator->second.get();
            }
            return iterator != m_Cache.end();
        }
    };
}