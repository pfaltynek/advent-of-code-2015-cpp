#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>

std::regex regex_rule("^Sue (\\d+): (\\w+): (\\d+), (\\w+): (\\d+), (\\w+): (\\d+)$"); //Sue 1: cars: 9, akitas: 3, goldfish: 0

bool DecodeAuntSue(std::string line, std::map<std::string, int> &desc, int &aunt_idx) {
	std::smatch sm;

	desc.clear();

	if (!regex_match(line, sm, regex_rule)) {
		return false;
	}

	aunt_idx = atoi(sm.str(1).c_str());
	desc[sm.str(2)] = atoi(sm.str(3).c_str());
	desc[sm.str(4)] = atoi(sm.str(5).c_str());
	desc[sm.str(6)] = atoi(sm.str(7).c_str());

	return true;
}

bool CheckAuntPart1(std::map<std::string, int> sue, std::map<std::string, int> check) {

	for (std::map<std::string, int>::iterator it = check.begin(); it != check.end(); ++it) {
		if (sue[it->first] != it->second) {
			return false;
		}
	}
	return true;
}

bool CheckAuntPart2(std::map<std::string, int> sue, std::map<std::string, int> check) {

	for (std::map<std::string, int>::iterator it = check.begin(); it != check.end(); ++it) {
		if ((it->first == "cats") || (it->first == "trees")) {
			if (sue[it->first] >= it->second) {
				return false;
			}
		} else if ((it->first == "pomeranians") || (it->first == "goldfish")) {
			if (sue[it->first] <= it->second) {
				return false;
			}
		} else {
			if (sue[it->first] != it->second) {
				return false;
			}
		}
	}
	return true;
}

int main(void) {
	int result1, result2, cnt, idx;
	std::ifstream ifs;
	std::map<std::string, int> aunt;
	std::map<int, std::map<std::string, int>> aunts;
	std::string line;

	std::cout << "=== Advent of Code - day 16 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	result2 = result1 = -1;
	cnt = 0;

	ifs.open("input.txt", std::ifstream::in);

	if (ifs.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	while (std::getline(ifs, line)) {
		cnt++;

		if (DecodeAuntSue(line, aunt, idx)) {
			aunts[idx] = aunt;
		} else {
			std::cout << "Error decoding input line " << cnt << std::endl;
			return -1;
		}
	}

	if (ifs.is_open()) {
		ifs.close();
	}

	aunt.clear();
	aunt["children"] = 3;
	aunt["cats"] = 7;
	aunt["samoyeds"] = 2;
	aunt["pomeranians"] = 3;
	aunt["akitas"] = 0;
	aunt["vizslas"] = 0;
	aunt["goldfish"] = 5;
	aunt["trees"] = 3;
	aunt["cars"] = 2;
	aunt["perfumes"] = 1;

	for (std::map<int, std::map<std::string, int>>::iterator it = aunts.begin(); it != aunts.end(); ++it) {
		if (result1 < 0) {
			if (CheckAuntPart1(aunt, it->second)) {
				result1 = it->first;
			}
		}
		if (result2 < 0) {
			if (CheckAuntPart2(aunt, it->second)) {
				result2 = it->first;
			}
		}
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
