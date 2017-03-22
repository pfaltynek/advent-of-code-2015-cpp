#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>



bool IsValidRouteInfo(std::string line, std::string &from, std::string &to, int &distance) {
	std::regex regex_route("^(\\w+) to (\\w+) = (\\d+)$");
	std::smatch sm;

	if (regex_match(line, sm, regex_route)) {
		from = sm.str(1);
		to = sm.str(2);
		distance = atoi(sm.str(3).c_str());
		return true;
	}
	return false;
}

int main(void) {
	int result1 = 0, result2 = 0, cnt;
	std::ifstream input;
	std::string line;

	std::cout << "=== Advent of Code - day 8 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open("input.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	cnt = 0;

	while (std::getline(input, line)) {
		cnt++;
		int distance;
		std::string from, to;

		if (!IsValidRouteInfo(line, from, to, distance)) {
			std::cout << "Instruction invalid format at input line " << cnt << std::endl;
			return -1;
		}

	}

	if (input.is_open()) {
		input.close();
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
