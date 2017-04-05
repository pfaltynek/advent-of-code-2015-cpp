#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

//#define TEST 1

#if TEST
std::regex regex_rule("^[#\\.]{6}$");
#define WIDTH 6
#define HEIGHT 6
#define STEPS 4
#else
std::regex regex_rule("^[#\\.]{100}$");
#define WIDTH 100
#define HEIGHT 100
#define STEPS 100
#endif
#define SIZE (WIDTH * HEIGHT)

std::string light_map_init, light_map_current, light_map_next;

bool CheckLightsLineSize(std::string line) {
	std::smatch sm;

	if (!regex_match(line, sm, regex_rule)) {
		return false;
	}

	return true;
}

bool IsLightOn(int x, int y) {
	if ((x >= 0) && (x < WIDTH) && (y >= 0) && (y < HEIGHT)) {
		return light_map_current[(y * WIDTH) + x] == '#';
	}
	return false;
}

bool GetLightInfo(int x, int y, int &neighbors) {
	bool result = false;

	neighbors = 0;

	for (int xi = -1; xi <= 1; xi++) {
		for (int yi = -1; yi <= 1; yi++) {
			if (IsLightOn(x + xi, y + yi)) {
				if ((xi == 0) && (yi == 0)) {
					result = true;
				} else {
					neighbors++;
				}
			}
		}
	}

	return result;
}

void UpdateMap() {
	int around = 0;
	bool is_on = false;
	char light;

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			is_on = GetLightInfo(x, y, around);

			light = '.';

			if (is_on) {
				if ((around == 2) || (around == 3)) {
					light = '#';
				}
			} else {
				if (around == 3) {
					light = '#';
				}
			}
			light_map_next[(y * WIDTH) + x] = light;
		}
	}

	light_map_current = light_map_next;
}

int main(void) {
	int result1, result2, cnt, value;
	std::ifstream ifs;
	std::string line, light_map_init;

	std::cout << "=== Advent of Code - day 18 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	result2 = result1 = cnt = 0;

	light_map_init.clear();

#if TEST
	ifs.open("input-test1.txt", std::ifstream::in);
#else
	ifs.open("input.txt", std::ifstream::in);
#endif

	if (ifs.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	while (std::getline(ifs, line)) {
		cnt++;

		if (CheckLightsLineSize(line)) {
			light_map_init += line;
		} else {
			std::cout << "Error decoding input line " << cnt << std::endl;
			return -1;
		}
	}

	if (light_map_init.size() != WIDTH * HEIGHT) {
		std::cout << "Invalid size of input file.\n";
		return -1;
	}

	if (ifs.is_open()) {
		ifs.close();
	}

	light_map_current = light_map_init;
	light_map_next = light_map_current;

	for (int i = 0; i < STEPS; i++) {
		UpdateMap();
	}

	for (int i = 0; i < light_map_current.size(); i++) {
		if (light_map_current[i] == '#') {
			result1++;
		}
	}

	light_map_current = light_map_init;
	light_map_next = light_map_current;

	for (int i = 0; i < STEPS; i++) {
		UpdateMap();
		light_map_current[0] = '#';
		light_map_current[WIDTH - 1] = '#';
		light_map_current[SIZE - WIDTH] = '#';
		light_map_current[SIZE - 1] = '#';
	}

	for (int i = 0; i < light_map_current.size(); i++) {
		if (light_map_current[i] == '#') {
			result2++;
		}
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
