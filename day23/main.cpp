#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

typedef enum {
	INST_TRIPLE,
	INST_HALF,
	INST_INCREMENT,
	INST_JUMP,
	INST_JUMP_EVEN,
	INST_JUMP_ONE
} INSTRUCTION_TYPE;

typedef struct {
	INSTRUCTION_TYPE type;
	int offset, index;
	std::string line;
} INSTRUCTION;

bool DecodeInstruction(std::string line, INSTRUCTION &instruction) {
	std::smatch sm;
	std::regex regex_tpl_rule("^tpl (a|b)$");
	std::regex regex_hlf_rule("^hlf (a|b)$");
	std::regex regex_inc_rule("^inc (a|b)$");
	std::regex regex_jmp_rule("^jmp ([+|-]\\d+)$");
	std::regex regex_jio_rule("^jio (a|b), ([+|-]\\d+)$");
	std::regex regex_jie_rule("^jie (a|b), ([+|-]\\d+)$");

	instruction.index = 0;
	instruction.offset = 0;
	instruction.line = line;

	if (regex_match(line, sm, regex_tpl_rule)) {
		instruction.type = INST_TRIPLE;
		instruction.index = sm.str(1)[0] - 'a';
	} else if (regex_match(line, sm, regex_hlf_rule)) {
		instruction.type = INST_HALF;
		instruction.index = sm.str(1)[0] - 'a';
	} else if (regex_match(line, sm, regex_inc_rule)) {
		instruction.type = INST_INCREMENT;
		instruction.index = sm.str(1)[0] - 'a';
	} else if (regex_match(line, sm, regex_jmp_rule)) {
		instruction.type = INST_JUMP;
		instruction.offset = atoi(sm.str(1).c_str());
	} else if (regex_match(line, sm, regex_jio_rule)) {
		instruction.type = INST_JUMP_ONE;
		instruction.index = sm.str(1)[0] - 'a';
		instruction.offset = atoi(sm.str(2).c_str());
	} else if (regex_match(line, sm, regex_jie_rule)) {
		instruction.type = INST_JUMP_EVEN;
		instruction.index = sm.str(1)[0] - 'a';
		instruction.offset = atoi(sm.str(2).c_str());
	} else {
		return false;
	}

	if ((instruction.index > 1) || (instruction.index < 0)) {
		return false;
	}

	return true;
}

unsigned int SimulateProgram(std::vector<INSTRUCTION> prog, int a_init) {
	int idx = 0;
	unsigned int regs[2];

	regs[0] = a_init;
	regs[1] = 0;

	while (idx < prog.size()) {
		switch (prog[idx].type){
			case INST_HALF:
				regs[prog[idx].index] =  regs[prog[idx].index] / 2;
				idx++;
				break;
			case INST_TRIPLE:
				regs[prog[idx].index] *=  3;
				idx++;
				break;
			case INST_INCREMENT:
				regs[prog[idx].index]++;
				idx++;
				break;
			case INST_JUMP:
				idx += prog[idx].offset;
				break;
			case INST_JUMP_EVEN:
				if (regs[prog[idx].index] % 2) {
					idx++;
				} else {
					idx += prog[idx].offset;
				}
				break;
			case INST_JUMP_ONE:
				if (regs[prog[idx].index] == 1) {
					idx += prog[idx].offset;
				} else {
					idx++;
				}
				break;
			default:
				int z = 1236;
				break;
		}
	}

	return regs[1];
}

int main(void) {
	unsigned int result1, result2;
	int cnt;
	std::ifstream ifs;
	std::string line;
	std::vector<INSTRUCTION> prog;
	INSTRUCTION inst;

	std::cout << "=== Advent of Code - day 23 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	result1 = result2 = cnt = 0;

	prog.clear();

	ifs.open("input.txt", std::ifstream::in);

	if (ifs.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	while (std::getline(ifs, line)) {
		cnt++;

		if (DecodeInstruction(line, inst)) {
			prog.push_back(inst);
		} else {
			std::cout << "Error decoding input line " << cnt << std::endl;
			return -1;
		}
	}

	if (ifs.is_open()) {
		ifs.close();
	}

	result1 = SimulateProgram(prog, 0);

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;

	result2 = SimulateProgram(prog, 1);

	std::cout << "Result is " << result2 << std::endl;
}
