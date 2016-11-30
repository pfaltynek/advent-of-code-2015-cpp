//#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

const std::string sides_divider = " -> ";
const std::string op_and = " AND ";
const std::string op_or = " OR ";
const std::string op_not = " NOT ";
const std::string op_lshift = " LSHIFT ";
const std::string op_rshift = " RSHIFT ";

typedef enum OPERATION {
	OP_ASSIGN,
	OP_AND,
	OP_OR,
	OP_NOT,
	OP_LSHIFT,
	OP_RSHIFT
} OPERATION;

class INSTRUCTION {
  public:
	std::string out;
	std::string in1;
	std::string in2;
	unsigned int inval1;
	unsigned int inval2;
	OPERATION operation;
	INSTRUCTION();
};

INSTRUCTION::INSTRUCTION() {
	operation = OPERATION::OP_ASSIGN;
	inval1 = 0;
	inval2 = 0;
	out = "";
	in1 = "";
	in2 = "";
}

bool IsNumeric(std::string expression) {
	return expression.find_first_not_of("0123456789") != std::string::npos;
}

int main(void) {
	int result1 = 0, result2 = 0, cnt;
	std::ifstream input;
	std::string line;

	std::cout << "=== Advent of Code - day 7 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open("input.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	cnt = 0;

	while (std::getline(input, line)) {

		cnt++;
	}

	if (input.is_open()) {
		input.close();
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
