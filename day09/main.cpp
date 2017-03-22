#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>

bool IsValidRouteInfo(std::string line, std::string &from, std::string &to, int &distance) {
	std::regex regex_route("^(\\w+) to (\\w+) = (\\d+)$");
	std::smatch sm;

	if (regex_match(line, sm, regex_route)) {
		from = sm.str(1);
		to = sm.str(2);
		distance = atoi(sm.str(3).c_str());
		return true;
	}
	return false;
}

void ExploreRoutes(std::map<std::map<std::string, int>>, std::vector<string>, int current_route, int &result1, int &result2) {
	if (sites.size()) {
		std::vector<std::string> new_sites(sites);

	} else {
		if (current_route < result1) {
			result1 = current_route;
		}
		if (current_route > result2) {
			result2 = current_route;
		}
	}
	std::vector<std::string> new_sites;
}

int main(void) {
	int result1 = 0, result2 = 0, cnt;
	std::ifstream input;
	std::string line;
	std::map<std::string, std::map<std::string, int>> map;
	std::vector<std::string> sites;

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
		int distance;
		std::string from, to;

		if (!IsValidRouteInfo(line, from, to, distance)) {
			std::cout << "Instruction invalid format at input line " << cnt << std::endl;
			return -1;
		}
		map[from][to] = distance;
		map[to][from] = distance;
		if (std::find(sites.begin(), sites.end(), from) == sites.end()) {
			sites.push_back(from);
		}
		if (std::find(sites.begin(), sites.end(), to) == sites.end()) {
			sites.push_back(to);
		}
	}

	if (input.is_open()) {
		input.close();
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
