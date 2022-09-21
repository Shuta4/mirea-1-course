#include <iostream>
#include <cmath>

float rectangleS(float const& a, float const& b) {
	return a * b;
}

float triangleS(float const& a, float const& b, float const& c) {
	float const p = (a + b + c) / 2;
	return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

float circleS(float const& r) {
	return M_PI * r * r;
}

int main(int argc, char *argv[]) {
	float a, b, c, r;

	std::cout << "Enter a and b to calculate S of rectangle >> ";
	std::cin >> a >> b;
	if (a <= 0 || b <= 0) {
		std::cout << "a and b must be greter then 0\n";
		return 1;
	}
	std::cout << "S of rectangle = " << rectangleS(a, b) << '\n';

	std::cout << "Enter a, b, c to calculate S of triangle >> ";
	std::cin >> a >> b >> c;
	if (a <= 0 || b <= 0 || c <= 0) {
		std::cout << "a, b and c must be greater then 0\n";
		return 1;
	}
	if (a + b > c || a + c > b || c + b > a) {
		std::cout << "Incorrect values\n";
		return 1;
	}
	std::cout << "S of triangle = " << triangleS(a, b, c) << '\n';

	std::cout << "Enter r to calculate S of circle >> ";
	std::cin >> r;
	if (r <= 0) {
		std::cout << "r must be greater then 0\n";
		return 1;
	}
	std::cout << "S of circle = " << circleS(r) << '\n';
}
