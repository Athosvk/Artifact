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
        EMessageType m_Type;

    public:
        Message();
        EMessageType getType() const;
    };
}
