#include <iostream>

int main(int argc, char *argv[])
{
	float a, b;
	std::cout << "Find a + b, a - b, a * b and a / b.\n";
	std::cout << "Enter a and b: ";
	std::cin >> a >> b;

	std::cout << "a + b = " << a + b << '\n';
	std::cout << "a - b = " << a - b << '\n';
	std::cout << "a * b = " << a * b << '\n';
	if(b == 0) {
		std::cout << "Can not divide by 0\n";
	} else {
		std::cout << "a / b = " << a / b << '\n';
	}
}
