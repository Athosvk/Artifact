#pragma once
#include <BadEngine/Core/GameObject.h>
#include <BadEngine/Physics/BoxCollider2D.h>
#include <BadEngine/Rendering/SpriteRenderer.h>

class Box : public BadEngine::GameObject
{
private:
    BadEngine::BoxCollider2D* m_Collider;
    BadEngine::SpriteRenderer* m_Renderer;

public:
    Box(unsigned a_ID, BadEngine::EntitySystem& a_EntitySystem);

    void setDimensions(float a_Width, float a_Height);
};

