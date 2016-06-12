#pragma once
#include <string>

namespace Artifact
{	
	/// <summary>
	/// Provides a more universal access and utility functions for communicating with the OpenGL api
	/// </summary>
	class GL
    {
    public:
        GL() = delete;
        ~GL() = delete;
		
		/// <summary>Pops the last reported error of the stack as string</summary>
		/// <returns>The description of the last reported error</returns>
		static std::string getErrorString();
		
		/// <summary>Gets the error string using the given error code</summary>
		/// <param name="a_ErrorCode">The error code to get the description of</param>
		/// <returns>The description of the error</returns>
		static std::string getErrorString(GLenum a_ErrorCode);
    };
}