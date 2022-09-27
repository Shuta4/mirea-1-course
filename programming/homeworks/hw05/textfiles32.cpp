#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

char make_shift(int const& shift, char const& first, int const& count, char const& c) {
	auto shifted = (c - first + shift) % count;
	if (shifted < 0) {
		return first + count + shifted;
	}
	return first + shifted;
}

char shift_char(int const& shift, char const& c) {
	if (std::isdigit(c)) {
		return make_shift(shift, '0', 10, c);
	} else if (std::isalpha(c)) {
		if (std::toupper(c) == c) {
			return make_shift(shift, 'A', 26, c);
		} else {
			return make_shift(shift, 'a', 26, c);
		}
	}
	return c;
}

int main(int argc, char *argv[]) {
	std::string s("");
	std::string cs("");
	std::cout << "Enter content of file >>\n";
	while (s.empty() || !cs.empty()) {
		getline(std::cin, cs);
		s += cs + '\n';
	}

	std::ofstream fo;
	fo.open("test");
	if (!fo.is_open()) {
		std::cout << "Can not open file for writing\n";
		return 1;
	}
	fo << s;
	fo.close();

	int shift;
	std::cout << "Enter encryption shift >> ";
	std::cin >> shift;

	std::ifstream fi;
	fi.open("test");
	if (!fi.is_open()) {
		std::cout << "Can not open file for reading\n";
		return 1;
	}

	fo.open("encrypted");
	if (!fo.is_open()) {
		std::cout << "Can not open file for writing encrypted text\n";
		return 1;
	}

	while (std::getline(fi, s)) {
		std::string encrypted;
		for (auto c : s) {
			encrypted += shift_char(shift, c);
		}
		fo << encrypted << '\n';
	}
	fi.close();
	fo.close();
}
