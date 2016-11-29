//#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

const std::string turn_on = "turn on ";
const std::string turn_off = "turn off ";
const std::string toggle = "toggle ";
const std::string through = " through ";

int main(void) {
	int result1 = 0, result2 = 0, cnt;
	std::ifstream input;
	std::string line;
	unsigned char grid1[1000][1000];
	int grid2[1000][1000];

	std::cout << "=== Advent of Code - day 6 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open("input.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	memset(grid1, sizeof(grid1), 0);
	memset(grid2, sizeof(grid2), 0);

	cnt = 0;

	while (std::getline(input, line)) {
		int x1, y1, x2, y2, cmd, pos;
		std::string coord1, coord2;

		cnt++;
		// instruction parse
		if (line.find(turn_on) == 0) {
			cmd = 1;
			line = line.substr(turn_on.size());
		} else if (line.find(turn_off) == 0) {
			cmd = -1;
			line = line.substr(turn_off.size());
		} else if (line.find(toggle) == 0) {
			cmd = 0;
			line = line.substr(toggle.size());
		} else {
			std::cout << "Unknown instruction type at input line " << cnt
					  << std::endl;
			return -1;
		}
		pos = line.find(through);
		if (pos != std::string::npos) {
			coord1 = line.substr(0, pos);
			coord2 = line.substr(pos + through.size());
		} else {
			std::cout << "Unable to find coordinates at input line " << cnt
					  << std::endl;
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
