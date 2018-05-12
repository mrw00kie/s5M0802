#include <iostream>
#include <sstream>
#include <string>

#include "Header.h"

int main()
{
	while (1)
	{
		std::string input;
		std::getline(std::cin, input);

		std::istringstream iss(input);

		int r1 = 0;
		int r2 = 0;
		int r3 = 0;

		while (iss)
		{
			std::string sub;
			iss >> sub;

			r1 += rom_one(sub);
			r2 += rom_two(sub);
			r3 += rom_three(sub);
		}

		std::cout << std::hex << "ROM 1: " << r1 << std::endl << "ROM 2: " << r2 << std::endl << "ROM 3: " << r3 << std::endl;
	}

	return 0;
}