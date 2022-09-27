#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[]) {
	unsigned int n(0), k(0);
	std::cout << "Enter N and K >> ";
	std::cin >> n >> k;

	std::vector v {n};
	for (int i = 0; i < k; i++) {
		auto m = std::max_element(v.begin(), v.end());

		int a(0), b(0), p(*m - 1);
		a = b = p / 2;
		if (p % 2 != 0) {
			b++;
		}

		v.erase(m);
		v.push_back(a);
		v.push_back(b);
	}

	std::cout << v[v.size() - 2] << '\n' << v[v.size() - 1] << '\n';
}
