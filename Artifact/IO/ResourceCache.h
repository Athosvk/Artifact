#pragma once
#include <string>
#include <unordered_map>
#include <memory>

namespace Artifact
{
    template<typename TResourceType>
    class ResourceCache
    {
    private:
        std::unordered_map<std::string, std::unique_ptr<TResourceType>> m_Cache;

    public:
        TResourceType* emplace(const std::string& a_Name, std::unique_ptr<TResourceType> a_Resource)
        {
            auto resourceHandle = a_Resource.get();
            m_Cache.emplace(a_Name, std::move(a_Resource));
            return resourceHandle;
        }

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