#pragma once
#include <random>

namespace Artifact
{	
	/// <summary>
	/// Provides method for generating random number sequences	
	/// </summary>
	class Random
    {
    private:
		/// <summary> The random engine used for generating the random numbers</summary>
		static std::default_random_engine s_Generator;

    public:		
		/// <summary>Initializes a new instance of the <see cref="Random"/> class.</summary>
		Random() = delete;
		
		/// <summary>Finalizes an instance of the <see cref="Random"/> class.</summary>
		~Random() = delete;
		
		/// <summary>Returns a random number within the specified range</summary>
		/// <param name="a_Min">The minimum value</param>
		/// <param name="a_Max">The maximum value</param>
		/// <returns>A random number between the given boundaries</returns>
		static int range(int a_Min, int a_Max);
		
		/// <summary>Returns a random number within the specified range</summary>
		/// <param name="a_Min">The minimum value</param>
		/// <param name="a_Max">The maximum value</param>
		/// <returns>A random number between the given boundaries</returns>
		static float range(float a_Min, float a_Max);
    };
}
