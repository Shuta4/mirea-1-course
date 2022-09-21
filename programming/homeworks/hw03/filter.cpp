#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[])
{
	std::string s;
	std::cout << "Enter some string >> ";
	std::getline(std::cin, s);

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
	std::getline(fi, s);
	fi.close();

	std::cout << "Filtered string: ";
	for (int i = 0; i < s.size(); i++) {
		auto c = s[i];
		if (std::isdigit(c)) {
			std::cout << c;
		} else if (i > 0 && std::isdigit(s[i - 1])) {
			std::cout << ' ';
		}
	}
	std::cout << '\n';
}
