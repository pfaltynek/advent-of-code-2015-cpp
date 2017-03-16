#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

int main(void) {
	int result1, result2;
	std::ifstream input;
	std::string line, str;
	bool basement_entered = false;

	result1 = 0;
	result2 = 0;
	str.clear();

	std::cout << "=== Advent of Code - day 1 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open("input.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	while (std::getline(input, line)) {
		str += line;
	}

	if (input.is_open()) {
		input.close();
	}

	for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
		switch (*it) {
			case '(':
				result1++;
				break;
			case ')':
				result1--;
				break;
			case '\n':
			case '\r':
				break;
			default:
				std::cout << "Invalid character in input file.\n";
				return -1;
				break;
		}

		if (!basement_entered) {
			result2++;
			if (result1 < 0) {
				basement_entered = true;
			}
		}
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
