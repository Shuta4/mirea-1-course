#include <iostream>

int f(int const& m, int const& b, int const& c, int const& i) {
	if (i == 0) {
		return 0;
	}
	return (m * f(m, b, c, i - 1) + b) % c;
}

int main(int argc, char *argv[]) {
	int m, b, c, i;

	std::cout << "Enter m, b, c and i >> ";
	std::cin >> m >> b >> c >> i;

	if (c == 0) {
		std::cout << "c can not be 0\n";
		return 1;
	}

	std::cout << "Generated number = " << f(m, b, c, i) << '\n';
}
