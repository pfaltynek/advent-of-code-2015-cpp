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

bool ProcessInstruction(INSTRUCTION ins, std::map<std::string, int> &values) {
	bool result = false;
	int value1, value2;

	switch (ins.operation) {
		case OP_AND:
		case OP_OR:
		case OP_LSHIFT:
		case OP_RSHIFT:
			if (!ins.in2.empty()) {
				if (values.find(ins.in2) == values.end()) {
					return false;
				} else {
					value2 = values[ins.in2];
				}
			} else {
				value2 = ins.in2val;
			}

		case OP_NOT:
		case OP_ASSIGN:
			if (!ins.in1.empty()) {
				if (values.find(ins.in1) == values.end()) {
					return false;
				} else {
					value1 = values[ins.in1];
				}
			} else {
				value1 = ins.in1val;
			}
			break;
	}

	switch (ins.operation) {
		case OP_AND:
			values[ins.out] = value1 & value2;
			break;

		case OP_OR:
			values[ins.out] = value1 | value2;
			break;

		case OP_LSHIFT:
			values[ins.out] = value1 << value2;
			break;

		case OP_RSHIFT:
			values[ins.out] = value1 >> value2;
			break;

		case OP_ASSIGN:
			values[ins.out] = value1;
			break;

		case OP_NOT:
			values[ins.out] = ~value1;
			break;
	}

	return true;
}

int ProcessInstructions(std::map<std::string, INSTRUCTION> data,
						std::string request) {
	std::map<std::string, int> values;
	std::map<std::string, INSTRUCTION> ins;
	std::vector<std::string> index;
	std::map<std::string, INSTRUCTION>::iterator it;

	index.clear();
	index.push_back(request);
	values.clear();
	ins.clear();

	// while ((index.size() > 0) || (ins.size() > 0)) {
	while (values.find(request) == values.end()) {
		if (!index.empty()) {
			std::string variable;
			variable = index.pop_back();
			it = data.find(variable);
			if (it == data.end()) {
				int z = 999; // problem
			} else {
				if (!ProcessInstruction(it->second, values)) {
					ins[variable] = it->second;
					if (!it->second.in1.empty()) {
						index.push_back(it->second.in1);
					}
					if (!it->second.in2.empty()) {
						index.push_back(it->second.in2);
					}
				}
				else{
					
				}
			}
		}
	}
}

return values[request];
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
		inst.in1.clear();
		inst.in2.clear();
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
