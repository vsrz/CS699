
#include <SFML/Graphics.hpp>
#include "Application.h"
#include "Tests.h"

int main()
{
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

