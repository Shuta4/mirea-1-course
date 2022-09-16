#include <iostream>
#include <vector>
#include <cmath>

#define MATRIX(T) std::vector<std::vector<T>>

int main(int argc, char *argv[]) {

	MATRIX(float) sales {
		{5, 2, 0, 10},
		{3, 5, 2, 5},
		{20, 0, 0, 0},
	};

	MATRIX(float) prices {
		{1.2, 0.5},
		{2.8, 0.4},
		{5, 1},
		{2, 1.5},
	};

	MATRIX(float) c;

	for (int i = 0; i < sales.size(); i++) {
		c.push_back({});
		for (int j = 0; j < prices[0].size(); j++) {
			float mul = 0;
			for (int q = 0; q < sales[i].size(); q++) {
				mul += sales[i][q] * prices[q][j];
			}
			c[i].push_back(mul);
		}
	}

	std::cout << "Matrix C:\n";
	for (int i = 0; i < c.size(); i++) {
		for (int j = 0; j < c[i].size(); j++) {
			std::cout << c[i][j] << ' ';
		}
		std::cout << '\n';
	}

	float max_income = 0;
	float min_income = INFINITY;
	float max_com = 0;
	float min_com = INFINITY;
	float full_income = 0;
	float full_com = 0;
	float full_money = 0;

	for (int i = 0; i < c.size(); i++) {
		auto current_income = c[i][0];
		auto current_com = c[i][1];

		max_income = std::max(current_income, max_income);
		min_income = std::min(current_income, min_income);

		max_com = std::max(current_com, max_com);
		min_com = std::min(current_com, min_com);

		full_income += current_income;
		full_com += current_com;
	}

	full_money = full_income + full_com;

	std::cout << "\nAnswers:\n"
		<< "1.1 Max income      : " << max_income << '\n'
		<< "1.2 Min income      : " << min_income << '\n'
		<< "2.1 Max commission  : " << max_com << '\n'
		<< "2.2 Min commission  : " << min_com << '\n'
		<< "3.  Full income     : " << full_income << '\n'
		<< "4.  Full commission : " << full_com << '\n'
		<< "5.  Full money      : " << full_money << '\n';
}
