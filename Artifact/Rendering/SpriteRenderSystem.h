#pragma once
#include "../Core/System.h"
#include "../Rendering/SpriteBatch.h"

namespace Artifact
{
    class RenderMessage;

    class SpriteRenderSystem : public System
    {
    private:
        SpriteBatch m_SpriteBatch;
        Camera2D* m_CurrentCamera;

    public:
        SpriteRenderSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem);

        virtual void registerListeners() override;

    private:
        void renderSprites();
    };
}
