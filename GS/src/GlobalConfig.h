#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H

#pragma once

#include <string>
#include <map>

class GlobalConfig
{
public:
	static GlobalConfig& get();

	
	template <typename T>
	T getValue(std::string key);

	void setValue(std::string key, std::string value);

private:
	void initalize();	
	GlobalConfig();
	GlobalConfig(const GlobalConfig&);
	GlobalConfig& operator=(const GlobalConfig&);

	std::map<std::string, std::string> mConfig;
};

#endif
