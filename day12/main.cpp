#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string>

void ExploreJSON(nlohmann::json j, int &result1, int &result2) {
	int r1, r2, p1, p2;
	bool red_found;

	red_found = false;
	r1 = 0;
	r2 = 0;

	if (j.is_number_integer()) {
		r1 = j;
		r2 = j;
	} else if (j.is_array()) {
		for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
			p1 = 0;
			p2 = 0;
			ExploreJSON(*it, p1, p2);
			r1 += p1;
			r2 += p2;
		}
	} else if (j.is_object()) {
		for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
			if (it.value().is_string()) {
				if (it.value() == "red") {
					red_found = true;
				}
			} else {
				p1 = 0;
				p2 = 0;
				ExploreJSON(it.value(), p1, p2);
				r1 += p1;
				r2 += p2;
			}
		}
		if (red_found) {
			r2 = 0;
		}
	}

	result1 += r1;
	result2 += r2;
}

int main(void) {
	int result1 = 0, result2 = 0;
	std::ifstream i;
	nlohmann::json j;

	i.open("input.txt");

	i >> j;

	std::cout << "=== Advent of Code - day 12 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	if (i.is_open()) {
		i.close();
	}

	ExploreJSON(j, result1, result2);

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
