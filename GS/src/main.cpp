
#include <SFML/Graphics.hpp>
#include "Application.h"
#include "Tests.h"

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

