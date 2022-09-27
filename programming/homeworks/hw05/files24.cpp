#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>

struct ResultRow {
	std::string country;
	int golden;
	int silver;
	int bronze;
	int medals;
	int points;
};

int main(int argc, char *argv[]) {

	std::cout << "=== Olympics calculator ===\n"
			  << "Enter data in format:\n"
			  << "COUNTRY GOLDEN_MEDALS SILVER_MEDALS BRONZE_MEDALS\n"
			  << "To end input process enter empty line\n"
			  << "Enter data:\n";

	std::vector<ResultRow> results;

	int country_max_width = 7;

	std::string s;
	while (results.empty() || !s.empty()) {
		getline(std::cin, s);
		if (s.empty()) continue;

		std::stringstream ss(s);

		ResultRow row;
		ss >> row.country >> row.golden >> row.silver >> row.bronze;
		results.push_back(row);

		country_max_width = std::max(country_max_width, (int) row.country.size());
	}

	for (auto &row : results) {
		row.medals = row.golden + row.silver + row.bronze;
		row.points = row.golden * 7 + row.silver * 6 + row.bronze * 5;
	}

	std::sort(results.begin(), results.end(),
		[](ResultRow const &r1, ResultRow const &r2){
			return r1.country < r2.country;
		}
	);

	std::ofstream fo("olympics");
	if (!fo.is_open()) {
		std::cout << "Can not open file for writing\n";
		return 1;
	}
	fo << std::setw(country_max_width) << "Country" << '\t'
		<< std::setw(6) << "Golden" << '\t'
		<< std::setw(6) << "Silver" << '\t'
		<< std::setw(6) << "Bronze" << '\t'
		<< std::setw(6) << "Medals" << '\t'
		<< std::setw(6) << "Points" << "\t\n";

	std::cout << std::setw(country_max_width) << "Country" << '\t'
		<< std::setw(6) << "Golden" << '\t'
		<< std::setw(6) << "Silver" << '\t'
		<< std::setw(6) << "Bronze" << '\t'
		<< std::setw(6) << "Medals" << '\t'
		<< std::setw(6) << "Points" << "\t\n";

	for (auto const &row : results) {

		fo << std::setw(country_max_width) << row.country << '\t'
			<< std::setw(6) << row.golden << '\t'
			<< std::setw(6) << row.silver << '\t'
			<< std::setw(6) << row.bronze << '\t'
			<< std::setw(6) << row.medals << '\t'
			<< std::setw(6) << row.points << "\t\n";

		std::cout << std::setw(country_max_width) << row.country << '\t'
			<< std::setw(6) << row.golden << '\t'
			<< std::setw(6) << row.silver << '\t'
			<< std::setw(6) << row.bronze << '\t'
			<< std::setw(6) << row.medals << '\t'
			<< std::setw(6) << row.points << "\t\n";
	}
}
