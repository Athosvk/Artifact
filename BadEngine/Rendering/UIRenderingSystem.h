#pragma once
#include "SpriteFont.h"
#include "../Core/System.h"
#include "SpriteBatch.h"

namespace BadEngine
{
    class UIRenderingSystem : public System
    {
    private:
        SpriteBatch m_SpriteBatch;

    public:
        UIRenderingSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem);

        virtual void registerListeners() override;
    private:
        void renderUI();
    };
}
