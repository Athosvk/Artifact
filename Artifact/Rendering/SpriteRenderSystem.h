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
        ComponentHandle<Camera2D> m_CurrentCamera = ComponentHandle<Camera2D>::NullHandle;

    public:
        SpriteRenderSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem);

        virtual void registerListeners() override;

    private:
        void renderSprites();
    };
}
