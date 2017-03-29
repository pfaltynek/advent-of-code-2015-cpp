#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>

std::regex regex_rule("^(\\w+) would (lose|gain) (\\d+) happiness units by sitting next to (\\w+).$");

bool DecodeUnits(std::string line, std::string &who, std::string &next_to, int &units) {
	std::smatch sm;

	if (!regex_match(line, sm, regex_rule)) {
		return false;
	}
	who = sm.str(1);
	next_to = sm.str(4);
	units = atoi(sm.str(3).c_str());
	if (sm.str(2) == "lose") {
		units *= -1;
	}

	return true;
}

int CalculateHappiness(std::map<std::string, std::map<std::string, int>> units, std::vector<std::string> items) {
	int result = 0;

	if (items.size() <= 1) {
		return 0;
	}

	for (int i = 0; i < items.size() - 1; i++) {
		result += units[items[i]][items[i + 1]];
		result += units[items[i + 1]][items[i]];
	}

	result += units[items[0]][items[items.size() - 1]];
	result += units[items[items.size() - 1]][items[0]];

	return result;
}

int GetBestHappiness(std::map<std::string, std::map<std::string, int>> units, std::vector<std::string> items) {
	int result = 0, tmp;

	std::sort(items.begin(), items.end());

	do {
		tmp = CalculateHappiness(units, items);
		if (tmp > result) {
			result = tmp;
		}
	} while (std::next_permutation(items.begin(), items.end()));

	return result;
}

int main(void) {
	std::string who, next_to, line;
	int units, result1, result2, cnt;
	std::ifstream ifs;
	std::map<std::string, std::map<std::string, int>> happiness_map;
	std::vector<std::string> items;

	std::cout << "=== Advent of Code - day 13 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	result2 = result1 = cnt = 0;

	ifs.open("input.txt", std::ifstream::in);

	if (ifs.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	while (std::getline(ifs, line)) {
		cnt++;
		if (DecodeUnits(line, who, next_to, units)) {
			if (std::find(items.begin(), items.end(), who) == items.end()) {
				items.push_back(who);
			}
			if (std::find(items.begin(), items.end(), next_to) == items.end()) {
				items.push_back(next_to);
			}
			happiness_map[who][next_to] = units;
		} else {
			std::cout << "Error decoding input line " << cnt << std::endl;
			return -1;
		}
	}

	if (ifs.is_open()) {
		ifs.close();
	}

	result1 = GetBestHappiness(happiness_map, items);

	std::cout << "Result is " << result1 <<std::endl;
	std::cout << "--- part 2 ---" << std::endl;

	items.push_back("Jouza_Jouzovaty");
	result2 = GetBestHappiness(happiness_map, items);

	std::cout << "Result is " << result2 << std::endl;
}
