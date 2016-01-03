#pragma once
#include "../Core/System.h"
#include "../Rendering/SpriteBatch.h"

namespace BadEngine
{
    class RenderMessage;

    class SpriteRenderSystem : public System
    {
    private:
        SpriteBatch m_SpriteBatch;

    public:
        SpriteRenderSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem);

        virtual void registerListeners() override;

    private:
        void renderSprites(const RenderMessage* a_RenderMessage);
    };
}
