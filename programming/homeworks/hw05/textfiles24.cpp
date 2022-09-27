#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

int main(int argc, char *argv[]) {
	std::string s;
	std::string cs;
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

	std::ifstream fi;
	fi.open("test");
	if (!fi.is_open()) {
		std::cout << "Can not open file for reading\n";
		return 1;
	}

	std::map<char, bool> chars {
		{'B', true},
		{'C', true},
		{'D', true},
		{'F', true},
		{'G', true},
		{'H', true},
		{'J', true},
		{'K', true},
		{'L', true},
		{'M', true},
		{'N', true},
		{'P', true},
		{'Q', true},
		{'R', true},
		{'S', true},
		{'T', true},
		{'V', true},
		{'W', true},
		{'X', true},
		{'Z', true},
	};
	std::map<char, unsigned int> char_count;
	using pair_t = std::pair<char, unsigned int>;
	while (std::getline(fi, s)) {
		for (auto c : s) {
			auto uc = std::toupper(c);
			if (chars[uc]) {
				char_count[uc]++;
			}
		}
	}
	fi.close();

	auto c = std::min_element(
    	std::begin(char_count), std::end(char_count),
    	[] (const pair_t & p1, const pair_t & p2) {
        	return p1.second < p2.second;
    	}
	);

	std::cout << "least often consonant: " << c->first << '\n';
}
