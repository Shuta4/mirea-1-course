#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

int convert_to_10(std::string num, int base) {
	int result = 0;

	for (int i = 0; i < num.size(); i++) {
		auto c = num[i];
		int n = 0;
		if (std::isdigit(c)) {
			n = c - '0';
		} else {
			n = c - 'A' + 10;
		}

		if (n >= base) {
			return -1;
		}

		result += n * std::pow(base, num.size() - 1 - i);

	}
	return result;
}

std::string convert_from_10(int num, int base) {
	if (num == 0) {
		return "0";
	}

	std::string result;

	while(num > 0) {
		auto m = num % base;
		char c;
		if (m > 9) {
			c = 'A' + m - 10;
		} else {
			c = std::to_string(m)[0];
		}
		result += c;

		num = num / base;
	}

	std::reverse(result.begin(), result.end());

	return result;
}

int main(int argc, char *argv[]) {

	std::string number;
	int from_ns, to_ns;
	std::cout << "Enter number and its numbering system >> ";
	std::cin >> number >> from_ns;
	if (from_ns <= 1 || from_ns > 36) {
		std::cout << "Incorrect numbering system (must be 1 < ns <= 36)\n";
		return 1;
	}

	std::cout << "Enter numbering system to convert number to >> ";
	std::cin >> to_ns;
	if (to_ns <= 1 || to_ns > 36) {
		std::cout << "Incorrect numbering system (must be 1 < ns <= 36)\n";
		return 1;
	}

	auto num = convert_to_10(number, from_ns);
	if (num == -1) {
		std::cout << "Entered number is incorrect\n";
		return 1;
	}
	std::cout << convert_from_10(num, to_ns) << '\n';
}
