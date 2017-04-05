#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

std::regex regex_rule("^(\\d+)$");
const int EGGNOG_AMOUNT = 150;

bool DecodeContainerSize(std::string line, int &value) {
	std::smatch sm;

	if (!regex_match(line, sm, regex_rule)) {
		return false;
	}

	value = atoi(sm.str(1).c_str());

	return true;
}

void ArrangeEggnog(const std::vector<int> &containers, int sum, int used_cont_cnt, int int_idx, int &combinations_cnt, int &min_comb_size, int &min_comb_cnt) {
	for (int i = int_idx; i < containers.size(); i++) {
		int new_sum = sum + containers[i];
		if (new_sum < EGGNOG_AMOUNT) {
			ArrangeEggnog(containers, new_sum, used_cont_cnt + 1, i + 1, combinations_cnt, min_comb_size, min_comb_cnt);
		} else if (new_sum == EGGNOG_AMOUNT) {
			combinations_cnt++;
			if (used_cont_cnt + 1 < min_comb_size) {
				min_comb_size = used_cont_cnt + 1;
				min_comb_cnt = 1;
			} else if (used_cont_cnt + 1 == min_comb_size) {
				min_comb_cnt++;
			}
		}
	}
}

int main(void) {
	int result1, result2, cnt, value;
	std::ifstream ifs;
	std::vector<int> containers, used_cont;
	std::string line;

	std::cout << "=== Advent of Code - day 16 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	result2 = result1 = cnt = 0;

	ifs.open("input.txt", std::ifstream::in);

	if (ifs.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	while (std::getline(ifs, line)) {
		cnt++;

		if (DecodeContainerSize(line, value)) {
			containers.push_back(value);
		} else {
			std::cout << "Error decoding input line " << cnt << std::endl;
			return -1;
		}
	}

	if (ifs.is_open()) {
		ifs.close();
	}

	std::sort(containers.begin(), containers.end());
	std::reverse(containers.begin(), containers.end());

	cnt = containers.size() + 1;
	used_cont.clear();

	ArrangeEggnog(containers, 0, 0, 0, result1, cnt, result2);

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
