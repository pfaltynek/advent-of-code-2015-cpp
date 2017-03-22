#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

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

bool DecodeInstruction(std::string line, INSTRUCTION &inst) {
	std::regex regex_instruction_and("^([a-z]+|\\d+) AND ([a-z]+|\\d+) -> ([a-z]+)$");
	std::regex regex_instruction_or("^([a-z]+|\\d+) OR ([a-z]+|\\d+) -> ([a-z]+)$");
	std::regex regex_instruction_lshift("^([a-z]+|\\d+) LSHIFT (\\d+) -> ([a-z]+)$");
	std::regex regex_instruction_rshift("^([a-z]+|\\d+) RSHIFT (\\d+) -> ([a-z]+)$");
	std::regex regex_instruction_not("^NOT ([a-z]+|\\d+) -> ([a-z]+)$");
	std::regex regex_instruction_assign("^([a-z]+|\\d+) -> ([a-z]+)$");
	std::smatch sm;

	inst.in1.clear();
	inst.in2.clear();
	inst.out.clear();
	inst.in1val = 0;
	inst.in2val = 0;

	if (std::regex_match(line, sm, regex_instruction_and)) {
		inst.operation = OPERATION::OP_AND;
		inst.in1 = sm.str(1);
		inst.in2 = sm.str(2);
		inst.out = sm.str(3);
		if (IsNumeric(inst.in1)) {
			inst.in1val = atoi(inst.in1.c_str());
			inst.in1.clear();
		}
		if (IsNumeric(inst.in2)) {
			inst.in2val = atoi(inst.in2.c_str());
			inst.in2.clear();
		}
	} else if (std::regex_match(line, sm, regex_instruction_or)) {
		inst.operation = OPERATION::OP_OR;
		inst.in1 = sm.str(1);
		inst.in2 = sm.str(2);
		inst.out = sm.str(3);
		if (IsNumeric(inst.in1)) {
			inst.in1val = atoi(inst.in1.c_str());
			inst.in1.clear();
		}
		if (IsNumeric(inst.in2)) {
			inst.in2val = atoi(inst.in2.c_str());
			inst.in2.clear();
		}
	} else if (std::regex_match(line, sm, regex_instruction_rshift)) {
		inst.operation = OPERATION::OP_RSHIFT;
		inst.in1 = sm.str(1);
		inst.in2 = sm.str(2);
		inst.out = sm.str(3);
		if (IsNumeric(inst.in1)) {
			inst.in1val = atoi(inst.in1.c_str());
			inst.in1.clear();
		}
		if (IsNumeric(inst.in2)) {
			inst.in2val = atoi(inst.in2.c_str());
			inst.in2.clear();
		}
	} else if (std::regex_match(line, sm, regex_instruction_lshift)) {
		inst.operation = OPERATION::OP_LSHIFT;
		inst.in1 = sm.str(1);
		inst.in2 = sm.str(2);
		inst.out = sm.str(3);
		if (IsNumeric(inst.in1)) {
			inst.in1val = atoi(inst.in1.c_str());
			inst.in1.clear();
		}
		if (IsNumeric(inst.in2)) {
			inst.in2val = atoi(inst.in2.c_str());
			inst.in2.clear();
		}
	} else if (std::regex_match(line, sm, regex_instruction_not)) {
		inst.operation = OPERATION::OP_NOT;
		inst.in1 = sm.str(1);
		inst.out = sm.str(2);
		if (IsNumeric(inst.in1)) {
			inst.in1val = atoi(inst.in1.c_str());
			inst.in1.clear();
		}
	} else if (std::regex_match(line, sm, regex_instruction_assign)) {
		inst.operation = OPERATION::OP_ASSIGN;
		inst.in1 = sm.str(1);
		inst.out = sm.str(2);
		if (IsNumeric(inst.in1)) {
			inst.in1val = atoi(inst.in1.c_str());
			inst.in1.clear();
		}
	} else {
		return false;
	}

	return true;
}

bool ProcessInstruction(INSTRUCTION ins, std::map<std::string, int> &values, std::vector<std::string> &values2search) {
	bool result = true;
	int value1, value2;

	switch (ins.operation) {
		case OP_AND:
		case OP_OR:
		case OP_LSHIFT:
		case OP_RSHIFT:
			if (!ins.in2.empty()) {
				if (values.find(ins.in2) == values.end()) {
					if (std::find(values2search.begin(), values2search.end(), ins.in2) == values2search.end()) {
						values2search.push_back(ins.in2);
					}
					result = false;
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
					if (std::find(values2search.begin(), values2search.end(), ins.in1) == values2search.end()) {
						values2search.push_back(ins.in1);
					}
					result = false;
				} else {
					value1 = values[ins.in1];
				}
			} else {
				value1 = ins.in1val;
			}
			break;
	}

	if (!result) {
		return false;
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

int ProcessInstructions(std::map<std::string, INSTRUCTION> data, std::string request) {
	std::map<std::string, int> values;
	std::map<std::string, INSTRUCTION> ins(data), new_ins;
	std::vector<std::string> index, new_index;
	std::map<std::string, INSTRUCTION>::iterator it;
	std::vector<std::string>::iterator itv;

	index.clear();
	index.push_back(request);
	values.clear();

	while (values.find(request) == values.end()) {
		new_index.clear();
		for (itv = index.begin(); itv != index.end(); ++itv) {
			it = ins.find(*itv);
			if (it != ins.end()) {
				if (!ProcessInstruction(it->second, values, new_index)) {
					new_index.push_back(it->first);
				} else {
					ins.erase(it);
				}
			} else {
				int z = 11; // problem!!!
			}
		}
		index = new_index;

		new_ins.clear();
		for (it = ins.begin(); it != ins.end(); ++it) {
			itv = std::find(index.begin(), index.end(), it->first);
			if (!ProcessInstruction(it->second, values, index)) {
				new_ins[it->first] = it->second;
				if (itv == index.end()) {
					index.push_back(it->first);
				}
			} else {
				if (itv != index.end()) {
					index.erase(itv);
				}
			}
		}
		ins = new_ins;
	}

	return values[request];
}

int main(void) {
	int result1 = 0, result2 = 0, cnt;
	std::ifstream input;
	std::string line;
	std::map<std::string, INSTRUCTION> instructions;
	INSTRUCTION part2modification;

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

		if (!DecodeInstruction(line, inst)) {
			std::cout << "Instruction invalid format at input line " << cnt << std::endl;
			return -1;
		}
		instructions[inst.out] = inst;
	}

	if (input.is_open()) {
		input.close();
	}

	result1 = ProcessInstructions(instructions, "a");
	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;

	part2modification.operation = OP_ASSIGN;
	part2modification.in1.clear();
	part2modification.in2.clear();
	part2modification.out = "b";
	part2modification.in1val = result1;
	part2modification.in2val = 0;
	instructions[part2modification.out] = part2modification;
	result2 = ProcessInstructions(instructions, "a");

	std::cout << "Result is " << result2 << std::endl;
}
