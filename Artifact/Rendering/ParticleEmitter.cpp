#include <cmath>

#include "ParticleEmitter.h"
#include "../MathHelper.h"
#include "../Random.h"

namespace Artifact
{
	ParticleEmitter::ParticleEmitter(GameObject a_GameObject)
		: Component(a_GameObject)
	{
	}

	void ParticleEmitter::spawn(unsigned a_Count)
	{
		auto newFirstInactive = static_cast<size_t>(MathHelper::min(Particles.size(), m_FirstInactive + a_Count));
		for(size_t i = m_FirstInactive; i < newFirstInactive; ++i)
		{
			Particles[i] = Particle();
			float angle = Random::range(MinAngle, MaxAngle);
			Particles[i].Direction = MathHelper::directionFromAngle(angle);
		}
		m_FirstInactive = newFirstInactive;
	}

	void ParticleEmitter::update(double a_DeltaTime)
	{
		if(SpawnInterval > 0.0f)
		{
			m_SpawnTimer += static_cast<float>(a_DeltaTime);
			auto spawnCount = static_cast<int>(m_SpawnTimer / SpawnInterval);
			if(spawnCount > 0)
			{
				spawn(spawnCount);
			}
			m_SpawnTimer = fmod(m_SpawnTimer, SpawnInterval);
		}
		for(size_t i = 0; i < m_FirstInactive; ++i)
		{
			Particles[i].PreviousLifeTime = Particles[i].LifeTime;
			Particles[i].LifeTime += static_cast<float>(a_DeltaTime);
			if(Particles[i].LifeTime >= MaxLifeTime)
			{
				deactivate(i);
			}
		}
	}

	size_t ParticleEmitter::getFirstInactiveIndex() const
	{
		return m_FirstInactive;
	}

	void ParticleEmitter::deactivate(size_t a_Index)
	{
		std::swap(Particles[a_Index], Particles[m_FirstInactive - 1]);
		m_FirstInactive--;
	}
}
