
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <algorithm>
#include "GlobalConfig.h"
#include "Application.h"
#include "Tests.h"

std::map<std::string, std::string> g_debugData;
bool g_collisionOverlay = false;


int main()
{
#ifdef RUN_TESTS

	Tests t;
	t.run();
	return 0;
#endif

	try
	{
		Application app;
		app.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}

    return 0;
}

