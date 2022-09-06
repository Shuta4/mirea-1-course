#include <iostream>
#include <cmath>

int main(int argc, char *argv[])
{
	float x, a;
	std::cout << "Enter x and a: ";
	std::cin >> x >> a;

	if (std::abs(x) < 1) {
		std::cout << "w = " << a * std::log(std::abs(x)) << '\n';
	} else if (x * x > a) {
		std::cout << "Can not compute square root\n";
	} else {
		std::cout << "w = " << std::sqrt(a - x * x) << '\n';
	}
}
