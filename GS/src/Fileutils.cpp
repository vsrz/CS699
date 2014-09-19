#include "Fileutils.h"
#include <iostream>

/**
 * CS537 - Advanced Networking, T. Springer Spr2013
 * Jeremy Villegas, Justin Power
 **/

/* write string stream to disk */
bool Fileutils::writeFileToDisk(std::string file, std::string filename, std::ios::openmode openmode)
{
	try
	{
		std::ofstream f(filename.c_str(), openmode);
		f << file;
		f.close();
	}
	catch (int error)
	{
		std::cout << "Error writing file";
		return false;
	}
	return true;
}


/* gets the extension of a filename */
std::string Fileutils::getFileExtension(std::string fn)
{
	return (fn.substr(fn.find_last_of(".") + 1));
}

/* converts file to uppercase */
std::string Fileutils::stringToUpper(std::string s)
{
	std::string str;
	for (size_t l = 0; l < s.length(); l++)
		str += toupper(s[l]);
	return str;
}

/* returns bool based on file existing */
bool Fileutils::fileExists(std::string fn)
{
	std::ifstream in;
	in.open(fn.c_str(), std::ios::binary);
	if (in.is_open())
	{
		in.close();
		return true;
	}
	return false;

}

/* Read file and return the file in a string
* assume it exists */
void Fileutils::readFile(std::string &s, std::string fn)
{
	std::ifstream f(fn.c_str(), std::ios::in | std::ios::binary);

	if (f)
	{
		std::string content;

		/* Jump to the end and grab the length */
		f.seekg(0, std::ios::end);
		content.resize(f.tellg());
		f.seekg(0, std::ios::beg);

		/* read close and return the file */
		f.read(&content[0], content.size());
		f.close();

		s += content;
	}

}
