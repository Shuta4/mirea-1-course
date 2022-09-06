#include <iostream>
#include <cmath>

int main(int argc, char *argv[])
{
	float R, r, h;
	std::cout << "Find V and S of truncated cone\n";
	std::cout << "Enter R, r and h: ";
	std::cin >> R >> r >> h;

	if (R <= 0 || r <= 0 || h <= 0) {
		std::cout << "All entered values should be greater then 0\n";
	} else {
		std::cout << "V = " << 1.0 / 3.0 * M_PI * h * (R * R + R * r + r * r)
			<< "; S = " << M_PI * (R * R + (R + r) *
					std::sqrt((R - r) * (R - r) + h * h) + r * r) << '\n';
	}
}
