#include <iostream>

int main(int argc, char *argv[])
{
	bool lamp, curtain;
	int hour;
	std::cout << "Defines if there is a light in the room.\n";

	std::cout << "Enter 1 if curtains is open else enter 0: ";
	std::cin >> curtain;

	std::cout << "Enter 1 if lamp is on else enter 0: ";
	std::cin >> lamp;

	std::cout << "Enter current hour (from 0 to 24): ";
	std::cin >> hour;

	if (hour < 0 || hour > 24) {
		std::cout << "Hour can not be less then 0 or more then 24\n";
		return 1;
	}

	if (lamp || curtain && (hour > 7 && hour < 19)) {
		std::cout << "Soft light covers the room\n";
	} else {
		std::cout << "There is only dark in the room\n";
	}
}
