#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H

#pragma once

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

typedef sf::Vector2i MousePosition;
typedef sf::Vector2f TilePosition;
typedef sf::Vector2f SpritePosition;


class GlobalConfig
{
public:
	static GlobalConfig& get();
	
	// Initalization check
	bool								IS_INITALIZED;

	// The different times it takes to use each station
	float								WASH_USE_TIME;
	float								CUT_USE_TIME;
	float								COLOR_USE_TIME;
	float								REGISTER_USE_TIME;

	int									TOTAL_CUSTOMERS;

	// The number of seconds it takes before heart penalties are enforced between state changes
	float								STATE_CHANGE_COOLDOWN;

	// AI engine
	bool								AI_ENGINE_ENABLED;

	// Multipliers
	float								CUSTOMER_SPEED_MULTIPLIER;

private:
	void initalize();	
	GlobalConfig() {}
	GlobalConfig(const GlobalConfig&);
	GlobalConfig& operator=(const GlobalConfig&);

};

#endif
