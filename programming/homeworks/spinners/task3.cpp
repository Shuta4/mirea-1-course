#include <iostream>

int main(int argc, char *argv[]) {
	unsigned int n(0), m(0);
	std::cout << "Enter N and M >> ";
	std::cin >> n >> m;

	int c = 0;
	int r = 0;
	for (int j = 1; j <= n; j++) {
 		c = c + j;
	}
	for (int i = 1; i <= m; i++) {
 		r = r + c * i;
	}

	std::cout << "count: " << r << '\n';
}
