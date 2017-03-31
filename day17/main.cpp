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

void ArrangeEggnog(std::vector<int> containers, std::vector<int> used_cont_idxs, int sum, int &combinations, int &min_value, int &min_count) {
	for (std::vector<int>::iterator it = free_cont.begin(); it != free_cont.end(); ++it) {
		int new_sum = sum + *it;

		if (new_sum < EGGNOG_AMOUNT) {
			std::vector<int> new_used_cont(used_cont);
			std::vector<int> new_free_cont(free_cont);

			new_used_cont.push_back(*it);
			free_cont.erase(it);
			free_cont.swap(new_free_cont);
			ArrangeEggnog(new_used_cont, new_free_cont, new_sum, combinations, min_value, min_count);
		} else if (new_sum == EGGNOG_AMOUNT) {
			combinations++;
			if (used_cont.size() + 1 < min_value) {
				min_value = used_cont.size() + 1;
				min_count = 1;
			} else if (used_cont.size() + 1 == min_value) {
				min_count++;
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
	ArrangeEggnog(containers, used_cont, 0, result1, cnt, result2);

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
