#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

int main(void) {
	std::ifstream input;
	int result1 = 0, result2 = 0;
	std::string line;

	char buff[101], *ptr, *pnum;
	int cnt = 0;

	std::cout << "=== Advent of Code - day 2 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open("input.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	while (std::getline(input, line)) {
		int dims[3], idx = 0, tmp;
		std::regex regex_dimensions("^(\\d+)x(\\d+)x(\\d+)$");
		std::smatch sm;

		cnt++;

		if (!regex_match(line, sm, regex_dimensions)) {
			std::cout << "Invalid input format at line " << cnt << std::endl;
			return -1;
		}

		dims[0] = atoi(sm.str(1).c_str());
		dims[1] = atoi(sm.str(2).c_str());
		dims[2] = atoi(sm.str(3).c_str());

		if (dims[0] > dims[1]) {
			tmp = dims[1];
			dims[1] = dims[0];
			dims[0] = tmp;
		}
		if (dims[1] > dims[2]) {
			tmp = dims[2];
			dims[2] = dims[1];
			dims[1] = tmp;
		}
		result1 += (2 * (dims[0] * dims[1])) + (2 * (dims[0] * dims[2])) +
				   (2 * (dims[1] * dims[2])) + (dims[0] * dims[1]);
		result2 +=
			(2 * dims[0]) + (2 * dims[1]) + (dims[0] * dims[1] * dims[2]);
	}

	if (input.is_open()) {
		input.close();
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
