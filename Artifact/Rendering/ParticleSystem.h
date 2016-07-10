#pragma once
#include "../Core/System.h"
#include "SpriteBatch.h"
#include "ParticleEmitter.h"

namespace Artifact
{
	/// <summary> The system drawing the particles of each particle emmitter </summary>
	/// <seealso cref="System" />
	class ParticleSystem : public System
	{
	private:
		/// <summary>The SpriteBatch to draw the particles with</summary>
		SpriteBatch m_SpriteBatch;
	public:
		/// <summary>Initializes a new instance of the <see cref="ParticleSystem"/> class.</summary>
		/// <param name="a_EntitySystem">The entity system to operate on, so that it can fetch the needed components </param>
		/// <param name="a_MessagingSystem">The messaging system to communicate with other systems.</param>
		ParticleSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem);

		/// <summary>Registers the listeners for the messages it will listen to </summary>
		virtual void registerListeners() override;
	private:
		/// <summary>Renders the particles of each particle emitters </summary>
		void render();
		
		/// <summary>Updates the particle simulations</summary>
		/// <param name="a_DeltaTime">The time since the last update</param>
		void updateParticleSimulations(double a_DeltaTime) const;

		/// <summary>Integrates the attributes of each particle using their corresponding emitter </summary>
		void integrateAttributes() const;

		template<typename TValueType>
		TValueType lerp(TValueType a_Value1, TValueType a_Value2, float a_T) const
		{
			return a_Value1 + (a_Value2 - a_Value1) * a_T;
		}

		template<>
		Color lerp(Color a_Value1, Color a_Value2, float a_T) const
		{
			auto result = lerp<glm::vec4>(glm::vec4(a_Value1.R, a_Value1.G, a_Value1.B, a_Value1.A),
				glm::vec4(a_Value2.R, a_Value2.G, a_Value2.B, a_Value2.A), a_T);
			return Color(result.x, result.y, result.z, result.w);
		}
	};
}
