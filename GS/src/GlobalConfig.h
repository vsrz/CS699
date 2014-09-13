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

	// Total number of customers to service in this trip
	int									TOTAL_CUSTOMERS;

	// The number of seconds it takes before heart penalties are enforced between state changes
	float								STATE_CHANGE_COOLDOWN_MULTIPLIER;
	float								PATIENCE_PENALTY_MULTIPLIER;
	// Add multipler for bonus timer (after they are served)

	// If customers move throughout the salon on their own and how often it does it
	bool								AI_ENGINE_ENABLED;
	float								AI_ENGINE_TICKRATE;

	// Multipliers
	float								CUSTOMER_SPEED_MULTIPLIER;
	float								CUSTOMER_TIP_MULTIPLIER;

	// How often the game attempts to release a customer into the scene
	float								CUSTOMER_RELEASE_INTERVAL;

	// Cost to the customer for each service
	float								PAYMENT_WASH;
	float								PAYMENT_CUT;
	float								PAYMENT_COLOR;
	float								PAYMENT_PRODUCT;

	// Starting heart multiplier. No matter what is rolled during creation,
	// we multiply the roll by this number when they spawn into the scene
	float								STARTING_PATIENCE_MULTIPLIER;

	std::string							SCORE_FILENAME;
	std::string							SCORE_HTTP_URL;
private:
	void initalize();	
	GlobalConfig() {}
	GlobalConfig(const GlobalConfig&);
	GlobalConfig& operator=(const GlobalConfig&);

};

#endif
