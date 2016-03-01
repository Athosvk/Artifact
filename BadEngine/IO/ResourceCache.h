#pragma once
#include <string>
#include <unordered_map>
#include <memory>

namespace BadEngine
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

        /* Workaround for MSVC bug regarding inability to pass template class arguments
        to template classes */
        template<typename TContainerType, typename TIndexType>
        typename TContainerType::iterator find(TContainerType& a_Container, const TIndexType& a_Index)
        {
            return a_Container.find(a_Index);
        }

        bool tryGetResource(const std::string& a_Name, TResourceType*& a_ResourceHandle)
        {
            auto iterator = find<decltype(m_Cache), std::string>(m_Cache, a_Name);
            if(iterator != m_Cache.end())
            {
                a_ResourceHandle = iterator->second.get();
            }
            return iterator != m_Cache.end();
        }
    };
}