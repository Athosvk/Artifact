#pragma once
#include <memory>
#include <unordered_map>
#include <map>
#include <functional>
#include <typeindex>

#include "../Delegate.h"
#include "GameObject.h"

namespace Artifact
{
    class MessageQueue;
	
	/// <summary>
	/// Represents a message that can be sent using a MessagingSystem instance
	/// </summary>
	class Message
    {
    };
	
	/// <summary>
	/// The system used to allow for communication between different systems
	/// </summary>
	class MessagingSystem
    {
    private:		
		/// <summary>The listeners for messages that are broadcasted</summary>
		std::unordered_map<std::type_index, Delegate<void(const Message*)>> m_MessageListeners;		
		/// <summary>The listeners for messages that are sent to specific entities, mapped using their ID</summary>
		std::unordered_map<std::type_index, std::map<unsigned, Delegate<void(const Message*)>>> m_ObjectMessageListeners;

    public:
		/// <summary>Broadcasts a message of the given MessageType constructed from the given message arguments</summary>
		/// <param name="...a_MessageArguments">The arguments for the message</param>
		template<typename TMessageType, typename... TArguments>
        void broadcast(TArguments&&... a_MessageArguments)
        {
            auto newMessage = TMessageType(std::forward<TArguments>(a_MessageArguments)...);

            auto iterator = m_MessageListeners.find(typeid(TMessageType));
            if(iterator != m_MessageListeners.end())
            {
                iterator->second(&newMessage);
            }
        }

		/// <summary>Sends the message of the given MessageType constructed fromt he message arguments to the specified entity</summary>
		/// <param name="a_GameObject">The entity to send the message to</param>
		/// <param name="...a_MessageArguments">The arguments for constructing the message of the given MessageType</param>
		template<typename TMessageType, typename... TArguments>
        void sendMessage(GameObject a_GameObject, TArguments&&... a_MessageArguments)
        {
            auto newMessage = TMessageType(std::forward<TArguments>(a_MessageArguments)...);
            sendMessage(a_GameObject, &newMessage, typeid(TMessageType));
        }

		/// <summary>Dispatches a queue of messages</summary>
		/// <param name="a_MessageQueue">The messagequeue containing the messages to disptach</param>
		void dispatchQueue(MessageQueue& a_MessageQueue);

		/// <summary>Registers a listener for broadcasted messages</summary>
		/// <param name="a_Callback">The callback to register for the given broadcast</param>
		template<typename TMessageType>
        void registerListener(std::function<void(const Message* a_Message)> a_Callback)
        {
            m_MessageListeners[typeid(TMessageType)] += a_Callback;
        }

		/// <summary>Registers the listener for a message sent to the specified entity</summary>
		/// <param name="a_Callback">The callback to register for the given message</param>
		/// <param name="a_GameObject">The entity to listen to </param>
		template<typename TMessageType>
        void registerListener(std::function<void(const Message* a_Message)> a_Callback, GameObject a_GameObject)
        {
            m_ObjectMessageListeners[typeid(TMessageType)][a_GameObject.getID()] += a_Callback;
        }

    private:		
		/// <summary>Sends the message</summary>
		/// <param name="a_Target">The target of the message</param>
		/// <param name="a_Message">The message to send</param>
		/// <param name="a_Type">The type index of the message's type</param>
		void sendMessage(GameObject a_Target, const Message* a_Message, std::type_index a_Type);
    };
}
