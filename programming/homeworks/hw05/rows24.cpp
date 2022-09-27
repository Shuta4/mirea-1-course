#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>

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
	std::cout << "On each line enter one number in 7 numbering system (to stop enter empty line) >>\n";
	std::vector<std::string> numbers7;
	std::string cn;
	while (numbers7.empty() || !cn.empty()) {
		getline(std::cin, cn);
		if (!cn.empty()) {
			numbers7.push_back(cn);
		}
	}

	std::vector<std::string> numbers3;
	for (auto n7 : numbers7) {
		auto num = convert_to_10(n7, 7);
		if (num == -1) {
			std::cout << "Entered number '" << n7 << "' is incorrect\n";
			return 1;
		}
		numbers3.push_back(convert_from_10(num, 3));
	}

	std::cout << "Numbers in 3 numbering system:\n";
	for (auto n3 : numbers3) {
		std::cout << n3 << '\n';
	}
}
