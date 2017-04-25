#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

const unsigned long long multiplier = 252533;
const unsigned long long divider = 33554393;
const unsigned long long first_code = 20151125;

const unsigned int target_row = 2947;
const unsigned int target_col = 3029;

int main(void) {
	unsigned long long result;
	unsigned int row, col;

	std::cout << "=== Advent of Code - day 25 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	row = col = 1;
	result = first_code;

	while ((row != target_row) || (col != target_col)) {
		if (--row == 0) {
			row = col + 1;
			col = 1;
		} else {
			col++;
		}
		result = (result * multiplier) % divider;
	}

	std::cout << "Result is " << result << std::endl;
}
