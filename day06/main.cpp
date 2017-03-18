//#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

const std::string turn_on = "turn on ";
const std::string turn_off = "turn off ";
const std::string toggle = "toggle ";
const std::string through = " through ";

unsigned char grid1[1000][1000];
int grid2[1000][1000];

bool DecodeInstruction(std::string line, int &cmd, int &x1, int &y1, int &x2, int &y2) {
	std::regex regex_toggle("^toggle (\\d+),(\\d+) through (\\d+),(\\d+)$");
	std::regex regex_turn_off("^turn off (\\d+),(\\d+) through (\\d+),(\\d+)$");
	std::regex regex_turn_on("^turn on (\\d+),(\\d+) through (\\d+),(\\d+)$");
	std::smatch sm;

	if (regex_match(line, sm, regex_toggle)) {
		cmd = 0;
	} else if (regex_match(line, sm, regex_turn_on)) {
		cmd = 1;
	} else if (regex_match(line, sm, regex_turn_off)) {
		cmd = -1;
	} else {
		return false;
	}

	x1 = atoi(sm.str(1).c_str());
	y1 = atoi(sm.str(2).c_str());
	x2 = atoi(sm.str(3).c_str());
	y2 = atoi(sm.str(4).c_str());

	return true;
}

bool DecodeCoords(std::string coords, int &x, int &y) {
	std::string tmp;
	int pos;

	pos = coords.find(',');
	if (pos != std::string::npos) {
		tmp = coords.substr(0, pos);
		if (!tmp.size()) {
			return false;
		}
		x = atoi(tmp.c_str());

		tmp = coords.substr(pos + 1);
		if (!tmp.size()) {
			return false;
		}
		y = atoi(tmp.c_str());
	} else {
		return false;
	}
	return true;
}

int main(void) {
	int result1 = 0, result2 = 0, cnt;
	std::ifstream input;
	std::string line;

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

		if (!DecodeInstruction(line, cmd, x1, y1, x2, y2)) {
			std::cout << "Unknown instruction type at input line " << cnt << std::endl;
			return -1;
		}

		if ((x1 < 0) || (x1 > 999) || (y1 < 0) || (y1 > 999) || (x2 < 0) || (x2 > 999) || (y2 < 0) || (y2 > 999)) {
			std::cout << "Invalid coordinates at input line " << cnt << std::endl;
			return -1;
		}

		// instruction processing
		switch (cmd) {
			case -1: // turn off
				for (int x = x1; x <= x2; x++) {
					for (int y = y1; y <= y2; y++) {
						// part1
						grid1[x][y] = 0;
						// part2
						if (grid2[x][y] > 0) {
							grid2[x][y]--;
						}
					}
				}
				break;
			case 0: // toggle
				for (int x = x1; x <= x2; x++) {
					for (int y = y1; y <= y2; y++) {
						// part1
						grid1[x][y] ^= 1;
						// part2
						grid2[x][y] += 2;
					}
				}
				break;
			case 1: // turn on
				for (int x = x1; x <= x2; x++) {
					for (int y = y1; y <= y2; y++) {
						// part1
						grid1[x][y] = 1;
						// part2
						grid2[x][y]++;
					}
				}
				break;
		}
	}

	if (input.is_open()) {
		input.close();
	}

	for (size_t i = 0; i < 1000; i++) {
		for (size_t j = 0; j < 1000; j++) {
			result1 += grid1[i][j];
			result2 += grid2[i][j];
		}
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
