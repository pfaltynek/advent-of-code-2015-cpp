#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

const std::string str_hit_pts = "Hit Points";
const std::string str_damage = "Damage";
const std::string str_armor = "Armor";

std::regex regex_rule("^(" + str_hit_pts + "|" + str_armor + "|" + str_damage + "): (\\d+)$");

class cFighter {
  public:
	cFighter() {
		_damage = 0;
		_armor = 0;
		_hit_pts = 100;
	};
	void Init(int hit_pts, int armor, int damage) {
		_armor = armor;
		_damage = damage;
		_hit_pts = hit_pts;
	}
	int PerformAttack() {
		return _hit_pts <= 0 ? 0 : _damage;
	}
	bool GotAttacked(int damage) {
		_hit_pts -= damage > _armor ? damage - _armor : 1;
		return _hit_pts <= 0;
	}

  private:
	int _damage, _armor, _hit_pts;
};

bool DecodeBossParams(std::string line, std::string &param, int &value) {
	std::smatch sm;

	if (!regex_match(line, sm, regex_rule)) {
		return false;
	}

	param = sm.str(1);
	value = atoi(sm.str(2).c_str());

	return true;
}

int main(void) {
	int result1, result2, cnt, value;
	std::ifstream ifs;
	std::string line, param;
	std::map<std::string, int> boss;

	std::cout << "=== Advent of Code - day 21 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	result1 = cnt = 0;
	result2 = INT_MAX;

	ifs.open("input.txt", std::ifstream::in);

	if (ifs.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	while (std::getline(ifs, line)) {
		cnt++;

		if (DecodeBossParams(line, param, value)) {
			boss[param] = value;
		} else {
			std::cout << "Error decoding input line " << cnt << std::endl;
			return -1;
		}
	}

	if (boss.size() != 3) {
		std::cout << "Invalid or incomplette boss definition" << std::endl;
		return -1;
	}

	if (ifs.is_open()) {
		ifs.close();
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;

	std::cout << "Result is " << result2 << std::endl;
}
