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

	// Allocation points
	ALLOCATION_POINTS					= 100.f;

	// Time it takes to use the various stations
	WASH_USE_TIME						= 3.f;
	CUT_USE_TIME						= 3.f;
	COLOR_USE_TIME						= 3.f;
	REGISTER_USE_TIME					= 1.f;	

	// Total customers we're required to serve
	TOTAL_CUSTOMERS						= 15;

	// Customer Speed Multiplier
	CUSTOMER_SPEED_MULTIPLIER			= 1.f;

	// The number of seconds it takes before heart penalties are enforced between state changes
	STATE_CHANGE_COOLDOWN_MULTIPLIER	= 100.f;
	PATIENCE_PENALTY_MULTIPLIER			= 100.f;

	// This flag will cause customers to move to chairs from the waiting area on their own
	AI_ENGINE_ENABLED					= true;
	AI_ENGINE_TICKRATE					= 2.f;

	// Cost to the customer for each service
	PAYMENT_WASH						= 5.f;
	PAYMENT_CUT							= 25.f;
	PAYMENT_COLOR						= 25.f;
	PAYMENT_PRODUCT						= 40.f;
	
	// Tip multiplier
	CUSTOMER_TIP_MULTIPLIER				= 100.f;

	// Starting heart 
	STARTING_PATIENCE_MULTIPLIER		= 100.f;


	// How often the game attempts to release a customer into the scene
	CUSTOMER_RELEASE_INTERVAL = 2.f;

	IS_INITALIZED = true;


}

