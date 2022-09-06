#include <iostream>
#include <cmath>

int main(int argc, char *argv[])
{
	float n;
	int start;
	std::cout << "Enter N: ";
	std::cin >> n;

	if (n < 0) {
		start = 1;
	} else {
		start = n + 1;
	}

	for (int i = start; i < start + 10; i++) {
		std::cout << i << '\n';
	}
}
