#include <Box2D\Box2D.h>

#include "BoxCollider2D.h"
#include "../Rendering/SpriteRenderer.h"
#include "../Transform.h"
#include "../Core/EntitySystem.h"

namespace BadEngine
{
    BoxCollider2D::BoxCollider2D(GameObject a_GameObject)
        : Component(a_GameObject)
    {
    }

    BoxCollider2D::~BoxCollider2D()
    {
    }

    float BoxCollider2D::getWidth() const
    {
        return m_Width;
    }

    float BoxCollider2D::getHeight() const
    {
        return m_Height;
    }

    void BoxCollider2D::setWidth(float a_Width)
    {
        m_Width = a_Width;
        m_Shape.SetAsBox(m_Width / 2, m_Height / 2);
    }

    void BoxCollider2D::setHeight(float a_Height)
    {
        m_Height = a_Height;
        m_Shape.SetAsBox(m_Width / 2, m_Height / 2);
    }

    const b2PolygonShape* BoxCollider2D::getShape() const
    {
        return &m_Shape;
    }
}
