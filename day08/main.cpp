#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

std::regex regex_string("^\"(.*)\"$");

bool IsHexNumber(std::string expression) {
	return expression.find_first_not_of("0123456789ABCDEFabcdef") == std::string::npos;
}

bool IsValidString(std::string line) {
	std::smatch sm;

	if (regex_match(line, sm, regex_string)) {
		return true;
	}
	return false;
}

int CalculatePart1(std::string line) {
	int len, i = 0;
	std::string tmp;
	std::smatch sm;

	regex_match(line, sm, regex_string);
	tmp = sm.str(1);
	len = tmp.size();

	while (i < tmp.size()) {
		if (tmp[i] != '\\') {
			i++;
		} else if ((i + 1) < tmp.size()) {
			i++;
			switch (tmp[i]) {
				case '\\':
				case '\"':
					i++;
					len--;
					break;
				case 'x':
					if ((i + 2) < tmp.size()) {
						if (IsHexNumber(tmp.substr(i + 1, 2))) {
							i += 3;
							len -= 3;
						}
					} else {
						i++;
					}
					break;
				default:
					i++;
					break;
			}
		}
	}

	return line.size() - len;
}

int CalculatePart2(std::string line) {
	int len = 2;

	for (std::string::iterator it = line.begin(); it != line.end(); ++it) {
		switch (*it) {
			case '\\':
			case '\"':
				len += 2;
				break;
			default:
				len++;
				break;
		}
	}

	return len - line.size();
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

		if (!IsValidString(line)) {
			std::cout << "Instruction invalid format at input line " << cnt << std::endl;
			return -1;
		}

		result1 += CalculatePart1(line);
		result2 += CalculatePart2(line);
	}

	if (input.is_open()) {
		input.close();
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
