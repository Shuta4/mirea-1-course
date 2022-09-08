#include <iostream>
#include <cmath>

int main(int argc, char *argv[])
{
	float S, p;
	int n;
	std::cout << "Find m by S, p, n\n";
	std::cout << "Enter S, p and n: ";
	std::cin >> S >> p >> n;

	if (S == 0 || n == 0 || p == 0) {
		std::cout << "S, p and n can not be 0\n";
		return 1;
	}

	if (n < 0) {
		std::cout << "n must be greater then 0\n";
		return 1;
	}

	float r = p / 100;
	float m = (S * r * std::pow(1 + r, n)) / (12 * (std::pow(1 + r, n) - 1));

	std::cout << "m = " << m << '\n';
}
