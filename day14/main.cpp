#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <string>

std::regex regex_rule("^(\\w+) can fly (\\d+) km/s for (\\d+) seconds, but then must rest for (\\d+) seconds.$");

const int RACE_TIME = 2503;

typedef struct {
	std::string name;
	int speed, fly_time, rest_time, time_remaining, distance, points;
	bool flying;
} REINDEER;

bool DecodeReindeer(std::string line, REINDEER &reindeer) {
	std::smatch sm;

	if (!regex_match(line, sm, regex_rule)) {
		return false;
	}
	reindeer.name = sm.str(1);
	reindeer.speed = atoi(sm.str(2).c_str());
	reindeer.fly_time = atoi(sm.str(3).c_str());
	reindeer.rest_time = atoi(sm.str(4).c_str());
	reindeer.time_remaining = reindeer.fly_time;
	reindeer.flying = true;
	reindeer.distance = 0;
	reindeer.points = 0;

	return true;
}

void CalculateRaceResults(std::vector<REINDEER> reindeers, int &result1, int &result2) {
	int distance = 0, points = 0;
	std::vector<int> leaders;

	for (int i = 0; i < RACE_TIME; i++) {
		distance = 0;
		leaders.clear();

		for (int j = 0; j < reindeers.size(); j++) {
			reindeers[j].time_remaining--;
			if (reindeers[j].flying) {
				reindeers[j].distance += reindeers[j].speed;
				if (reindeers[j].time_remaining == 0) {
					reindeers[j].flying = false;
					reindeers[j].time_remaining = reindeers[j].rest_time;
				}
			} else {
				if (reindeers[j].time_remaining == 0) {
					reindeers[j].flying = true;
					reindeers[j].time_remaining = reindeers[j].fly_time;
				}
			}
			if (reindeers[j].distance > distance) {
				leaders.clear();
				leaders.push_back(j);
				distance = reindeers[j].distance;
			} else if (reindeers[j].distance == distance) {
				leaders.push_back(j);
			}
		}
		for (int j = 0; j < leaders.size(); j++) {
			reindeers[leaders[j]].points++;
		}
	}

	for (int j = 0; j < reindeers.size(); j++) {
		if (reindeers[j].points > points) {
			points = reindeers[j].points;
		}
	}
	result1 = distance;
	result2 = points;
}

int main(void) {
	int units, result1, result2, cnt;
	std::ifstream ifs;
	std::vector<REINDEER> reindeers;
	std::string line;

	std::cout << "=== Advent of Code - day 14 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	result2 = result1 = cnt = 0;

	ifs.open("input.txt", std::ifstream::in);

	if (ifs.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	while (std::getline(ifs, line)) {
		cnt++;
		REINDEER reindeer;
		if (DecodeReindeer(line, reindeer)) {
			reindeers.push_back(reindeer);
		} else {
			std::cout << "Error decoding input line " << cnt << std::endl;
			return -1;
		}
	}

	if (ifs.is_open()) {
		ifs.close();
	}

	CalculateRaceResults(reindeers, result1, result2);

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
