#include <iostream>
#include <vector>
#include <string>

/* Simple heap sort on c++ based on linux kernel implementation:
* https://github.com/torvalds/linux/blob/master/lib/sort.c#L192
*/
void sort(std::vector<int> &v) {
	int n = v.size(), a = v.size() / 2;

	if (!a) return; /* size < 2 || size == 0 */

	while(true) {
		int b, c, d;

		if (a) a--; /* Building heap: shift down --a */
		else if (n--) /* Sorting: Extract root to --n */
			std::swap(v[0], v[n]);
		else break; /* Sort complete */

		for (b = a; c = 2 * b + 1, (d = c + 1) < n;)
			b = v[c] > v[d] ? c : d;
		if (d == n) b = c;

		while (b != a && v[a] > v[b]) b = (b - 1) / 2;
		c = b;
		while (b != a) {
			b = (b - 1) / 2;
			std::swap(v[b], v[c]);
		}
	}
}

int main(int argc, char *argv[]) {
	std::vector<int> v;
	std::cout << "Enter some numbers to sort (to stop enter empty line):\n";
	while (true) {
		std::string s;
		getline(std::cin, s);
		if (s.empty()) break;

		v.push_back(stoi(s));
	}

	sort(v);

	std::cout << "Sorted numbers: ";
	for (auto n : v) {
		std::cout << n << ' ';
	}
	std::cout << '\n';
}
