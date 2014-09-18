#ifndef DATEUTILS_H
#define DATEUTILS_H

#pragma once
#include <string>

class Dateutils
{
public:
	static void getDateTimeRfc2822(std::string &s);
	static void getLastModifiedRfc2822(std::string &s);
	static std::string getDateTime();


};

#endif
