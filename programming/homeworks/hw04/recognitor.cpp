#include <iostream>
#include <string>
#include <map>
#include <cmath>

int main(int argc, char *argv[]) {
	std::string roman;
	std::cout << "Enter Roman number >> ";
	std::cin >> roman;

	std::map<char, int> values {
		{'I', 1},
		{'V', 5},
		{'X', 10},
		{'L', 50},
		{'C', 100},
		{'D', 500},
		{'M', 1000},
	};

	int n = 0;
	for (int i = 0; i < roman.size(); i++) {
		auto c = std::toupper(roman[i]);
		auto val = values[c];
		for (int j = i + 1; j < roman.size(); j++) {
			auto nextc = std::toupper(roman[j]);
			if (j == i + 1 && val < values[nextc]) {
				val *= -1;
			} else if (std::abs(val) < values[nextc]) {
				std::cout << "This is incorrect Roman number\n";
				return 1;
			}
		}
		n += val;
	}

	std::cout << "Number = " << n << '\n';
}
