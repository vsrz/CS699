#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>

#pragma once

class Fileutils
{
public:
	static bool writeFileToDisk(std::string data, std::string filename, std::ios::openmode openmode = std::ios::app);
	static std::string getFileExtension(std::string filename);
	static std::string stringToUpper(std::string s);
	static bool fileExists(std::string filename);
	static void readFile(std::string &s, std::string filename);
};

#endif
