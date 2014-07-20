#include "GlobalConfig.h"
#include <iostream>

GlobalConfig& GlobalConfig::get()
{
	static GlobalConfig instance;
	instance.initalize();
	return instance;
}

void GlobalConfig::initalize()
{
	// Initial initalization. This is only called once.
	if (IS_INITALIZED)
	{
		return;
	}

	WASH_USE_TIME = 3.f;
	CUT_USE_TIME = 3.f;
	COLOR_USE_TIME = 3.f;
	REGISTER_USE_TIME = 1.f;	

	TOTAL_CUSTOMERS = 15;

	// Customer Speed Multiplier
	CUSTOMER_SPEED_MULTIPLIER = 1.f;

	// The number of seconds it takes before heart penalties are enforced between state changes
	STATE_CHANGE_COOLDOWN = 10.f;

	// AI engine
	AI_ENGINE_ENABLED = false;


	// Payment amounts
	const float							PAYMENT_WASH = 5.f;
	const float							PAYMENT_CUT = 25.f;
	const float							PAYMENT_COLOR = 25.f;
	const float							PAYMENT_PRODUCT = 40.f;
	
	IS_INITALIZED = true;


}

