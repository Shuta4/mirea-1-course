#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[])
{
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
	std::cout << "Content of file:\n";
	while (std::getline(fi, s)) {
		std::cout << s << '\n';
	}
	fi.close();
}
