#include <iostream>
#include <sstream>
#include <algorithm>

int main(int argc, char *argv[])
{
	std::string s = "HGIHSTHNKSHLRPJSRHLFGYKHJKAPOK";
	std::sort(s.begin(), s.end());
	std::cout << s;
}
