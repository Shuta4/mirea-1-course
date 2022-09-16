#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
	std::ofstream fo;
	fo.open("test");
	for (int i = 1; i <= 10; i++) {
		float x;
		std::cout << "Enter " << i << " number >> ";
		std::cin >> x;
		fo << x << '\n';
	}
	fo.close();

	std::ifstream fi;
	fi.open("test");
	float s = 0;
	for (int i = 0; i < 10; i++) {
		float x;
		fi >> x;
		s += x;
	}
	fi.close();

	std::cout << "Sum of numbers = " << s << '\n';
}
