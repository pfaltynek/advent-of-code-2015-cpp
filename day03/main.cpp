#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

std::map<long long, int> part1, part2;

void DeliverPresent(int x, int y, bool ispart1) {
	std::map<long long, int>::iterator it1;
	long long pos, tmp;

	pos = x;
	pos &= 0x00000000FFFFFFFF;
	tmp = y;
	tmp = tmp << 32;
	tmp &= 0xFFFFFFFF00000000;
	pos |= tmp;

	if (ispart1) {
		it1 = part1.find(pos);
		if (it1 != part1.end()) {
			part1[pos] = 1;
		} else {
			part1[pos]++;
		}
	} else {
		it1 = part2.find(pos);
		if (it1 != part2.end()) {
			part2[pos] = 1;
		} else {
			part2[pos]++;
		}
	}
}

int main(void) {
	std::ifstream input;
	std::string line, data;
	int result1 = 0, result2 = 0;
	int x1, y1, x2, y2, x3, y3;
	bool isSanta = true;

	std::cout << "=== Advent of Code - day 3 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open("input.txt", std::ifstream::in);
	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	part1.clear();
	part2.clear();
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
	x3 = 0;
	y3 = 0;
	DeliverPresent(x1, y1, true);
	DeliverPresent(x2, y2, false);
	DeliverPresent(x3, y3, false);
	data.clear();

	while (std::getline(input, line)) {
		data += line;
	}
	for (std::string::iterator it = data.begin(); it != data.end(); ++it) {
		switch (*it) {
			case 'v':
				y1++;
				DeliverPresent(x1, y1, true);
				if (isSanta) {
					y2++;
					DeliverPresent(x2, y2, false);
				} else {
					y3++;
					DeliverPresent(x3, y3, false);
				}
				break;
			case '^':
				y1--;
				DeliverPresent(x1, y1, true);
				if (isSanta) {
					y2--;
					DeliverPresent(x2, y2, false);
				} else {
					y3--;
					DeliverPresent(x3, y3, false);
				}
				break;
			case '>':
				x1++;
				DeliverPresent(x1, y1, true);
				if (isSanta) {
					x2++;
					DeliverPresent(x2, y2, false);
				} else {
					x3++;
					DeliverPresent(x3, y3, false);
				}
				break;
			case '<':
				x1--;
				DeliverPresent(x1, y1, true);
				if (isSanta) {
					x2--;
					DeliverPresent(x2, y2, false);
				} else {
					x3--;
					DeliverPresent(x3, y3, false);
				}
				break;

			case '\r':
			case '\n':
				break;
		}
		isSanta = !isSanta;
	}

	if (input.is_open()) {
		input.close();
	}

	result1 = part1.size();
	result2 = part2.size();
	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
