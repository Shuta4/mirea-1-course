#include <iostream>
#include <string>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <vector>

int main(int argc, char *argv[]) {
	std::cout << "On each line enter numbers splitted by space (to stop enter empty line) >>\n";
	std::vector<std::vector<float>> numbers;
	std::string cn;
	int i = 0;
	while (numbers.empty() || !cn.empty()) {
		getline(std::cin, cn);
		if (cn.empty()) {
			break;
		}

		numbers.push_back({});
		std::stringstream ss(cn);
		float num;
		while(ss >> num) {
			numbers[i].push_back(num);
		};
		i++;
	}

	using pt = std::pair<int, float>;
	std::vector<pt> averages;

	for (int i = 0; i < numbers.size(); i++) {
		averages.push_back({
			i,
			std::accumulate(numbers[i].begin(), numbers[i].end(), 0) / numbers[i].size()
		});
	}

	std::sort(averages.begin(), averages.end(),
		[](const pt &x, const pt &y) {
    		return x.second > y.second;
		}
	);

	std::cout << "Result:\n";
	for (auto p : averages) {
		std::cout << p.second << ": ";
		for (auto n : numbers[p.first]) {
			std::cout << n << ' ';
		}
		std::cout << '\n';
	}
}
