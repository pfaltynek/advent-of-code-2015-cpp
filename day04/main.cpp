#include <cstdio>
#include <iostream>
#include <openssl/md5.h>
#include <string.h>

const char input[] = "bgvyzdsv";
char buffer[101];
unsigned char hash[MD5_DIGEST_LENGTH];

int main(void) {
	int result1 = 0, result2 = 0, number = 0, count;
	int size;

	std::cout << "=== Advent of Code - day 4 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	while ((result1 == 0) || (result2 == 0)) {
		sprintf(buffer, "%s%d", input, number);
		size = strlen(buffer);
		MD5((const unsigned char *)buffer, size, hash);
		count = 0;
		if (hash[0] == 0 && hash[1] == 0){
			if (((hash[2] & 0xF0) == 0) && (result1 == 0)) {
				result1 = number;
			}
			if ((hash[2]  == 0) && (result2 == 0)) {
				result2 = number;
			}
		}
		number++;
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}

