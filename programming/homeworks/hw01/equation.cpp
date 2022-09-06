#include <iostream>

int main(int argc, char *argv[])
{
	float b, c;
	std::cout << "Find x in bx + c = 0\n";
	std::cout << "Enter b and c: ";
	std::cin >> b >> c;

	if (b == 0) {
		if (c == 0) {
			std::cout << "x can be any number\n";
		} else {
			std::cout << "This equation have no solutions\n";
		}
	} else {
		std::cout << "x = " << -c / b << '\n';
	}
}
