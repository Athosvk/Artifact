#pragma once
#include "../Core/System.h"
#include "../Rendering/SpriteBatch.h"

namespace BadEngine
{
    class SpriteRenderSystem : public System
    {
    public:
        SpriteRenderSystem(EntitySystem& a_EntitySystem);

        virtual void sendMessage(const Message* a_Message) override;

    private:
        void renderSprites(EntitySystem& a_EntitySystem);
    };
}
