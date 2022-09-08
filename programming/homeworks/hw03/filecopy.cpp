#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[])
{
	std::ofstream fo;
	fo.open("test");
	fo << "TEST FILE CONTENT";
	fo.close();

	std::ifstream fi;
	std::stringstream buf;
	fi.open("test");
	buf << fi.rdbuf();
	fi.close();

	std::cout << buf.str();

}
