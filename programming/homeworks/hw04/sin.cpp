#include <iostream>
#include <cmath>
#include <ncurses.h>

#define CENTER_CHAR '+'
#define LINES_HOR_CHAR '-'
#define LINES_VER_CHAR '|'
#define GRAPH_CHAR '*'

int main(int argc, char *argv[]) {
	initscr();
	noecho();
	cbreak();
	curs_set(0);

	auto center_x = COLS / 2;
	auto center_y = LINES / 2;

	for (int y = 0; y < LINES; y++) {
		mvaddch(y, center_x, LINES_VER_CHAR);
	}
	for (int x = 0; x < COLS; x++) {
		mvaddch(center_y, x, LINES_HOR_CHAR);
	}
	mvaddch(center_y, center_x, CENTER_CHAR);

	for (int x = 0; x < COLS; x++) {
		for (int y = 0; y < LINES; y++) {
			float px = (center_x - x);
			float b = LINES / 3;
			float c = COLS / 13;
			float py = b * std::sin(px / c);
			if (std::abs(py - center_y + y) < 1) {
				mvaddch(y, x, GRAPH_CHAR);
			}
		}
	}

	refresh();
	while(auto c = getch()) {
		if (c == 'q') break;
	};
	endwin();
}
