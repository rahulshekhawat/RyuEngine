
#include <iostream>
#include "ApplicationBase.h"

int main()
{
	ApplicationBase mainApplication;

	try
	{
		int result = mainApplication.Run();
		//~ @todo process Result before exit
	}
	catch (const std::exception& e)
	{

		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

}
