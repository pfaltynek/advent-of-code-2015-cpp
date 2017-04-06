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

int SolvePart1(std::string molecule, std::map<std::string, std::vector<std::string>> replacements) {
	std::map<std::string, int> distinct;
	size_t last_pos = 0;

	for (std::map<std::string, std::vector<std::string>>::iterator it = replacements.begin(); it != replacements.end(); ++it) {
		last_pos = molecule.find(it->first, 0);
		while (last_pos != std::string::npos) {
			for (int i = 0; i < it->second.size(); i++) {
				std::string tmp = molecule;
				tmp.replace(last_pos, it->first.size(), it->second[i]);

				distinct[tmp]++;
			}
			last_pos = molecule.find(it->first, last_pos + 1);
		}
	}

	return distinct.size();
}

void SolvePart2(std::string &molecule, int steps, std::map<std::string, std::string> &replacements, int &result) {
	steps++;

	if (molecule == "e") {
		if (steps < result) {
			result = steps;
		}
		return;
	} else if (steps >= result) {
		return;
	}
	for (std::map<std::string, std::string>::iterator it = replacements.begin(); it != replacements.end(); ++it) {
		size_t pos = 0;
		pos = molecule.find(it->first, pos);
		while (pos != std::string::npos) {
			molecule.replace(pos, it->first.size(), it->second);
			SolvePart2(molecule, steps, replacements, result);
			molecule.replace(pos, it->second.size(), it->first);
			pos = molecule.find(it->first, pos + 1);
		}
	}
}

int main(void) {
	int result1, result2, cnt;
	std::ifstream ifs;
	std::string line, left, right, molecule;
	std::map<std::string, std::vector<std::string>> map;
	std::map<std::string, std::string> rev_map;
	bool replacements_decoded = false;

	std::cout << "=== Advent of Code - day 19 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	result1 = cnt = 0;
	result2 = INT_MAX;

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
			rev_map[right] = left;
		} else {
			std::cout << "Error decoding input line " << cnt << std::endl;
			return -1;
		}
	}

	if (ifs.is_open()) {
		ifs.close();
	}

	result1 = SolvePart1(molecule, map);

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;

	SolvePart2(molecule, 0, rev_map, result2);

	std::cout << "Result is " << result2 << std::endl;
}
