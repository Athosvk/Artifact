#pragma once
#include <Artifact/Core/GameObject.h>
#include <Artifact/Physics/BoxCollider2D.h>
#include <Artifact/Rendering/SpriteRenderer.h>

class Box : public Artifact::GameObject
{
private:
    Artifact::BoxCollider2D* m_Collider;
    Artifact::SpriteRenderer* m_Renderer;

public:
    Box(unsigned a_ID, Artifact::EntitySystem& a_EntitySystem);

    void setDimensions(float a_Width, float a_Height);
};

