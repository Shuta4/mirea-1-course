#include <iostream>
#include <cmath>

int main(int argc, char *argv[])
{
	float a, b, c, d;
	std::cout << "Find x in ax^2 + bx + c = 0\n";
	std::cout << "Enter a, b and c: ";
	std::cin >> a >> b >> c;

	if (a == 0) {
		if (b == 0) {
			if (c == 0) {
				std::cout << "x can be any number\n";
			} else {
				std::cout << "This equation have no solutions\n";
			}
		} else {
			std::cout << "x = " << -c / b << '\n';
		}
	} else {
		d = b * b - 4 * a * c;
		if (d == 0) {
			std::cout << "x = " << -b / (2 * a) << '\n';
		} else if (d < 0) {
			std::cout << "This quadro equation have no solutions\n";
		} else {
			std::cout << "x = " << (-b + std::sqrt(d)) / (2 * a)
				<< " or x = " << (-b - std::sqrt(d)) / (2 * a) << '\n';
		}
	}
}
