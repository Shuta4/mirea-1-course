#include <ncurses.h>
#include <vector>
#include <map>
#include <random>
#include <cmath>

std::random_device rd;
std::mt19937 gen(rd());

struct Coords {
	unsigned int x; unsigned int y;
};

enum class InputType {
	none, up, down, left, right, enter, rotate, cancel
};

class Ship {
public:
	enum class Direction {
		left, right, up, down
	};

	explicit Ship(Coords c, Direction d, int s) {
		size = 1;
		setCoords(c);
		setDirection(d);
		setSize(s);
		for (unsigned int i = 0; i < size; i++) shooted_parts.push_back(false);
		killed = false;
	}

	void setCoords(Coords c) {
		coords = c;
	}

	void setDirection(Direction d) {
		dir = d;
	}

	void setSize(int s) {
		if (s > 4 || s < 1) {
			/* Impossible size */
			return;
		}
		size = s;
	}

	auto getCoords() {
		return coords;
	}

	auto getDirection() {
		return dir;
	}

	auto getSize() {
		return size;
	}

	auto shoot(unsigned int part) {
		if (killed) return; /* Can not overkill */
		if (part > size - 1) {
			return; /* Impossible part */
		}
		shooted_parts[part] = true;
		for (auto v : shooted_parts) {
			if (!v) {
				killed = false;
				break;
			}
			killed = true;
		}
	}

	const auto &getShootedParts() {
		return shooted_parts;
	}

	auto isKilled() {
		return killed;
	}

	auto getCells() {
		std::vector<std::pair<Coords, bool>> ship_cells;
		for (unsigned int j = 0; j < size; j++) {
			Coords c {coords.x, coords.y};
			switch (dir) {
				case Ship::Direction::left:
					c.x -= j;
					break;
				case Ship::Direction::right:
					c.x += j;
					break;
				case Ship::Direction::up:
					c.y -= j;
					break;
				case Ship::Direction::down:
					c.y += j;
					break;
				};
			ship_cells.emplace_back(c, shooted_parts[j]);
		}
		return ship_cells;
	}

private:
	Coords coords;
	Direction dir;
	unsigned int size;
	std::vector<bool> shooted_parts;
	bool killed;
};

class FieldState {
public:
	enum class State {
		prepairing, playing
	};

	static std::map<int, int> max_ships_with_size() {
		return {
			{1, 4},
			{2, 3},
			{3, 2},
			{4, 1}
		};
	}

	FieldState() {
		state = State::prepairing;
		ships = {};
		selected_ship = -1;
		selected_coords = {0, 0};
	}

	bool startPlaying() {
		for (auto const &it : max_ships_with_size()) {
			if (sized_ships_count[it.first] != it.second) {
				return false;
			}
		}
		state = State::playing;
		return true;
	}

	bool addShip(Ship s) {
		if (state != State::prepairing) return false;
		auto ship_size = s.getSize();
		if (sized_ships_count[ship_size] >= max_ships_with_size()[ship_size]) {
			return false; /* Can not add more ships with this size */
		}
		ships.push_back(s);
		sized_ships_count[ship_size]++;
		return true;
	}

	bool removeShip(unsigned int i) {
		if (state != State::prepairing) return false;
		if (i >= ships.size()) return false; /* Impossible index */
		auto ship_size = ships[i].getSize();
		sized_ships_count[ship_size]--;
		ships.erase(std::next(ships.begin(), i));
		if (selected_ship == (int) i) selected_ship = -1;
		return true;
	}

	auto &getShips() {
		return ships;
	}

	auto getState() {
		return state;
	}

	auto selectShip(unsigned int i) {
		selected_ship = i;
	}

	auto selectCell(Coords c) {
		selected_coords = c;
		selected_ship = -1;
	}

	auto getSelectedShip() {
		return selected_ship;
	}

	auto getSelectedCoords() {
		return selected_coords;
	}

	void shoot(Coords);

	auto isShooted(Coords c) {
		for (auto it : shooted_cells) {
			if (it.x == c.x && it.y == c.y) return true;
		}
		return false;
	}

	auto getShootedCells() {
		return shooted_cells;
	}

	auto allShipsKilled() {
		if (state == State::prepairing) return false;
		for (auto &ship : ships) {
			if (!ship.isKilled()) return false;
		}
		return true;
	}

	auto checkShipPosition(int ship_index) {
		auto &ship = ships[ship_index];
		auto our_cells = ship.getCells();
		for (unsigned int i = 0; i < ships.size(); i++) {
			if ((int) i == ship_index) continue;

			auto ship_cells = ships[i].getCells();
			for (unsigned int j = 0; j < ship_cells.size(); j++) {
				auto c = ship_cells[j].first;
				for (unsigned int k = 0; k < our_cells.size(); k++) {
					if ((c.x == our_cells[k].first.x + 1 ||
							c.x == our_cells[k].first.x - 1 ||
							c.x == our_cells[k].first.x) &&
							(c.y == our_cells[k].first.y + 1 ||
							c.y == our_cells[k].first.y - 1 ||
							c.y == our_cells[k].first.y)) {
						return false;
					}
				}
			}
		}
		return true;
	}

	auto placeShipsRandomly() {
		while (ships.size()) {
			removeShip(0);
		}
		unsigned int tries = 0;
		if (!placeShipRandomly(4, tries)) return false;
		tries = 0;
		if (!placeShipRandomly(3, tries)) return false;
		tries = 0;
		if (!placeShipRandomly(3, tries)) return false;
		tries = 0;
		if (!placeShipRandomly(2, tries)) return false;
		tries = 0;
		if (!placeShipRandomly(2, tries)) return false;
		tries = 0;
		if (!placeShipRandomly(2, tries)) return false;
		tries = 0;
		if (!placeShipRandomly(1, tries)) return false;
		tries = 0;
		if (!placeShipRandomly(1, tries)) return false;
		tries = 0;
		if (!placeShipRandomly(1, tries)) return false;
		tries = 0;
		if (!placeShipRandomly(1, tries)) return false;
		return true;
	}

private:
	bool placeShipRandomly(unsigned int, unsigned int &);

	Ship::Direction getRandomDirection() {
		using enum Ship::Direction;
		std::uniform_int_distribution<int> what_dir(0, 3);
		switch (what_dir(gen)) {
			case 0:
				return up;
				break;
			case 1:
				return right;
				break;
			case 2:
				return down;
				break;
			case 3:
				return left;
				break;
		}
		return up;
	}

	State state;
	std::vector<Ship> ships;
	std::map<int, int> sized_ships_count;
	int selected_ship;
	Coords selected_coords;
	std::vector<Coords> shooted_cells;
};

class FieldCell {
public:
	enum class Type {
		/*
		*        ┌───┐     ┏━━━━      ━━━━┓
		*        │   │     ┃   ┃      ┃   ┃
        *        └───┘     ┗━━━━      ━━━━┛
		*/
		empty, bordered, ship_left, ship_right,
		/*
		*  ┏━━━┓   ┃━━━┃    ━━━━━   ┃━━━┃   ┏━━━┓  like empty
		*  ┃   ┃   ┃   ┃    ┃   ┃   ┃   ┃   ┃   ┃  but with
        *  ┃━━━┃   ┗━━━┛    ━━━━━   ┃━━━┃   ┗━━━┛  X instead of *
		*/
		ship_up, ship_down, ship_h, ship_v, ship, hidden_ship
	};
	static const int width = 5;
	static const int height = 3;

	explicit FieldCell(Coords start, Type t, bool shooted, bool selected) {
		type = t;
		is_shooted = shooted;
		is_selected = selected;
		win = newwin(height, width, start.y, start.x);
	}

	auto setType(Type t) {
		type = t;
	}

	auto setShooted(bool v) {
		is_shooted = v;
	}

	auto setSelected(bool v) {
		is_selected = v;
	}

	auto isShooted() {
		return is_shooted;
	}

	auto render() {
		chtype ls, rs, ts, bs, tl, tr, bl, br;
		switch (type) {
			case Type::bordered:
				ls = rs = ACS_VLINE;
				ts = bs = ACS_HLINE;
				tl = ACS_ULCORNER;
				tr = ACS_URCORNER;
				bl = ACS_LLCORNER;
				br = ACS_LRCORNER;
				break;
			case Type::ship_left:
				ls = rs = ACS_VLINE;
				ts = bs = tr = br = ACS_HLINE;
				tl = ACS_ULCORNER;
				bl = ACS_LLCORNER;
				break;
			case Type::ship_right:
				ls = rs = ACS_VLINE;
				ts = bs = tl = bl = ACS_HLINE;
				tr = ACS_URCORNER;
				br = ACS_LRCORNER;
				break;
			case Type::ship_up:
				ls = rs = bl = br = ACS_VLINE;
				ts = bs = ACS_HLINE;
				tl = ACS_ULCORNER;
				tr = ACS_URCORNER;
				break;
			case Type::ship_down:
				ls = rs = tl = tr = ACS_VLINE;
				ts = bs = ACS_HLINE;
				bl = ACS_LLCORNER;
				br = ACS_LRCORNER;
				break;
			case Type::ship_h:
				ls = rs = ACS_VLINE;
				ts = bs = tl = tr = bl = br = ACS_HLINE;
				break;
			case Type::ship_v:
				ls = rs = tl = tr = bl = br = ACS_VLINE;
				ts = bs = ACS_HLINE;
				break;
			case Type::ship:
				ls = rs = ACS_VLINE;
				ts = bs = ACS_HLINE;
				tl = ACS_ULCORNER;
				tr = ACS_URCORNER;
				bl = ACS_LLCORNER;
				br = ACS_LRCORNER;
				break;
			default:
				ls = rs = ts = bs = tl = tr = bl = br = ' ';
		}

		auto is_ship = (type != Type::empty && type != Type::bordered) || type == Type::hidden_ship;

		if (is_ship && type != Type::hidden_ship) {
			wattron(win, A_BOLD);
			wattron(win, COLOR_PAIR(2));
		};
		if (is_selected) wattron(win, A_REVERSE);

		wborder(win, ls, rs, ts, bs, tl, tr, bl, br);
		wattroff(win, COLOR_PAIR(2));

		const int middle_y = (height - 1) / 2;
		for (int i = 1; i < width - 1; i++) mvwaddch(win, middle_y, i, ' ');

		if (is_shooted) {
			chtype ch = '*';
			if (is_ship) ch = 'X';
			mvwaddch(win, middle_y, (width - 1) / 2, ch);
		}

		/* Turn off all setted attrs for maintainability */
		wstandend(win);

		wrefresh(win);
	}

private:
	WINDOW *win;
	Type type;
	/* X for shooted ships and ● for shooted empty cells */
	bool is_shooted;
	/* Just changing color of symbols */
	bool is_selected;
};

class GameField {
public:
	static const int rows = 10;
	static const int columns = 10;
	static const int height = FieldCell::height * rows + 2;
	static const int width = FieldCell::width * columns + 2;

	explicit GameField(Coords start) {
		win = newwin(height, width, start.y, start.x);
		for (unsigned int i = 0; i < rows; i++) {
			cells.push_back({});

			for (unsigned int j = 0; j < columns; j++) {
				cells[i].push_back(FieldCell(
						{
							start.x + j * FieldCell::width + 1,
							start.y + i * FieldCell::height + 1
						},
						FieldCell::Type::empty,
						false, false
				));
			}
		}
	}

	auto render(bool active, FieldState &fs) {
		chtype ls, rs, ts, bs, tl, tr, bl, br;

		ls = rs = ACS_VLINE;
		ts = bs = ACS_HLINE;
		tl = ACS_ULCORNER;
		tr = ACS_URCORNER;
		bl = ACS_LLCORNER;
		br = ACS_LRCORNER;

		if (active) wattron(win, COLOR_PAIR(1));
		wborder(win, ls, rs, ts, bs, tl, tr, bl, br);
		wattroff(win, COLOR_PAIR(1));

		wrefresh(win);

		auto default_type = fs.getState() == FieldState::State::prepairing ?
			FieldCell::Type::bordered : FieldCell::Type::empty;

		auto selected_ship = fs.getSelectedShip();
		auto selected_c = fs.getSelectedCoords();

		for (unsigned int i = 0; i < rows; i++) {
			for (unsigned int j = 0; j < columns; j++) {
				cells[i][j].setType(default_type);
				cells[i][j].setSelected(
						selected_ship == -1 && i == selected_c.y && j == selected_c.x);
				cells[i][j].setShooted(false);
			}
		}

		for (auto c : fs.getShootedCells()) {
			cells[c.y][c.x].setShooted(true);
		}

		auto &ships = fs.getShips();
		for (int i = 0; i < (int) ships.size(); i++) {
			auto &ship = ships[i];
			auto dir = ship.getDirection();
			auto size = ship.getSize();
			auto shooted = ship.getShootedParts();

			auto ship_cells = ship.getCells();

			for (unsigned int j = 0; j < size; j++) {
				auto p = ship_cells[j];
				if (fs.getState() == FieldState::State::prepairing || ship.isKilled()) {
					if (size == 1) {
						cells[p.first.y][p.first.x].setType(FieldCell::Type::ship);
					} else {
						using enum FieldCell::Type;
						switch (dir) {
							case Ship::Direction::up:
								if (j == 0) {
									cells[p.first.y][p.first.x].setType(ship_down);
								} else if (j == size - 1) {
									cells[p.first.y][p.first.x].setType(ship_up);
								} else {
									cells[p.first.y][p.first.x].setType(ship_v);
								}
								break;
							case Ship::Direction::down:
								if (j == 0) {
									cells[p.first.y][p.first.x].setType(ship_up);
								} else if (j == size - 1) {
									cells[p.first.y][p.first.x].setType(ship_down);
								} else {
									cells[p.first.y][p.first.x].setType(ship_v);
								}
								break;
							case Ship::Direction::left:
								if (j == 0) {
									cells[p.first.y][p.first.x].setType(ship_right);
								} else if (j == size - 1) {
									cells[p.first.y][p.first.x].setType(ship_left);
								} else {
									cells[p.first.y][p.first.x].setType(ship_h);
								}
								break;
							case Ship::Direction::right:
								if (j == 0) {
									cells[p.first.y][p.first.x].setType(ship_left);
								} else if (j == size - 1) {
									cells[p.first.y][p.first.x].setType(ship_right);
								} else {
									cells[p.first.y][p.first.x].setType(ship_h);
								}
								break;
						}
					}
					if (selected_ship != -1)
						cells[p.first.y][p.first.x].setSelected(selected_ship == i);
				} else {
					cells[p.first.y][p.first.x].setType(FieldCell::Type::hidden_ship);
				}
				cells[p.first.y][p.first.x].setShooted(p.second);
			}
		}

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				cells[i][j].render();
			}
		}
	}

private:
	WINDOW *win;
	std::vector<std::vector<FieldCell>> cells;
};

auto processInput(GameField &gf, FieldState &fs,
		InputType input) {

	bool next = false;
	auto selected_ship = fs.getSelectedShip();
	if (fs.getState() == FieldState::State::prepairing && selected_ship != -1) {
		auto &ships = fs.getShips();
		auto &ship = ships[selected_ship];
		auto dir = ship.getDirection();
		auto c = ship.getCoords();
		auto size = ship.getSize();
		switch (input) {
			case InputType::up:
				if ((dir == Ship::Direction::up && c.y - size + 1 > 0) ||
						(dir != Ship::Direction::up && c.y > 0)) {
					c.y -= 1;
					ship.setCoords(c);
				}
				break;
			case InputType::down:
				if ((dir == Ship::Direction::down && c.y + size < GameField::rows) ||
						(dir != Ship::Direction::down && c.y < GameField::rows - 1)) {
					c.y += 1;
					ship.setCoords(c);
				}
				break;
			case InputType::left:
				if ((dir == Ship::Direction::left && c.x - size + 1 > 0) ||
						(dir != Ship::Direction::left && c.x > 0)) {
					c.x -= 1;
					ship.setCoords(c);
				}
				break;
			case InputType::right:
				if ((dir == Ship::Direction::right && c.x + size < GameField::columns) ||
						(dir != Ship::Direction::right && c.x < GameField::columns - 1)) {
					c.x += 1;
					ship.setCoords(c);
				}
				break;
			case InputType::rotate:
				switch (dir) {
					case Ship::Direction::up:
						if ((int) c.x + (int) size <= GameField::columns) {
							ship.setDirection(Ship::Direction::right);
						}
						break;
					case Ship::Direction::right:
						if ((int) c.y + (int) size <= GameField::rows) {
							ship.setDirection(Ship::Direction::down);
						}
						break;
					case Ship::Direction::down:
						if ((int) c.x - (int) size + 1 >= 0) {
							ship.setDirection(Ship::Direction::left);
						}
						break;
					case Ship::Direction::left:
						if ((int) c.y - (int) size + 1 >= 0) {
							ship.setDirection(Ship::Direction::up);
						}
						break;
					}
				break;
			case InputType::enter:
				next = fs.checkShipPosition(selected_ship);
				if (next) {
					fs.selectCell({0, 0});
				}
				break;
			case InputType::cancel:
				fs.removeShip(selected_ship);
			default:
				break;
		}
	} else {
		auto coords = fs.getSelectedCoords();
		switch (input) {
			case InputType::up:
				if (coords.y > 0) fs.selectCell({coords.x, coords.y - 1});
				break;
			case InputType::down:
				if (coords.y < GameField::rows - 1) fs.selectCell({coords.x, coords.y + 1});
				break;
			case InputType::left:
				if (coords.x > 0) fs.selectCell({coords.x - 1, coords.y});
				break;
			case InputType::right:
				if (coords.x < GameField::columns - 1) fs.selectCell({coords.x + 1, coords.y});
				break;
			case InputType::enter:
				if (fs.getState() == FieldState::State::prepairing) {
					auto ships = fs.getShips();
					for (unsigned int i = 0; i < ships.size(); i++) {
						auto ship_cells = ships[i].getCells();
						for (unsigned int j = 0; j < ship_cells.size(); j++) {
							auto c = ship_cells[j].first;
							if (c.x == coords.x && c.y == coords.y) {
								fs.selectShip(i);
								break;
							}
						}
					}
				} else {
					if (!fs.isShooted(coords)) {
						fs.shoot(coords);
						next = true;
					}
					for (auto &ship : fs.getShips()) {
						auto ship_cells = ship.getCells();
						for (unsigned int i = 0; i < ship_cells.size(); i++) {
							auto c = ship_cells[i].first;
							if (c.x == coords.x && c.y == coords.y) {
								ship.shoot(i);
								if (ship.isKilled()) {
									for (unsigned int j = 0; j < ship_cells.size(); j++) {
										auto sc = ship_cells[j].first;
										fs.shoot(Coords({sc.x + 1, sc.y}));
										fs.shoot(Coords({sc.x + 1, sc.y + 1}));
										fs.shoot(Coords({sc.x + 1, sc.y - 1}));
										fs.shoot(Coords({sc.x - 1, sc.y}));
										fs.shoot(Coords({sc.x - 1, sc.y + 1}));
										fs.shoot(Coords({sc.x - 1, sc.y - 1}));
										fs.shoot(Coords({sc.x, sc.y - 1}));
										fs.shoot(Coords({sc.x, sc.y + 1}));
									}
								}
								next = false;
							}
						}
					}
				}
				break;
			default:
				break;
		}
	}
	return next;
}

class Menu {
public:
	enum class Item { ship1, ship2, ship3, ship4, random, autoplay, start };

	explicit Menu(Coords start) {
		win = newwin(9, 12, start.y, start.x);
		selected = Item::ship1;
	}

	void render(bool active) {
		chtype ls, rs, ts, bs, tl, tr, bl, br;

		ls = rs = ACS_VLINE;
		ts = bs = ACS_HLINE;
		tl = ACS_ULCORNER;
		tr = ACS_URCORNER;
		bl = ACS_LLCORNER;
		br = ACS_LRCORNER;

		if (active) wattron(win, COLOR_PAIR(1));
		wborder(win, ls, rs, ts, bs, tl, tr, bl, br);
		wattroff(win, COLOR_PAIR(1));

		if (selected == Item::ship1) wattron(win, A_REVERSE);
		mvwprintw(win, 1, 1, "Ship #");
		wattroff(win, A_REVERSE);
		if (selected == Item::ship2) wattron(win, A_REVERSE);
		mvwprintw(win, 2, 1, "Ship ##");
		wattroff(win, A_REVERSE);
		if (selected == Item::ship3) wattron(win, A_REVERSE);
		mvwprintw(win, 3, 1, "Ship ###");
		wattroff(win, A_REVERSE);
		if (selected == Item::ship4) wattron(win, A_REVERSE);
		mvwprintw(win, 4, 1, "Ship ####");
		wattroff(win, A_REVERSE);
		if (selected == Item::random) wattron(win, A_REVERSE);
		mvwprintw(win, 5, 1, "Random");
		wattroff(win, A_REVERSE);
		if (selected == Item::autoplay) wattron(win, A_REVERSE);
		mvwprintw(win, 6, 1, "Autoplay");
		wattroff(win, A_REVERSE);
		if (selected == Item::start) wattron(win, A_REVERSE);
		mvwprintw(win, 7, 1, "Start");
		wattroff(win, A_REVERSE);

		wrefresh(win);
	}

	bool processInput(InputType input) {
		switch (input) {
			case InputType::down:
			case InputType::right:
				switch (selected) {
					case Item::ship1:
						selected = Item::ship2;
						break;
					case Item::ship2:
						selected = Item::ship3;
						break;
					case Item::ship3:
						selected = Item::ship4;
						break;
					case Item::ship4:
						selected = Item::random;
						break;
					case Item::random:
						selected = Item::autoplay;
						break;
					case Item::autoplay:
						selected = Item::start;
						break;
					case Item::start:
						break;
				};
				break;
			case InputType::up:
			case InputType::left:
				switch (selected) {
					case Item::ship1:
						break;
					case Item::ship2:
						selected = Item::ship1;
						break;
					case Item::ship3:
						selected = Item::ship2;
						break;
					case Item::ship4:
						selected = Item::ship3;
						break;
					case Item::random:
						selected = Item::ship4;
						break;
					case Item::autoplay:
						selected = Item::random;
						break;
					case Item::start:
						selected = Item::autoplay;
						break;
				};
				break;
			case InputType::enter:
				return true;
				break;
			default:
				break;
		}
		return false;
	}

	Item getSelected() {
		return selected;
	}

private:
	WINDOW *win;
	Item selected;
};


void FieldState::shoot(Coords c) {
	if (c.x < 0 || c.x > GameField::columns - 1 ||
			c.y < 0 || c.y > GameField::rows - 1) return;
	shooted_cells.push_back(c);
}

bool FieldState::placeShipRandomly(unsigned int size, unsigned int &tries) {
	auto dir = getRandomDirection();
	unsigned int left_offset(0), right_offset(0), top_offset(0), bot_offset(0);
	switch (dir) {
		case Ship::Direction::up:
			top_offset = size;
			break;
		case Ship::Direction::right:
			right_offset = size;
			break;
		case Ship::Direction::down:
			bot_offset = size;
			break;
		case Ship::Direction::left:
			left_offset = size;
			break;
	}

	std::uniform_int_distribution<unsigned int> x_where(
			left_offset, GameField::columns - 1 - right_offset);
	std::uniform_int_distribution<unsigned int> y_where(
			top_offset, GameField::rows - 1 - bot_offset);

	Ship s(Coords({x_where(gen), y_where(gen)}), dir, size);
	if (!addShip(s)) return false;
	if (!checkShipPosition(ships.size() - 1)) {
		tries++;
		if (tries >= 100) {
			return false;
		}
		removeShip(ships.size() - 1);
		placeShipRandomly(size, tries);
	};
	return true;
}

class StatusBar {
public:
	explicit StatusBar(Coords start) {
		width = COLS - start.x;
		win = newwin(1, width, start.y, start.x);
	}

	void print(const char *s) {
		mvwhline(win, 0, 0, ' ', width);
		mvwprintw(win, 0, 0, s);
		wrefresh(win);
	}

private:
	WINDOW *win;
	unsigned int width;
};

struct Autoplay {
	bool on;
	std::vector<Coords> last_shooted;
};

bool autoShoot(Autoplay &conf, FieldState &fs) {
	bool next = true;
	Coords coords({0, 0});

	if (conf.last_shooted.size() == 0) {
		std::uniform_int_distribution<unsigned int> x_where(0, GameField::columns - 1);
		std::uniform_int_distribution<unsigned int> y_where(0, GameField::rows - 1);

		while(true) {
			coords.x = x_where(gen);
			coords.y = y_where(gen);
			if (fs.isShooted(coords)) {
				continue;
			}
			break;
		}
	} else {
		if (conf.last_shooted.size() == 1) {
			std::uniform_int_distribution<unsigned int> dir(0, 3);

			while (true) {
				coords = conf.last_shooted[0];

				switch(dir(gen)) {
					case 0: /* Up */
						if (coords.y == 0) continue;
						coords.y = coords.y - 1;
						break;
					case 1: /* Right */
						if (coords.x == GameField::columns - 1) continue;
						coords.x = coords.x + 1;
						break;
					case 2: /* Down */
						if (coords.y == GameField::rows - 1) continue;
						coords.y = coords.y + 1;
						break;
					case 3: /* Left */
						if (coords.x == 0) continue;
						coords.x = coords.x - 1;
						break;
				}
				if (fs.isShooted(coords)) {
					continue;
				}
				break;
			}
		} else {
			std::uniform_int_distribution<unsigned int> dir(0, 1);
			std::uniform_int_distribution<unsigned int> what_el(0, conf.last_shooted.size() - 1);
			while (true) {
				coords = conf.last_shooted[what_el(gen)];

				auto coords1 = conf.last_shooted[0];
				auto coords2 = conf.last_shooted[1];
				auto d_coords = Coords({
						(unsigned int) std::abs((int) coords2.x - (int) coords1.x),
						(unsigned int) std::abs((int) coords2.y - (int) coords1.y)
					});

				unsigned int d_x = d_coords.x > 0 ? 1 : 0;
				unsigned int d_y = d_coords.y > 0 ? 1 : 0;

				switch(dir(gen)) {
					case 0: /* Inc */
						if (coords.y == 0) continue;
						coords.x = coords.x + d_x * 1;
						coords.y = coords.y + d_y * 1;
						break;
					case 1: /* Dec */
						if (coords.x == GameField::columns - 1) continue;
						coords.x = coords.x - d_x * 1;
						coords.y = coords.y - d_y * 1;
						break;
				}
				if (fs.isShooted(coords)) {
					continue;
				}
				break;
			}
		}
	}
	fs.selectCell(coords);
	fs.shoot(coords);
	for (auto &ship : fs.getShips()) {
		auto ship_cells = ship.getCells();
		for (unsigned int i = 0; i < ship_cells.size(); i++) {
			auto c = ship_cells[i].first;
			if (c.x == coords.x && c.y == coords.y) {
				ship.shoot(i);
				conf.last_shooted.push_back(coords);
				if (ship.isKilled()) {
					conf.last_shooted.clear();
					for (unsigned int j = 0; j < ship_cells.size(); j++) {
						auto sc = ship_cells[j].first;
						fs.shoot(Coords({sc.x + 1, sc.y}));
						fs.shoot(Coords({sc.x + 1, sc.y + 1}));
						fs.shoot(Coords({sc.x + 1, sc.y - 1}));
						fs.shoot(Coords({sc.x - 1, sc.y}));
						fs.shoot(Coords({sc.x - 1, sc.y + 1}));
						fs.shoot(Coords({sc.x - 1, sc.y - 1}));
						fs.shoot(Coords({sc.x, sc.y - 1}));
						fs.shoot(Coords({sc.x, sc.y + 1}));
					}
				}
				next = false;
			}
		}
	}
	return next;
}

int main() {
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	keypad(stdscr, true);
	if (!has_colors()) {
		printw("Your terminal does not support colors! Press any key to exit...");
		getch();
		endwin();
		return 1;
	}
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	refresh();

	mvprintw(1, 1, "Use WASD to move selection");
	mvprintw(2, 1, "TAB to switch between menu and field");
	mvprintw(3, 1, "SPACE to place or select ship and");
	mvprintw(4, 1, "C or BACKSPACE to cancel.");
	mvprintw(5, 1, "R to rotate ship.");

	mvprintw(7, 1, "1. Player 1. Place ships");
	mvprintw(8, 1, "2. Player 1. Click start");
	mvprintw(9, 1, "3. Player 2. Place ships");
	mvprintw(10, 1, "4. Player 2. Click start");
	mvprintw(11, 1, "5. Play game");

	mvprintw(13, 1, "Press any key to continue...");
	getch();

	FieldState player1_state;
	FieldState player2_state;
	Autoplay player1_auto;
	Autoplay player2_auto;
	bool player1_turn = true;
	bool menu_selected = true;

	GameField gf({1, 1});
	Menu menu({GameField::width + 2, 1});
	StatusBar status({0, 0});

	auto quit = false;
	while (!quit) {
		auto working_with_player1 = true;
		if ((player1_state.getState() == FieldState::State::playing &&
				player2_state.getState() == FieldState::State::prepairing) ||
				(player1_state.getState() == FieldState::State::playing && player1_turn)) {
			working_with_player1 = false;
		}
		if (working_with_player1) gf.render(!menu_selected, player1_state);
		else gf.render(!menu_selected, player2_state);
		menu.render(menu_selected);

		if ((working_with_player1 && player1_state.allShipsKilled()) ||
				(!working_with_player1 && player2_state.allShipsKilled())) {
			if (player1_turn) status.print("Player 1 WIN! Press q to exit.");
			else status.print("Player 2 WIN! Press q to exit.");

			quit = true;
			while (true) {
				auto ch = getch();
				if (ch == 'q' || ch == 'Q') break;
			}
			break;
		}

		if (player1_state.getState() == FieldState::State::prepairing)
			status.print("Player 1: prepairing");
		else if (player2_state.getState() == FieldState::State::prepairing)
			status.print("Player 2: prepairing");
		else if (player1_turn)
			status.print("Player 1: turn");
		else
			status.print("Player 2: turn");

		auto input = InputType::none;
		if ((player1_turn && !player1_auto.on) || (!player1_turn && !player2_auto.on)) {
			auto ch = getch();
			switch (ch) {
				case 'q':
				case 'Q':
					quit = true;
					break;
				case KEY_DOWN:
				case 'j':
				case 'J':
				case 's':
				case 'S':
					input = InputType::down;
					break;
				case KEY_UP:
				case 'k':
				case 'K':
				case 'w':
				case 'W':
					input = InputType::up;
					break;
				case KEY_LEFT:
				case 'h':
				case 'H':
				case 'a':
				case 'A':
					input = InputType::left;
					break;
				case KEY_RIGHT:
				case 'l':
				case 'L':
				case 'd':
				case 'D':
					input = InputType::right;
					break;
				case 'r':
				case 'R':
					input = InputType::rotate;
					break;
				case ' ':
				case '\n':
					input = InputType::enter;
					break;
				case 'c':
				case 'C':
				case 27:
				case KEY_BACKSPACE:
					input = InputType::cancel;
					break;
				case '\t':
					if (player2_state.getState() == FieldState::State::prepairing) {
						if ((working_with_player1 && player1_state.getSelectedShip() == -1) ||
								(!working_with_player1 && player2_state.getSelectedShip() == -1)) {
							menu_selected = !menu_selected;
						}
					}
					break;
				default:
					continue;
			}
		}
		if (quit) break;

		if (((player1_turn && player1_auto.on) || (!player1_turn && player2_auto.on)) &&
				player1_state.getState() == FieldState::State::playing &&
				player2_state.getState() == FieldState::State::playing &&
				input == InputType::none) {
			bool next = false;

			if (player1_turn) {
				next = autoShoot(player1_auto, player2_state);
				gf.render(!menu_selected, player2_state);
			} else {
				next = autoShoot(player2_auto, player1_state);
				gf.render(!menu_selected, player1_state);
			}
			if (working_with_player1) gf.render(!menu_selected, player1_state);
			else gf.render(!menu_selected, player2_state);

			if (player1_turn) status.print("Player 1: press any key");
			else status.print("Player 2: press any key");
			auto l_ch = getch();
			if (l_ch == 'q' || l_ch == 'Q') {
				quit = true;
				break;
			}
			if (next) {
				player1_turn = !player1_turn;
			}
		} else if (input != InputType::none) {
			bool next = false;
			if (menu_selected) {
				next = menu.processInput(input);
			} else {
				if (working_with_player1) next = processInput(gf, player1_state, input);
				else next = processInput(gf, player2_state, input);
			}
			if (next && menu_selected) {
				if (menu.getSelected() == Menu::Item::start) {
					if (working_with_player1) {
						if (player1_state.startPlaying()) {
							player1_turn = false;
						}
					} else {
						if (player2_state.startPlaying()) {
							player1_turn = true;
							menu_selected = false;
						}
					}
				} else if (menu.getSelected() == Menu::Item::random) {
					if (working_with_player1) {
						player1_state.placeShipsRandomly();
					} else {
						player2_state.placeShipsRandomly();
					}
				} else if (menu.getSelected() == Menu::Item::autoplay) {
					if (working_with_player1) {
						player1_auto.on = true;
						player1_state.placeShipsRandomly();
						player1_state.startPlaying();
						player1_turn = false;
					} else {
						player2_auto.on = true;
						player2_state.placeShipsRandomly();
						player2_state.startPlaying();
						player1_turn = true;
						menu_selected = false;
					}
				} else {
					menu_selected = false;
					unsigned int size = 0;
					switch (menu.getSelected()) {
						case Menu::Item::start:
						case Menu::Item::random:
						case Menu::Item::autoplay:
							break;
						case Menu::Item::ship1:
							size = 1;
							break;
						case Menu::Item::ship2:
							size = 2;
							break;
						case Menu::Item::ship3:
							size = 3;
							break;
						case Menu::Item::ship4:
							size = 4;
							break;
					}
					if (working_with_player1) {
						if (player1_state.addShip(Ship ({0, 0}, Ship::Direction::right, size)))
							player1_state.selectShip(player1_state.getShips().size() - 1);
						else menu_selected = true;
					} else {
						if (player2_state.addShip(Ship ({0, 0}, Ship::Direction::right, size)))
							player2_state.selectShip(player2_state.getShips().size() - 1);
						else menu_selected = true;
					}
				}
			} else if (next && player2_state.getState() == FieldState::State::playing) {
				if (working_with_player1) gf.render(!menu_selected, player1_state);
				else gf.render(!menu_selected, player2_state);

				if (player1_turn) status.print("Player 1: press any key");
				else status.print("Player 2: press any key");
				auto l_ch = getch();
				if (l_ch == 'q' || l_ch == 'Q') {
					quit = true;
					break;
				}
				player1_turn = !player1_turn;
			}
		}
	}

	endwin();
}
