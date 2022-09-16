#include <iostream>
#include <algorithm>
#include <string>

int main(int argc, char *argv[])
{
	std::string s;
	std::cout << "Enter some string >> ";
	std::getline(std::cin, s);

	if (s.size() < 30) {
		std::cout << "You entered less then 30 symbols\n";
		return 1;
	} else if (s.size() > 30) {
		s = s.substr(0, 30);
	}

	for (int i = 0; i < s.size() - 1; i++) {
		for (int j = 0; j < s.size() - 1; j++ ) {
			if (s[j] > s[j + 1]) {
				std::swap(s[j], s[j + 1]);
			}
		}
	}
	std::cout << "Sorted string: " << s << '\n';
}
