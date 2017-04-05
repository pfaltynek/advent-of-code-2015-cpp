#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

std::regex regex_rule("^([a-zA-Z]+) => ([a-zA-Z]+)$");

bool DecodeReplacement(std::string line, std::string &left, std::string &right) {
	std::smatch sm;

	if (!regex_match(line, sm, regex_rule)) {
		return false;
	}

	left = sm.str(1).c_str();
	right = sm.str(2).c_str();

	return true;
}

int main(void) {
	int result1, result2, cnt;
	std::ifstream ifs;
	std::string line, left, right, molecule;
	std::map<std::string, std::vector<std::string>> map;
	bool replacements_decoded = false;

	std::cout << "=== Advent of Code - day 19 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	result2 = result1 = cnt = 0;

	ifs.open("input.txt", std::ifstream::in);

	if (ifs.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	while (std::getline(ifs, line)) {
		cnt++;

		if (line.empty()) {
			replacements_decoded = true;
			continue;
		}

		if (replacements_decoded) {
			molecule = line;
			break;
		}

		if (DecodeReplacement(line, left, right)) {
			if (map.find(left) != map.end()) {
				map[left].push_back(right);
			} else {
				std::vector<std::string> new1;
				new1.push_back(right);
				map[left] = new1;
			}
		} else {
			std::cout << "Error decoding input line " << cnt << std::endl;
			return -1;
		}
	}

	if (ifs.is_open()) {
		ifs.close();
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
