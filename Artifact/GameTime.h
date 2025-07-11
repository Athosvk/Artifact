#pragma once
#include <vector>

namespace Artifact
{	
	/// <summary>
	/// Represents the in game time
	/// </summary>
	class GameTime
    {
    private:		
		/// <summary>The current time in seconds passed</summary>
		double m_CurrentTime = 0.0;		
		/// <summary>The current time in the previous frame</summary>
		double m_PreviousTime = 0.0;;		
		/// <summary>The time passed between the current and previous frame</summary>
		double m_DeltaTime = 0.0;		
		/// <summary>The current frame number</summary>
		int m_CurrentFrame = 1;		
		/// <summary>The amount of samples taken to calculate the average times</summary>
		int m_SampleCount = 15;		
		/// <summary>The delta time samples taken from previous frames</summary>
		std::vector<double> m_Samples;

    public:		
		/// <summary>Initializes a new instance of the <see cref="GameTime"/> class.</summary>
		GameTime();
		
		/// <summary>Gets the current time in seconds</summary>
		/// <returns>The current time</returns>
		double getCurrentTime() const;
		
		/// <summary>Gets the delta time, the time passed between the current and previous frame</summary>
		/// <returns>The delta time</returns>
		double getDeltaTime() const;
		
		/// <summary>Gets the average delta time</summary>
		/// <returns>The average delta time, measured over the specified sample amount of frames</returns>
		double getAverageDeltaTime() const;
		
		/// <summary>Sets the frame sample count.</summary>
		/// <param name="a_FrameSampleCount">The new amount of frames to sample</param>
		void setFrameSampleCount(int a_FrameSampleCount);
		
		/// <summary>Updates the delta time based on the current and previous time</summary>
		void update();
    };
}

