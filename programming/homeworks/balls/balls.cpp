#include <iostream>
#include <vector>

bool next_set(std::vector<int> &v, int n) {
	int j = n - 2;
	while (j != -1 && v[j] >= v[j + 1]) j--;
	if (j == -1) return false;

	int k = n - 1;
	while (v[j] >= v[k]) k--;
	std::swap(v[j], v[k]);

	int l = j + 1, r = n - 1;
	while (l < r) std::swap(v[l++], v[r--]);
	return true;
}

int main(int argc, char *argv[]) {
	int n;
	std::cout << "Enter n >> ";
	std::cin >> n;

	std::vector<int> v;
	for (int i = 0; i < n; i++) {
		v.push_back(i);
	}

	int res = 1;
	while (next_set(v, n)) {
		for (int i = 0; i < n; i++) {
			if (i == v[i]) {
				res++;
				break;
			}
		}
	}

	std::cout << "Reshuffles: " << res << '\n';

}
