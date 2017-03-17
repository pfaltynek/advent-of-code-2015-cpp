#include <cstdio>
#include <iostream>
#include "md5.h"


const std::string input = "bgvyzdsv";
char buffer[101];

int main(void) {
	int result1 = 0, result2 = 0, number = 0, count;
	int size;
	std::string hash;
	MD5 md5;

	std::cout << "=== Advent of Code - day 4 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	while ((result1 == 0) || (result2 == 0)) {
		sprintf(buffer, "%s%d", input.c_str(), number);
		hash = md5.digestString(buffer);

		if ((hash.substr(0,5) == "00000") && (result1 == 0)) {
			result1 = number;
		}
		if ((hash.substr(0,6) == "000000") && (result2 == 0)) {
			result2 = number;
		}

		number++;
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}

