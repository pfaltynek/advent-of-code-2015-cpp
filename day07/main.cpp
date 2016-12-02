#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

const std::string sides_divider = " -> ";
const std::string op_and = " AND ";
const std::string op_or = " OR ";
const std::string op_not = "NOT ";
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

typedef struct {
	std::string out;
	std::string in1;
	std::string in2;
	unsigned int in1val;
	unsigned int in2val;
	OPERATION operation;
} INSTRUCTION;

bool IsNumeric(std::string expression) {
	return expression.find_first_not_of("0123456789") == std::string::npos;
}

int ProcessInstructions(std::map<std::string, INSTRUCTION> data, std::string request) {
	std::map<std::string, int> values;
	//std::map<std::string, INSTRUCTION> instructions(data);
	std::map<std::string, INSTRUCTION> ins;
	std::vector<std::string> index;
	std::map<std::string, INSTRUCTION>::iterator it;

	index.push_back(request);

	while (index.size() > 0) {
		std::string search_for = index[0];
		it = data.find(search_for);
		if (it == data.end()) {
			int z = 999; // problem
		}
		else {

		}
	}

	/*
		for (std::map<std::string, INSTRUCTION>::iterator it =
	   instructions.begin();
			 it != instructions.end(); ++it) {
			if ((it->second.operation == OPERATION::OP_ASSIGN) &&
	   (it->second.in1.empty())){
				int x = 9;
			}
		}
	*/
	return 0;
}

int main(void) {
	int result1 = 0, result2 = 0, cnt, pos;
	std::ifstream input;
	std::string line;
	std::map<std::string, INSTRUCTION> instructions;

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
		INSTRUCTION inst;
		std::string left;

		// decode instruction sides
		pos = line.find(sides_divider);
		if (pos == std::string::npos) {
			std::cout << "Instruction invalid format at input line " << cnt
					  << std::endl;
			return -1;
		}
		// parse instruction type
		left = line.substr(0, pos);
		inst.out = line.substr(pos + sides_divider.size());
		inst.in1val = 0;
		inst.in2val = 0;
		pos = left.find(op_and);
		if (pos != std::string::npos) {
			inst.operation = OPERATION::OP_AND;
			inst.in1 = left.substr(0, pos);
			inst.in2 = left.substr(pos + op_and.size());
			if (IsNumeric(inst.in1)) {
				inst.in1val = atoi(inst.in1.c_str());
				inst.in1.clear();
			}
			if (IsNumeric(inst.in2)) {
				inst.in2val = atoi(inst.in2.c_str());
				inst.in2.clear();
			}
		} else {
			pos = left.find(op_or);
			if (pos != std::string::npos) {
				inst.operation = OPERATION::OP_OR;
				inst.in1 = left.substr(0, pos);
				inst.in2 = left.substr(pos + op_or.size());
				if (IsNumeric(inst.in1)) {
					inst.in1val = atoi(inst.in1.c_str());
					inst.in1.clear();
				}
				if (IsNumeric(inst.in2)) {
					inst.in2val = atoi(inst.in2.c_str());
					inst.in2.clear();
				}
			} else {
				pos = left.find(op_not);
				if (pos != std::string::npos) {
					inst.operation = OPERATION::OP_NOT;
					if (pos != 0) {
						std::cout
							<< "Invalid NOT operation format in instruction at "
							   "input line "
							<< cnt << std::endl;
						return -1;
					}
					inst.in1 = left.substr(op_not.size());
					inst.in2.clear();
					if (IsNumeric(inst.in1)) {
						inst.in1val = atoi(inst.in1.c_str());
						inst.in1.clear();
					}
				} else {
					pos = left.find(op_lshift);
					if (pos != std::string::npos) {
						inst.operation = OPERATION::OP_LSHIFT;
						inst.in1 = left.substr(0, pos);
						inst.in2 = left.substr(pos + op_lshift.size());
						if (IsNumeric(inst.in1)) {
							inst.in1val = atoi(inst.in1.c_str());
							inst.in1.clear();
						}
						if (!IsNumeric(inst.in2)) {
							std::cout << "Invalid LSHIFT operation format in "
										 "instruction at "
										 "input line "
									  << cnt << std::endl;
							return -1;
						} else {
							inst.in2val = atoi(inst.in2.c_str());
							inst.in2.clear();
						}
					} else {
						pos = left.find(op_rshift);
						if (pos != std::string::npos) {
							inst.operation = OPERATION::OP_RSHIFT;
							inst.in1 = left.substr(0, pos);
							inst.in2 = left.substr(pos + op_rshift.size());
							if (IsNumeric(inst.in1)) {
								inst.in1val = atoi(inst.in1.c_str());
								inst.in1.clear();
							}
							if (!IsNumeric(inst.in2)) {
								std::cout
									<< "Invalid RSHIFT operation format in "
									   "instruction at "
									   "input line "
									<< cnt << std::endl;
								return -1;
							} else {
								inst.in2val = atoi(inst.in2.c_str());
								inst.in2.clear();
							}
						} else if (left.size() > 0) {
							inst.operation = OPERATION::OP_ASSIGN;
							inst.in1 = left;
							inst.in2.clear();
							if (IsNumeric(inst.in1)) {
								inst.in1val = atoi(inst.in1.c_str());
								inst.in1.clear();
							}
						} else {
							std::cout << "Invalid operation in instruction at "
										 "input line "
									  << cnt << std::endl;
							return -1;
						}
					}
				}
			}
		}
		instructions[inst.out] = inst;
	}

	if (input.is_open()) {
		input.close();
	}

	result1 = ProcessInstructions(instructions, "a");
	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
