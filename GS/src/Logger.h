#ifndef LOGGER_H
#define LOGGER_H

#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "Fileutils.h"


class Logger
{
public:
	static Logger& get();
	void setLogFilename(std::string filename);
	void write();
	void createEntry(std::string filename);
	void log(std::string entry);
private:
	void clear();
	std::string mFilename;
	std::string mLogdata;
	Logger() {}
	Logger(const Logger&);
	Logger& operator=(const Logger&);

};


#endif