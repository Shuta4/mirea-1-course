#include <iostream>
#include <fstream>
#include <vector>

int find_max(std::vector<int> const &numbers) {
	for (int i = 0; i < numbers.size() - 1; i++) {
		for (int j = numbers.size() - 1; j > i; j--) {
			auto ci = i;
			auto cj = j;
			while (ci < cj) {
				if (numbers[ci] != numbers[cj]) {
					break;
				}
				ci++;
				cj--;
			}
			if (ci < cj) {
				continue;
			}
			return j - i + 1;
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	unsigned int n;
	std::cout << "Enter N >> ";
	std::cin >> n;

	if (n < 2) {
		std::cout << "N can not be less then 2\n";
		return 1;
	}

	std::vector<int> numbers;
	for (int i = 1; i <= n; i++) {
		std::cout << "Enter " << i << " number >> ";
		int current;
		std::cin >> current;
		numbers.push_back(current);
	}

	std::ofstream fo;
	fo.open("test");
	if (!fo.is_open()) {
		std::cout << "Can not open file for writing\n";
		return 1;
	}
	for (auto n : numbers) {
		fo << n << '\n';
	}
	fo.close();

	std::cout << "Max length: " << find_max(numbers) << '\n';
	std::cout << "Content:\n";
	for (auto n: numbers) {
		std::cout << n << '\n';
	}
	return 0;
}
