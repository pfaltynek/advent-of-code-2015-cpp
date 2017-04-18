#include <fstream>
#include <iostream>
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

int main(void) {
	unsigned long long result1, result2, sum;
	int cnt, weight;
	std::ifstream ifs;
	std::string line;
	std::vector<int> weights;

	std::cout << "=== Advent of Code - day 24 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	result1 = result2 = cnt = sum = 0;

	weights.clear();

	ifs.open("input.txt", std::ifstream::in);

	if (ifs.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	while (std::getline(ifs, line)) {
		cnt++;

		if (DecodeWeight(line, weight)) {
			weights.push_back(weight);
			sum += weight;
		} else {
			std::cout << "Error decoding input line " << cnt << std::endl;
			return -1;
		}
	}

	if (ifs.is_open()) {
		ifs.close();
	}

	std::sort(weights.begin(), weights.end());
	std::reverse(weights.begin(), weights.end());

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;

	//result2 = SimulateProgram(prog, 1);

	std::cout << "Result is " << result2 << std::endl;
}
