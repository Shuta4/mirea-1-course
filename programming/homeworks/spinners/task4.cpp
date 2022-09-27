#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main(int argc, char *argv[]) {
	unsigned int n(0);
	std::cout << "Enter N >> ";
	std::cin >> n;

	std::vector<int> places(n);
	for (int i = 0; i < n; i++) {
		std::cout << "Enter " << i + 1 << " empty place >> ";
		std::cin >> places[i];
	}

	if (n < 6) {
		std::cout << "Empties: 0\n";
		return 0;
	}

	std::sort(places.begin(), places.end());

	int empties(0);
	for (int i = 0; i < n - 3; i++) {

		if (places[i] <= 36
				&& places[i] % 4 == 1
				&& places[i + 1] % 4 == 2
				&& places[i + 2] % 4 == 3
				&& places[i + 3] % 4 == 0) {

			auto iter = std::find(places.begin(), places.end(), 54 - places[i + 3] / 4 * 2 + 1);
			if (iter == places.end()) {
				continue;
			}
			if (*std::next(iter) == *iter + 1) {
				empties++;
			}
		}
	}

	std::cout << "Empties: " << empties << '\n';
}
