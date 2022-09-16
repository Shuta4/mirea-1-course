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
	std::cout << "S of rectangle = " << rectangleS(a, b) << '\n';

	std::cout << "Enter a, b, c to calculate S of triangle >> ";
	std::cin >> a >> b >> c;
	std::cout << "S of triangle = " << triangleS(a, b, c) << '\n';

	std::cout << "Enter r to calculate S of circle >> ";
	std::cin >> r;
	std::cout << "S of circle = " << circleS(r) << '\n';
}
