#pragma once
#include <vector>
#include <memory>

#include <Artifact/Core/EntitySystem.h>

template <typename TEntityType = Artifact::GameObject>
class EntityPool
{
private:
    std::vector<TEntityType> m_Items;
    Artifact::EntitySystem& m_EntitySystem;

public:
    EntityPool(Artifact::EntitySystem& a_EntitySystem, size_t a_InitialSize = 0)
        : m_EntitySystem(a_EntitySystem)
    {
        m_Items.reserve(a_InitialSize);
        for(size_t i = 0; i < a_InitialSize; ++i)
        {
            createNew();
        }
    }

    EntityPool(EntityPool<TEntityType>& a_Other) = delete;

    TEntityType getEntity()
    {
        TEntityType* entity = nullptr;
        if(tryFindInactive(entity))
        {
            entity->activate();
        }
        else
        {
            entity = &createNew();
        }
        return *entity;
    }

private:
    TEntityType createNew()
    {
        auto newEntity = m_EntitySystem.createEntity<TEntityType>();
        m_Items.push_back(newEntity);
        return newEntity;
    }

    bool tryFindInactive(TEntityType*& a_Entity)
    {
        for(auto& entity : m_Items)
        {
            if(!entity.isActive())
            {
                a_Entity = &entity;
                return true;
            }
        }
        return false;
    }
};

