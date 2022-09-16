#include <iostream>

#define stars "* * * * * * * *"
#define starl "|||||||||||||||"
#define stare "               "

int main(int argc, char *argv[]) {
	for (int i = 0; i < 13; i++) {
		bool filled = i % 2 == 0;
		if (i < 6) {
			std::cout << stars;
		} else if (filled) {
			std::cout << starl;
		} else {
			std::cout << stare;
		}
		if (filled) {
			std::cout << "||||||||||||||||||||||||||||";
		} else {
			std::cout << "                            ";
		}
		std::cout << '\n';
	}
}
