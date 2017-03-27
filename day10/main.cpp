#include <iostream>
#include <sstream>
#include <string>

const std::string input = "1113122113";

int main(void) {
	long long result1 = 0, result2 = 0;
	int cnt, curr, char_cnt;
	unsigned char chr, last;
	std::string buffer;
	std::stringstream is, os;

	std::cout << "=== Advent of Code - day 10 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	cnt = 0;

	is.str(input);

	while (cnt < 50) {
		char_cnt = 0;
		os.str("");
		os.clear();
		is.clear();
		last = 0;

		while (true) {
			is >> chr;
			if (!is.good()) {
				if (last > 0) {
					os << char_cnt << last;
					os.flush();
				}
				break;
			}

			if (chr == last) {
				char_cnt++;
			} else {
				if (last > 0) {
					os << char_cnt << last;
				}
				last = chr;
				char_cnt = 1;
			}
		}

		cnt++;

		buffer = os.str();

		if (cnt == 40) {
			result1 = buffer.size();
		}
		is.str(buffer);
	}
	result2 = buffer.size();

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
