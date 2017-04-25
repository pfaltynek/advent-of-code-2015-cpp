#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

bool DecodeWeight(std::string line, int &weight) {
	std::smatch sm;
	std::regex regex_rule("^(\\d+)$");

	if (regex_match(line, sm, regex_rule)) {
		weight = atoi(sm.str(1).c_str());
		return true;
	}

	return false;
}

bool IsAnyPackageUnarranged(std::map<int, int> &usage_map) {
	for (auto it = usage_map.begin(); it != usage_map.end(); ++it) {
		if (!it->second) {
			return true;
		}
	}

	return false;
}

bool ArrangeRestPackages(std::vector<int> &weights, std::map<int, int> &usage_map, int level, int curr_sum, int target_sum) {
	for (size_t i = 0; i < weights.size(); i++) {
		if (usage_map[weights[i]]) {
			continue;
		}

		int new_sum = curr_sum + weights[i];

		usage_map[weights[i]] = level;

		if (new_sum < target_sum) {
			if (ArrangeRestPackages(weights, usage_map, level, new_sum, target_sum)) {
				return true;
			}
		} else if (new_sum == target_sum) {
			return true;
		}

		usage_map[weights[i]] = 0;
	}

	return false;
}

bool CheckRestPackagesArrangement(std::vector<int> &weights, std::map<int, int> &usage_map, int target_sum) {
	int level = 2;
	while (IsAnyPackageUnarranged(usage_map)) {
		if (!ArrangeRestPackages(weights, usage_map, level, 0, target_sum)) {
			return false;
		}
		level++;
	}

	return true;
}

void ArrangePackages(std::vector<int> &weights, std::map<int, int> &usage_map, int start_idx, int curr_sum, int curr_cnt, unsigned long long curr_qe, int target_sum, int &cnt, unsigned long long &qe) {
	if (cnt < curr_cnt) {
		return;
	}

	for (size_t i = start_idx; i < weights.size(); i++) {
		int new_sum = curr_sum + weights[i];
		int new_cnt = curr_cnt + 1;
		unsigned long long new_qe = curr_qe * weights[i];

		usage_map[weights[i]] = 1;

		if (new_sum < target_sum) {
			ArrangePackages(weights, usage_map, i + 1, new_sum, new_cnt, new_qe, target_sum, cnt, qe);
		} else if (new_sum == target_sum) {
			std::map<int, int> new_usage_map(usage_map);

			if (CheckRestPackagesArrangement(weights, new_usage_map, target_sum)) {
				if ((new_cnt < cnt) || ((new_cnt == cnt) && (new_qe < qe))) {
					cnt = new_cnt;
					qe = new_qe;
				}
			}
		}

		usage_map[weights[i]] = 0;
	}
}

int main(void) {
	unsigned long long result1, result2, sum;
	int cnt, weight;
	std::ifstream ifs;
	std::string line;
	std::vector<int> weights;
	std::map<int, int> map;

	std::cout << "=== Advent of Code - day 24 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	result1 = result2 = cnt = sum = 0;
	result1--;
	result2--;

	weights.clear();
	map.clear();

	ifs.open("input.txt", std::ifstream::in);

	if (ifs.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	while (std::getline(ifs, line)) {
		cnt++;

		if (DecodeWeight(line, weight)) {
			weights.push_back(weight);
			map[weight] = 0;
			sum += weight;
		} else {
			std::cout << "Error decoding input line " << cnt << std::endl;
			return -1;
		}
	}

	if (ifs.is_open()) {
		ifs.close();
	}

	cnt = weights.size();

	std::sort(weights.begin(), weights.end());
	std::reverse(weights.begin(), weights.end());

	ArrangePackages(weights, map, 0, 0, 0, 1, sum / 3, cnt, result1);

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;

	ArrangePackages(weights, map, 0, 0, 0, 1, sum / 4, cnt, result2);

	std::cout << "Result is " << result2 << std::endl;
}
