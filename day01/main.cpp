#include <cstdio>
#include <iostream>

int main(void) {
	FILE* f;
	int c;
	int floor = 0;
	int basement_idx = 0;
	bool basement_entered = false;

	f = fopen("input.txt", "r");
	if (f == NULL) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	c = fgetc(f);
	while (c != EOF) {
		switch (c) {
			case '(':
				floor++;
				break;
			case ')':
				floor--;
				break;
			case '\n':
			case '\r':
				break;
			default:
				std::cout << "Invalid character in input file.\n";
				return -1;
				break;
		}
		if (!basement_entered) {
			basement_idx++;
			if (floor < 0) {
				basement_entered = true;
			}
		}
		c = fgetc(f);
	}

	if (f != NULL) {
		fclose(f);
		f = NULL;
	}
	std::cout << "Final floor is " << floor << std::endl
		 << "Basement entered at character position " << basement_idx << std::endl;
}
