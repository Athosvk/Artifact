#pragma once
#include <glm/glm.hpp>
#include <vector>

#include "../Core/Component.h"
#include "../Core/GameObject.h"
#include "../Color.h"
#include "../GL/GLTexture.h"

namespace Artifact
{
	/// <summary> A particle emmitter, capable of emitting collections of particles </summary>
	/// <seealso cref="Component" />
	class ParticleEmitter : public Component
	{
	private:		
		/// <summary> A single particle instance for drawing </summary>
		struct Particle
		{
			/// <summary>The relative position</summary>
			glm::vec2 RelativePosition = { 0.0f, 0.0f };
			/// <summary> The direction the particle is traveling in </summary>
			glm::vec2 Direction = { 1.0f, 0.0f };
			/// <summary> The life time </summary>
			float LifeTime = 0.0f;
			float PreviousLifeTime = 0.0f;
		};
	private:
		/// <summary>The index of the first inactive particle</summary>
		size_t m_FirstInactive = 0;
		float m_SpawnTimer = 0.0f;
	public:
		/// <summary> The spawn rate of the particles per second </summary>
		float SpawnInterval = 0.0f;
		/// <summary> The maximum time in seconds before a particle dies </summary>
		float MaxLifeTime = 0.25f;
		/// <summary> The speed of the particles when they are spawned </summary>
		float StartSpeed = 0.03f;
		/// <summary>The speed of the particles when they are nearing the end of lifetime</summary>
		float EndSpeed = 0.005f;
		/// <summary> The color of the particles when they are spawned </summary>
		Color StartColor = Color(1.0f, 1.0f, 1.0f, 1.0f);
		/// <summary> The color of the particles when they are at the end of lifetime </summary>
		Color EndColor = Color(1.0f, 1.0f, 0.0f, 0.0f);
		/// <summary>The start size</summary>
		float StartSize = 0.1f;
		/// <summary>The end size</summary>
		float EndSize = 0.15f;
		/// <summary>The minimum angle the particles are spawned with respect to the emitter </summary>
		float MinAngle = 180.0f;
		/// <summary>The maximum angle the particles are spawned with respect to the emitter </summary>
		float MaxAngle = 360.0f;
		/// <summary>The time the simluation has been running for this particle emitter </summary>
		float SimulationTime = 0.0f;
		/// <summary>The particles</summary>
		std::vector<Particle> Particles = std::vector<Particle>(40000);
		/// <summary>The texture</summary>
		GLTexture* Texture = nullptr;

	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="ParticleEmmitter"/> class.
		/// </summary>
		/// <param name="a_GameObject">The GameObject this component belongs to </param>
		ParticleEmitter(GameObject a_GameObject);
		
		/// <summary>Activates the specified amount of particles, restricted to the maximum amount of particles </summary>
		/// <param name="a_Count">The a_ count.</param>
		void spawn(unsigned a_Count);
		
		/// <summary>Updates simulation by the specified time</summary>
		/// <param name="a_DeltaTime">The a_ delta time.</param>
		void update(double a_DeltaTime);

		/// <summary>Gets the index of the first inactive particles in the array</summary>
		/// <returns>The index of the first inactive particle</returns>
		size_t getFirstInactiveIndex() const;
	private:
		/// <summary>Deactivates the particle at given index</summary>
		/// <param name="a_Index">The index of the particle to deactivate</param>
		void deactivate(size_t a_Index);
	};
}