#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[])
{
	std::ofstream fo;
	fo.open("test");
	fo << "lhl945j4o5l9ujlhjl49hjlisujhs9tihohj6h9it9ijd6uj";
	fo.close();

	std::ifstream fi;
	std::stringstream buf;
	fi.open("test");
	buf << fi.rdbuf();
	fi.close();

	std::string s = buf.str();

	for (auto c : s) {
		if (c >= '0' && c <= '9') {
			std::cout << c;
		}
	}

	std::cout << '\n';
}
