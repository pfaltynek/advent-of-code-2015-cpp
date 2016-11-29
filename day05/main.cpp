//#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

int main(void) {
	int result1 = 0, result2 = 0, len;
	std::ifstream input;
	std::string line;
	std::string vowels = "aeiou";

	std::cout << "=== Advent of Code - day 5 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open("input.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	while (std::getline(input, line)) {
		int vowels_cnt = 0;
		bool char_pair = false;
		int prev_char = -1;
		bool two_pairs = false;
		bool symetric_pair = false;

		// part1 checks:
		// if string does not contain any of the dirty substrings
		if ((line.find("ab") == std::string::npos) &&
			(line.find("cd") == std::string::npos) &&
			(line.find("pq") == std::string::npos) &&
			(line.find("xy") == std::string::npos)) {
			len = line.size();
			for (int i = 0; i < len; i++) {
				// check for character appearing twice in a row
				if (line[i] == prev_char) {
					char_pair = true;
				}
				prev_char = line[i];
				// check if contains three vowels
				if (vowels.find_first_of(line[i]) != std::string::npos) {
					vowels_cnt++;
				}
			}
			if ((vowels_cnt >= 3) && char_pair) {
				result1++;
			}
		}
		// part2 checks:
		for (int i = 0; i < (len - 2); i++) {
			// non overlaping twice appearation of letter pair
			if (line.find(line.substr(i, 2),i+2)!= std::string::npos){
				two_pairs = true;
			}
			// letter repeating with exactly one letter between them
			if (line[i] == line[i+2]) {
				symetric_pair = true;
			}
		}
		if (symetric_pair && two_pairs) {
			result2++;
		}
	}

	if (input.is_open()) {
		input.close();
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
