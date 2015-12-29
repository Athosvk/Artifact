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
        Message(EMessageType a_MessageType);

        EMessageType getType() const;
    };
}
