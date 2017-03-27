#include <iostream>
#include <regex>
#include <string>

const std::string input = "vzbxkghb";
std::regex regex_rule1("^[a-z]{8}$");
std::regex regex_rule2("^[^ilo]{8}$");
std::regex regex_rule3("^.*([a-z])\\1.*([a-z])\\2.*$");

bool CheckPassword(std::string password) {
	std::smatch sm;

	if (!regex_match(password, sm, regex_rule1)) {
		return false;
	}
	if (!regex_match(password, sm, regex_rule2)) {
		return false;
	}
	if (!regex_match(password, sm, regex_rule3)) {
		return false;
	}
	if (sm.str(1) == sm.str(2)) {
		return false;
	}

	for (int i = 0; i < password.size() - 3; i++) {
		if ((password[i] == password[i + 1] - 1) && (password[i + 1] == password[i + 2] - 1)) {
			return true;
		}
	}
	return false;
}

void IncrementPassword(std::string &password) {
	std::string::reverse_iterator rit;

	for (rit = password.rbegin(); rit != password.rend(); ++rit) {
		if (*rit != 'z') {
			(*rit)++;
			break;
		} else {
			*rit = 'a';
		}
	}
}

int main(void) {
	std::string result1, result2;

	std::cout << "=== Advent of Code - day 11 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	result1 = input;

	while (!CheckPassword(result1)) {
		IncrementPassword(result1);
	}

	result2 = result1;
	IncrementPassword(result2);

	while (!CheckPassword(result2)) {
		IncrementPassword(result2);
	}

	std::cout << "Result is '" << result1 << "'" << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is '" << result2 << "'" << std::endl;
}
