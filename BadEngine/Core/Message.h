#pragma once
namespace BadEngine
{
    enum class EMessageType
    {
        Update,
        Render,
        LateUpdate,
        FixedUpdate
    };

    class Message
    {
    private:
        const EMessageType m_Type;

    public:
        EMessageType getType() const;
    };
}
