#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <string.h>

int main(void) {
	FILE* f;
	char buff [101], *ptr, *pnum;
	int result1 = 0, result2 = 0;
	bool basement_entered = false;
	int input_line = 0;

	std::cout << "=== Advent of Code - day 2 ====" << std::endl;

	std::cout << "--- part 1 ---" << std::endl;

	f = fopen("input.txt", "r");
	if (f == NULL) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	while (fgets(buff, 101, f) != NULL) {
		int dims[3], idx = 0, tmp;
		
		input_line++;
		ptr = buff;
		while (idx < 3){
			pnum = ptr;
			while ((*pnum <= '9') && (*pnum >= '0')){
				pnum++;
			}
			if ((*pnum == 'x') || (*pnum == 'X') || (*pnum == 0) || (*pnum == '\n') || (*pnum == '\r')){
				*pnum = 0;
				dims[idx] = atoi(ptr);
				idx++;
				ptr = ++pnum;
			}
			else{
				std::cout << "Invalid input format at line " << input_line << std::endl;
				return -1;
			} 
		}

		if (dims[0] > dims[1]) {
			tmp = dims[1];
			dims[1] = dims[0];
			dims[0] = tmp;
		}
		if (dims[1] > dims[2]) {
			tmp = dims[2];
			dims[2] = dims[1];
			dims[1] = tmp;
		}
		result1 += (2 * (dims[0] * dims[1])) + (2 * (dims[0] * dims[2])) + (2 * (dims[1] * dims[2])) + (dims[0]*dims[1]);
		result2 += (2 * dims[0]) + (2 * dims[1]) + (dims[0] * dims[1] * dims[2]);
	}

	if (f != NULL) {
		fclose(f);
		f = NULL;
	}
	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
