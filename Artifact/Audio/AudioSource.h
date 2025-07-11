#pragma once
#include "../Core/Component.h"

namespace Artifact
{
    class Sound;

	/// <summary> Represents a 2D sound/audio source in the world, used to play the attached sound </summary>
	/// <seealso cref="Component" />
	class AudioSource : public Component
    {
    private:
		/// <summary>Whether the sound is being looped or not</summary>
		bool m_Loop = false;
    public:
		/// <summary>The sound resource to play, containing the sound data</summary>
		Sound* Sound = nullptr;
		/// <summary>
		/// The volume of the sound, so that we can control volume on a per 
		/// audio source instance basis, rather than per sound resource
		/// </summary>
		float Volume = 1.0f;

    public:
		/// <summary>Initializes a new instance of the <see cref="AudioSource"/> class.</summary>
		/// <param name="a_Entity">The entity to couple this component to</param>
		explicit AudioSource(GameObject a_Entity);

		/// <summary>Plays the sound attached to this audio source, using the properties in this audio source</summary>
		void play() const;

		/// <summary>Stops the attached sound from playing</summary>
		void stop() const;

		/// <summary>
		/// Enables the looping of the sound when played on this audio source
		/// so that the caller does not have to contininously check the state
		/// to replay it after it has finished
		/// </summary>
		void enableLooping();

		/// <summary>Disables looping of the sound when played on this audio source</summary>
		void disableLooping();
    };
}