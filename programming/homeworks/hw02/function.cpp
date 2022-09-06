#include <iostream>
#include <cmath>

int main(int argc, char *argv[])
{
	float x, y, b;
	std::cout << "z = ln(b - y) * sqrt(b - x)\n";
	std::cout << "Enter x, y and b: ";
	std::cin >> x >> y >> b;

	if (b - y <= 0) {
		std::cout << "Can not compute ln\n";
	} else if (b - x < 0) {
		std::cout << "Can not compute sqrt\n";
	} else {
		std::cout << "z = " << std::log(b - y) * std::sqrt(b - x) << '\n';
	}
}
