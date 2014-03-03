#include "GlobalConfig.h"

GlobalConfig& GlobalConfig::get()
{
	static GlobalConfig i;
	return i;
}

GlobalConfig::GlobalConfig()
{
	initalize();
}

template <typename T>
T GlobalConfig::getValue(std::string key)
{
	auto value = mConfig.find(key);
	if (value == mConfig.end()) return std::string();
	return value->second;
}

void GlobalConfig::initalize()
{	
	
}

void GlobalConfig::setValue(std::string key, std::string value)
{
	std::pair<std::string, std::string> p(key, value);
	mConfig.insert(p);
}
