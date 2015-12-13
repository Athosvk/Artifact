#pragma once
#include <vector>
#include <memory>

template <typename T>
class Pool
{
private:
    std::vector<std::unique_ptr<T>> m_Items;
    T m_Original;

public:
    Pool(T a_Original, size_t a_InitialSize = 1)
        : m_Original(a_Original)
    {
        m_Items.reserve(a_InitialSize);
        for(size_t i = 0; i < a_InitialSize; ++i)
        {
            createNew();
        }
    }

    Pool(Pool<T>& a_Other) = delete;

    T* getItem()
    {
        T* item = nullptr;
        if(tryFindInactive(item))
        {
            item = createNew();
        }
        return item;
    }

    void resize(int a_NewSize)
    {
        m_Items.resize(a_NewSize);
    }

private:
    T* createNew()
    {
        m_Items.emplace_back(std::make_unique<T>(m_Original));
        return m_Items.back().get();
    }

    bool tryFindInactive(T* a_Item)
    {
        for(const auto& item : m_Items)
        {
            if(!(*iterator->isActive()))
            {
                a_Item = iterator->get();
                a_Item->reset();
                return true;
            }
        }
        return false;
    }
};

