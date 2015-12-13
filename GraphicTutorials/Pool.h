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
        m_Original.deactivate();
        m_Items.reserve(a_InitialSize);

        for(size_t i = 0; i < a_InitialSize; ++i)
        {
            auto item = createNew();
        }
    }

    Pool(Pool<T>& a_Other) = delete;

    T* getItem()
    {
        T* item = nullptr;
        if(!tryFindInactive(item))
        {
            item = createNew();
        }
        item->activate();
        return item;
    }

    void resize(int a_NewSize)
    {
        m_Items.resize(a_NewSize);
    }

    auto begin()->decltype(m_Items.begin())
    {
        return m_Items.begin();
    }

    auto end()->decltype(m_Items.end())
    {
        return m_Items.end();
    }

private:
    T* createNew()
    {
        m_Items.push_back(m_Original.clone());
        return m_Items.back().get();
    }

    bool tryFindInactive(T*& a_Item)
    {
        for(const auto& item : m_Items)
        {
            if(!item->isActive())
            {
                a_Item = item.get();
                return true;
            }
        }
        return false;
    }
};

