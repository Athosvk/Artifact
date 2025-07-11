#pragma once
#include <string>

struct Mix_Chunk;

namespace Artifact
{
	/// <summary>
	/// Represents a sound resource that is loaded from disk, used to play audio in the game
	/// </summary>
	class Sound
    {
    public:
		/// <summary>
		/// The constant that can be used to make an audio source loop forever
		/// when passed as loop variable to play
		/// </summary>
        static const int LoopForever;
	private:
		/// <summary>The constant representing a failure of playing a sound</summary>
        static const int PlayFailed;
		
		/// <summary>The channel the sound is currently being played on</summary>
		/// <remarks> -1 if it is not being played from any channel </remarks>
		int m_CurrentChannel = -1;		
		/// <summary>The sound chunk to interface with SDL_mixer</summary>
		Mix_Chunk* m_SoundChunk;

    public:
		/// <summary>Initializes a new instance of the <see cref="Sound"/> class.</summary>
		/// <param name="a_FilePath">The file path to the sound to load</param>
		explicit Sound(const std::string a_FilePath);

		/// <summary>Finalizes an instance of the <see cref="Sound"/> class.</summary>
		~Sound();

		/// <summary>Plays the sound and loops it the given amount of times</summary>
		/// <param name="a_LoopCount">The amount of times to loop the playing of the sound</param>
		/// <remarks> Pass the LoopForever constant to make it loop until stop is called </remarks>
		void play(int a_LoopCount = 0);

		/// <summary>Stops the sound from playing on its current channel</summary>
		void stop() const;

		/// <summary>Sets the volume of the sound</summary>
		/// <param name="a_Volume">The new volume between 0 and MIX_MAX_VOLUME</param>
		void setVolume(unsigned a_Volume) const;
    };
}
