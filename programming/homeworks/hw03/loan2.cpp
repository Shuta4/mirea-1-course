#include <iostream>
#include <cmath>

int main(int argc, char *argv[])
{
	float S, m;
	int n;
	std::cout << "Find p by S, m, n\n";
	std::cout << "Enter S, m and n: ";
	std::cin >> S >> m >> n;

	if (S <= 0 || m <= 0) {
		std::cout << "S and m can not be <= 0\n";
		return 1;
	}

	if (n < 0) {
		std::cout << "n must be greater then 0\n";
		return 1;
	}

	float step = 10;
	float r = 10;
	float prev_r = 0;

	if (m * 12 * n < S) {
		std::cout << "Total pay is lower then S\n";
		return 1;
	}

	while (step >= 0.00001) {
		float current_m = (S * r * std::pow(1 + r, n)) / (12 * (std::pow(1 + r, n) - 1));
		if (current_m < m) {
			prev_r = r;
			r += step;
		} else if (std::abs(current_m - m) <= 0.1) {
			std::cout << "p = " << r * 100 << '\n';
			return 0;
		} else {
			step /= 10;
			r = prev_r + step;
		}
	}
	std::cout << "Can not find correct value.\n";
}
