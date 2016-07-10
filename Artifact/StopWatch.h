#pragma once
#if defined(WIN32) || defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#else 
#include <chrono>
#endif

namespace ArtifactTest
{	
	/// <summary>
	/// Provides methods for measuring elapsed time of a piece of code
	/// </summary>
	class StopWatch
	{
	private:		
		/// <summary>Whether the stopwatch was finished/ended</summary>
		bool m_Finished = false;

#if defined(WIN32) || defined(_WIN32) || defined(_WIN64)		
		/// <summary>The start time</summary>
		LARGE_INTEGER m_StartTime;		
		/// <summary>The end time</summary>
		LARGE_INTEGER m_EndTime;
#else		
		/// <summary>The start time</summary>
		std::chrono::high_resolution_clock::time_point m_StartTime;		
		/// <summary>The end time</summary>
		std::chrono::high_resolution_clock::time_point m_EndTime;
#endif
	public:		
		/// <summary>Creates a stopwatch and starts to record with it</summary>
		/// <returns>The created stopwatch</returns>
		static StopWatch startNew();
		
		/// <summary>Starts recording the time</summary>
		void start();
		
		/// <summary>Ends the time recording</summary>
		void end();

		/// <summary>Gets the measured time in nanoseconds</summary>
		/// <returns>The time passed in nanoseconds</returns>
		long long toNanoseconds();

	private:
#if defined(WIN32) || defined(_WIN32) || defined(_WIN64)		
		/// <summary>Gets the current time.</summary>
		/// <returns>The current time in nanoseconds</returns>
		LARGE_INTEGER getCurrentTime();
#else		
		/// <summary>Gets the current time.</summary>
		/// <returns>The current time in nanoseconds</returns>
		std::chrono::high_resolution_clock::time_point getCurrentTime();
#endif
	};
};
