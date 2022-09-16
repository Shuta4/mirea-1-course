#include <iostream>
#include <string>
#include <map>

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
		auto nextc = std::toupper(roman[i + 1]);
		if (values[c] < values[nextc]) {
			n -= values[c];
		} else {
			n += values[c];
		}
	}

	std::cout << "Number = " << n << '\n';
}
