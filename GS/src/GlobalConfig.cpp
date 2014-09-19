#include "GlobalConfig.h"
#include <iostream>
#include "Logger.h"
#include "Glob.h"

GlobalConfig& GlobalConfig::get()
{
	static GlobalConfig instance;
	instance.initalize();
	return instance;
}

void GlobalConfig::reset()
{
	IS_INITALIZED = false;
	initalize();
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
	STATE_CHANGE_COOLDOWN_MULTIPLIER	= 1.f;
	PATIENCE_PENALTY_MULTIPLIER			= 1.f;

	// This flag will cause customers to move to chairs from the waiting area on their own
	// Do not option this right now because you lose the opportunity to control customers
	// who are not sitting in the waiting area
	AI_ENGINE_ENABLED					= false;
	AI_ENGINE_TICKRATE					= 2.f;

	// Cost to the customer for each service
	PAYMENT_WASH						= 5.f;
	PAYMENT_CUT							= 25.f;
	PAYMENT_COLOR						= 25.f;
	PAYMENT_PRODUCT						= 40.f;
	
	// Tip multiplier
	CUSTOMER_TIP_MULTIPLIER				= 1.f;

	// Starting heart 
	STARTING_PATIENCE_MULTIPLIER		= 1.f;


	// How often the game attempts to release a customer into the scene
	CUSTOMER_RELEASE_INTERVAL = 5.f;

	// Filename that the scores are written to
	SCORE_FILENAME = "scores.csv";
	SCORE_HTTP_URL = "http://villegasfam.com/p/scores.php";
	SCORE_HASH_KEY = 597u;

	IS_INITALIZED = true;
	Logger::get().log("Game has started");
	logSettings();

}

void GlobalConfig::logSettings()
{

	Logger& log = Logger::get();
	std::string logstring;
	GlobalConfig& g = GlobalConfig::get();
	
	// CSV Values:
	// Cut Time, Wash Time, Color Time, Speed Multiplier, Register Use Time, Release Interval, State Change Cooldown Multiplier, Patience Penalty Multiplier, Remaining Points

	logstring = "Rules: ";
	logstring += toString(g.CUT_USE_TIME) + "," + toString(g.WASH_USE_TIME) + "," + toString(g.COLOR_USE_TIME) + ",";
	logstring += toString(g.CUSTOMER_SPEED_MULTIPLIER) + "," + toString(g.REGISTER_USE_TIME) + "," + toString(g.CUSTOMER_RELEASE_INTERVAL) + ",";
	logstring += toString(g.STATE_CHANGE_COOLDOWN_MULTIPLIER) + "," + toString(g.PATIENCE_PENALTY_MULTIPLIER) + "," + toString(g.ALLOCATION_POINTS);

	log.log(logstring);

}