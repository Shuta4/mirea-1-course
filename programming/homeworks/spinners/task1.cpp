#include <iostream>

int main(int argc, char *argv[]) {
	unsigned int a, b, c, n;
	std::cout << "Enter A, B and C >> ";
	std::cin >> a >> b >> c;

	n = (c - a) / b;

	std::cout << "N: " << n << '\n';
}
