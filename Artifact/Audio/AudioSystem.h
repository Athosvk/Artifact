#pragma once
#include "../Core/System.h"

namespace Artifact
{
	/// <summary>
	/// Represents the overall audio system, managing the interface to the library it encapsulates
	/// </summary>
	/// <seealso cref="System" />
	class AudioSystem : public System
    {
    public:
		/// <summary>Initializes a new instance of the <see cref="AudioSystem"/> class.</summary>
		/// <param name="a_EntitySystem">The entity system to retrieve the components to operate on</param>
		/// <param name="a_MessagingSystem">The messaging system to use for receiving and sending messages</param>
		AudioSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem);

		/// <summary>Finalizes an instance of the <see cref="AudioSystem"/> class.</summary>
		virtual ~AudioSystem() override;

		/// <summary>Allows for the system to register its listeners to the messagingsystem</summary>
		virtual void registerListeners() override;
    private:
		/// <summary>Initializes the instance of the audio library</summary>
		void initialize() const;
    };
}
