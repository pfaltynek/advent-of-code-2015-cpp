#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <string>

std::regex regex_rule("^(\\w+): capacity (-?\\d+), durability (-?\\d+), flavor (-?\\d+), texture (-?\\d+), calories (-?\\d+)$");

const int TEASPOONS_MAX = 100;

typedef struct {
	std::string name;
	int capacity, durability, flavor, texture, calories;
} INGREDIENCE;

bool DecodeIngredience(std::string line, INGREDIENCE &ingredience) {
	std::smatch sm;

	if (!regex_match(line, sm, regex_rule)) {
		return false;
	}
	ingredience.name = sm.str(1);
	ingredience.capacity = atoi(sm.str(2).c_str());
	ingredience.durability = atoi(sm.str(3).c_str());
	ingredience.flavor = atoi(sm.str(4).c_str());
	ingredience.texture = atoi(sm.str(5).c_str());
	ingredience.calories = atoi(sm.str(6).c_str());

	return true;
}



int main(void) {
	int units, result1, result2, cnt;
	std::ifstream ifs;
	std::vector<INGREDIENCE> ingrediences;
	std::string line;

	std::cout << "=== Advent of Code - day 15 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	result2 = result1 = cnt = 0;

	ifs.open("input.txt", std::ifstream::in);

	if (ifs.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	while (std::getline(ifs, line)) {
		cnt++;
		INGREDIENCE ingredience;
		if (DecodeIngredience(line, ingredience)) {
			ingrediences.push_back(ingredience);
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
