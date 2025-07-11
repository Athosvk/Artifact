#pragma once
#include <vector>
#include <memory>
#include <typeindex>

#include "MessagingSystem.h"

namespace Artifact
{
	/// <summary>
	/// A queue of messages that can be dispatched at once, so dispatching of a set of messages can be delayed
	/// </summary>
	class MessageQueue
    {
	private:
		/// <summary>
		/// A message that has been added to the queue
		/// </summary>
		struct QueuedMessage
        {
		private:
			/// <summary>The message containing the data of the type stored in m_MessageType</summary>
			std::unique_ptr<Message> m_Message;
			/// <summary>The type(index) of the message stored in this</summary>
			std::type_index m_MessageType;
			/// <summary>The entity to target with this message</summary>
			GameObject m_Target;

        public:			
			/// <summary>Initializes a new instance of the <see cref="QueuedMessage"/> struct.</summary>
			/// <param name="a_Message">The message that should be queued</param>
			/// <param name="a_Type">The type of the message to queue</param>
			/// <param name="a_Target">The GameObject at which the message is targeted</param>
			QueuedMessage(std::unique_ptr<Message> a_Message, std::type_index a_Type, GameObject a_Target);

			/// <summary>Gets the message that is stored in this instance</summary>
			/// <returns>The message with the message data</returns>
			const Message* getMessage() const;

			/// <summary>Gets the type index for the message type</summary>
			/// <returns>The type index for the message type</returns>
			std::type_index getMessageType() const;

			/// <summary>Gets the target for the message</summary>
			/// <returns>The target entity</returns>
			GameObject getTarget() const;
        };

		/// <summary>The messages stored in this queue</summary>
		std::vector<QueuedMessage> m_Messages;

    public:
		/// <summary>Returns the iterator to the first message</summary>
		/// <returns>The iterator to the first element</returns>
		auto begin()->decltype(m_Messages.begin());

		/// <summary>Returns the iterator to beyond the last message</summary>
		/// <returns></returns>
		auto end()->decltype(m_Messages.end());

		/// <summary>Clears the quueu of messages</summary>
		void clear();

		/// <summary>Determines whether there are messages queued or not</summary>
		/// <returns>Whether there are messages queued</returns>
		bool isEmpty() const;

		/// <summary>Enqueues a message of the specified type using the given arguments for its constructor 
		/// that is aimed towards the given target</summary>
		/// <param name="a_Target">The target at which the message is aimed</param>
		/// <param name="a_MessageArguments">The arguments for the constructor of the message</param>
		template<typename TMessageType, typename ...TArguments>
        void enqueue(GameObject a_Target, TArguments&&... a_MessageArguments)
        {
            auto message = std::make_unique<TMessageType>(std::forward<TArguments>(a_MessageArguments)...);
            m_Messages.emplace_back(std::move(message), typeid(TMessageType), a_Target);
        }
    };
}
