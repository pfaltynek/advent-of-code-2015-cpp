#include <cstdio>
#include <iostream>

int main(void) {
	FILE* f;
	int c;
	int result1 = 0, result2 = 0;
	bool basement_entered = false;

	std::cout << "=== Advent of Code - day 1 ====" << std::endl;

	std::cout << "--- part 1 ---" << std::endl;

	f = fopen("input.txt", "r");
	if (f == NULL) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	c = fgetc(f);
	while (c != EOF) {
		switch (c) {
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
		c = fgetc(f);
	}

	if (f != NULL) {
		fclose(f);
		f = NULL;
	}
	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
