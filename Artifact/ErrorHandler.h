#pragma once
#include <string>

namespace Artifact
{
	/// <summary>
	/// Throws a fatal error, exciting the application after displaying the error message
	/// </summary>
    void throwFatalError(std::string a_ErrorMessage);
}