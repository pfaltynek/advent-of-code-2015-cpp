#include <algorithm>
#include <iostream>
#include <vector>

const long INPUT_LIMIT = 36000000;
#define MAX_ARRAY_SIZE 1000000
long street[MAX_ARRAY_SIZE];

long Calculate(int presents, int house_limit = -1) {
	long result = -1;
	int name = 1, max_name;
	long delivery;

	for (int i = 0; i < MAX_ARRAY_SIZE; i++) {
		street[i] = 0;
	}

	while (result < 0) {
		delivery = name * presents;

		if (house_limit > 0) {
			max_name = house_limit * name;
			max_name++;
			if (max_name > MAX_ARRAY_SIZE) {
				max_name = MAX_ARRAY_SIZE;
			}
		} else {
			max_name = MAX_ARRAY_SIZE;
		}

		for (int i = name; i < max_name; i += name) {
			street[i] += delivery;

			if (street[i] >= INPUT_LIMIT) {
				result = i;
				break;
			}
		}
		name++;
	}

	return result;
}

int main(void) {
	long result1, result2;

	std::cout << "=== Advent of Code - day 20 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	result2 = result1 = 0;

	result1 = Calculate(10);

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;

	result2 = Calculate(11, 50);

	std::cout << "Result is " << result2 << std::endl;
}
