#include <iostream>
#include <cmath>

int main(int argc, char *argv[])
{
	for (float x = -4; x <= 4; x = x + 0.5) {
		std::cout << "x = " << x << ": ";
		if (x - 1 == 0) {
			std::cout << "division by 0\n";
		} else {
			std::cout << "y = " << (x * x - 2 * x + 2) / (x - 1) << '\n';
		}
	}
}
