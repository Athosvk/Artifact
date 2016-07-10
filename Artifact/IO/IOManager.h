#pragma once
#include <vector>

namespace Artifact
{	
	/// <summary>
	/// Handles loading of files from disk into memory
	/// </summary>
	class IOManager
    {
    public:		
		/// <summary>Initializes a new instance of the <see cref="IOManager"/> class.</summary>
		IOManager() = delete;
		
		/// <summary>Finalizes an instance of the <see cref="IOManager"/> class.</summary>
		~IOManager() = delete;
		
		/// <summary>Reads a binary file from disk and places it into the specified buffer</summary>
		/// <param name="a_Buffer">The buffer to load the file into</param>
		/// <param name="a_FilePath">The filepath to the file on disk</param>
		static void readBinary(std::vector<char>& a_Buffer, const std::string& a_FilePath);
		
		/// <summary>Reads an ASCII format file from disk and places it into the specified buffer</summary>
		/// <param name="a_Buffer">The buffer to load the file into</param>
		/// <param name="a_FilePath">The filepath to the file on disk</param>
		static void readText(std::vector<char>& a_Buffer, const std::string& a_FilePath);

    private:		
		/// <summary>Reads the specified filestream into the buffer</summary>
		/// <param name="a_Buffer">The buffer to read it into</param>
		/// <param name="a_File">The filestream to load into the buffer</param>
		static void readFileStream(std::vector<char>& a_Buffer, std::ifstream& a_File);
    };
}