#include "ParticleSystem.h"
#include "RenderMessage.h"
#include "../Core/World.h"

namespace Artifact
{
	ParticleSystem::ParticleSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem)
		: System(a_EntitySystem, a_MessagingSystem)
	{
	}

	void ParticleSystem::registerListeners()
	{
		m_MessagingSystem.registerListener<RenderMessage>([this](const Message* a_Message)
		{
			render();
		});
		m_MessagingSystem.registerListener<UpdateMessage>([this](const Message* a_Message)
		{
			updateParticleSimulations(static_cast<const UpdateMessage*>(a_Message)->
				getGameTime().getDeltaTime());
		});
		m_MessagingSystem.registerListener<FixedUpdateMessage>([this](const Message* a_Message)
		{
			integrateAttributes();
		});
	}

	void ParticleSystem::render()
	{
		m_SpriteBatch.begin(m_EntitySystem.getComponentsOfType<Camera2D>()[0]->getViewProjection());
		for(auto particleEmitter : m_EntitySystem.getComponentsOfType<ParticleEmitter>())
		{
			ComponentHandle<Transform> transform = particleEmitter->getComponent<Transform>();
			for(size_t i = 0; i < particleEmitter->getFirstInactiveIndex(); ++i)
			{
				auto& particle = particleEmitter->Particles[i];
				float relativeLifeTime = particle.LifeTime / particleEmitter->MaxLifeTime;
				float size = lerp(particleEmitter->StartSize, particleEmitter->EndSize, relativeLifeTime);
				auto destinationRectangle = Artifact::Rectangle(transform->getPosition() + 
					particle.RelativePosition - glm::vec2(size / 2, size / 2), size, size);
				m_SpriteBatch.draw(particleEmitter->Texture, destinationRectangle, transform->getRotation(),
					transform->getPosition(), lerp(particleEmitter->StartColor, particleEmitter->EndColor, 
					relativeLifeTime));
			}
		}
		m_SpriteBatch.end();
	}

	void ParticleSystem::updateParticleSimulations(double a_DeltaTime) const
	{
		for(auto particleEmitter : m_EntitySystem.getComponentsOfType<ParticleEmitter>())
		{
			particleEmitter->update(a_DeltaTime);
		}
	}

	void ParticleSystem::integrateAttributes() const
	{
		for(auto particleEmitter : m_EntitySystem.getComponentsOfType<ParticleEmitter>())
		{
			for(size_t i = 0; i < particleEmitter->getFirstInactiveIndex(); ++i)
			{
				auto& particle = particleEmitter->Particles[i];
				float relativeLifeTime = particle.LifeTime / particleEmitter->MaxLifeTime;
				particle.RelativePosition += particle.Direction * lerp(particleEmitter->StartSpeed,
					particleEmitter->EndSpeed, relativeLifeTime);
			}
		}
	}
}
