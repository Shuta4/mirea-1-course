#include <iostream>
#include <cmath>

int main(int argc, char *argv[]) {
	int a, b;
	std::cout << "Enter a and b >> ";
	std::cin >> a >> b;

	// division
	int d_a = a, d_b = b;
	while (d_a != 0 && d_b != 0) {
		if (d_a >= d_b) {
			d_a %= d_b;
		} else {
			d_b %= d_a;
		}
	}
	std::cout << "NOD (div) = " << d_a + d_b << '\n';

	// subtraction
	int s_a = a, s_b = b;
	while (s_a != s_b) {
		if (s_a > s_b) {
			s_a -= s_b;
		} else {
			s_b -= s_a;
		}
	}
	std::cout << "NOD (sub) = " << s_a << '\n';

}
