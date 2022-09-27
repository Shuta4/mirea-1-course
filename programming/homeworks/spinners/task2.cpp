#include <iostream>

int main(int argc, char *argv[]) {
	unsigned int m(0), n3(0), n4(0);
	std::cout << "Enter M >> ";
	std::cin >> m;

	if (m % 3 == 0) {
		n3 = m / 3;
	} else if (m % 4 == 0) {
		n4 = m / 4;
	} else if (m > 2) {
		for (int i = m % 4; i >= 0; i--) {
			int c4 = i * 4;
			int c3 = m - c4;

			if (c3 % 3 == 0) {
				n3 = c3 / 3;
				n4 = i;
				break;
			}
		}
	}

	std::cout << "N3: " << n3 << '\n'
			  << "N4: " << n4 << '\n';
}
