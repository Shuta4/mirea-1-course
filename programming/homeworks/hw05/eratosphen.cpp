#include <iostream>
#include <cmath>
#include <vector>

int main(int argc, char *argv[]) {
	unsigned int n;
	std::cout << "Enter n >> ";
	std::cin >> n;

	if (n < 1) {
		std::cout << "n must be greater then 1\n";
		return 1;
	}

	std::vector<bool> a(n + 1, true);
	for (int i = 2; i * i <= n; i++) {
		if (a[i]) {
			for (int j = i * i; j <= n; j += i) {
				a[j] = false;
			}
		}
	}

	std::cout << "Numbers: ";
	for (int i = 2; i < a.size(); i++) {
		if (a[i]) {
			std::cout << i << ' ';
		}
	}
	std::cout << '\n';
}
