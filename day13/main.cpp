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

int main(void) {
	std::string who, next_to, line;
	int units, result1, result2, cnt;
	std::ifstream ifs;
	std::map<std::string, std::map<std::string, int>> map;

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

		} else {
			std::cout << "Error decoding input line " << cnt << std::endl;
			return -1;
		}
	}

	if (ifs.is_open()) {
		ifs.close();
	}
	std::cout << "Result is '" << result1 << "'" << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is '" << result2 << "'" << std::endl;
}
