#include <iostream>

int sign(float const& x) {
	if (x > 0) {
		return 1;
	} else if (x == 0) {
		return 0;
	} else {
		return -1;
	}
}

int main(int argc, char *argv[])
{
	float x;
	std::cout << "sign(x)\nEnter x >> ";
	std::cin >> x;

	std::cout << sign(x) << '\n';

}
