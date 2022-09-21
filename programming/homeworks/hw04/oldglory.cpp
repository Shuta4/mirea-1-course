#include <iostream>

#define STAR_CHAR '*'
#define FILLED_CHAR '|'
#define UNFILLED_CHAR ' '

int main(int argc, char *argv[]) {
	for (int i = 0; i < 13; i++) {
		bool filled_line = i % 2 == 0;

		for (int j = 0; j < 42; j++) {
			bool is_line = i >= 6 || j >= 8 * 2 - 1;
			bool is_star = !is_line && j % 2 == 0;

			if (is_line && filled_line) {
				std::cout << FILLED_CHAR;
			} else if (!filled_line && is_line || !is_star) {
				std::cout << UNFILLED_CHAR;
			} else if (is_star) {
				std::cout << STAR_CHAR;
			}
		}
		std::cout << '\n';
	}
}
