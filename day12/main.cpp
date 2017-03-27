#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string>

void ExploreJSON(nlohmann::json &j, int &result1, int &result2) {
	/*if (j.is_string()) {

	} else if (j.is_number_integer()) {

	} else if ()*/
}

int main(void) {
	int result1 = 0, result2 = 0;
	std::ifstream i;
	nlohmann::json j;

	i.open("input.txt");

	i >> j;

	std::cout << "=== Advent of Code - day 12 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	if (i.is_open()) {
		i.close();
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
