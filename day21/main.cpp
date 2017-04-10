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
const int my_hit_pts_init = 100;

std::regex regex_rule("^(" + str_hit_pts + "|" + str_armor + "|" + str_damage + "): (\\d+)$");

class cFighter {
  public:
	cFighter() {
		_damage = 0;
		_armor = 0;
		_hit_pts = 100;
	};
	void Init(int hit_pts, int damage, int armor) {
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
	int GetHitPoints() {
		return _hit_pts;
	}

  private:
	int _damage, _armor, _hit_pts;
};

class cItem {
  public:
	std::string name;
	int cost, damage, armor;
	cItem(std::string item_name, int item_cost, int item_damage, int item_armor) {
		name = item_name;
		cost = item_cost;
		damage = item_damage;
		armor = item_armor;
	};
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

void FillWeapons(std::vector<cItem> &items) {
	items.clear();
	items.push_back(cItem("Dagger", 8, 4, 0));
	items.push_back(cItem("Shortsword", 10, 5, 0));
	items.push_back(cItem("Warhammer", 25, 6, 0));
	items.push_back(cItem("Longsword", 40, 7, 0));
	items.push_back(cItem("Greataxe", 74, 8, 0));
}

void FillArmor(std::vector<cItem> &items) {
	items.clear();
	items.push_back(cItem("No Armor", 0, 0, 0));
	items.push_back(cItem("Leather", 13, 0, 1));
	items.push_back(cItem("Chainmail", 31, 0, 2));
	items.push_back(cItem("Splintmail", 53, 0, 3));
	items.push_back(cItem("Bandedmail", 75, 0, 4));
	items.push_back(cItem("Platemail", 102, 0, 5));
}

void FillRings(std::vector<cItem> &items) {
	items.clear();
	items.push_back(cItem("No Ring", 0, 0, 0));
	items.push_back(cItem("Damage +1", 25, 1, 0));
	items.push_back(cItem("Damage +2", 50, 2, 0));
	items.push_back(cItem("Damage +3", 100, 3, 0));
	items.push_back(cItem("Defense +1", 20, 0, 1));
	items.push_back(cItem("Defense +2", 40, 0, 2));
	items.push_back(cItem("Defense +3", 80, 0, 3));
}

bool SimulateFight(cFighter me, cFighter boss) {
	while (true) {
		if (boss.GotAttacked(me.PerformAttack())){
			return true;
		}
		if (me.GotAttacked(boss.PerformAttack())){
			return false;
		}
	}
}

int main(void) {
	int result1, result2, cnt, value;
	std::ifstream ifs;
	std::string line, param;
	std::map<std::string, int> boss_cfg;
	std::vector<cItem> weapons, armors, rings;
	cFighter boss, me;

	std::cout << "=== Advent of Code - day 21 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	result1 = INT_MAX;
	result2 = 0;
	cnt = 0;
	
	ifs.open("input.txt", std::ifstream::in);

	if (ifs.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	while (std::getline(ifs, line)) {
		cnt++;

		if (DecodeBossParams(line, param, value)) {
			boss_cfg[param] = value;
		} else {
			std::cout << "Error decoding input line " << cnt << std::endl;
			return -1;
		}
	}

	if (boss_cfg.size() != 3) {
		std::cout << "Invalid or incomplette boss definition" << std::endl;
		return -1;
	}

	if (ifs.is_open()) {
		ifs.close();
	}

	FillWeapons(weapons);
	FillArmor(armors);
	FillRings(rings);

	for (int w = 0; w < weapons.size(); w++) {
		for (int a = 0; a < armors.size(); a++) {
			for (int r1 = 0; r1 < rings.size(); r1++) {
				for (int r2 = 0; r2 < rings.size(); r2++) {
					if ((r1 == r2) && (rings[r1].cost)) {
						continue;
					}
					value = weapons[w].cost + armors[a].cost + rings[r1].cost + rings[r2].cost;
					boss.Init(boss_cfg[str_hit_pts], boss_cfg[str_damage], boss_cfg[str_armor]);
					me.Init(my_hit_pts_init, weapons[w].damage + armors[a].damage + rings[r1].damage + rings[r2].damage, weapons[w].armor + armors[a].armor + rings[r1].armor + rings[r2].armor);
					if (SimulateFight(me, boss)) {
						if (value < result1) {
							result1 = value;
						}
					} else {
						if (value > result2) {
							result2 = value;
						}
					}
				}
			}
		}
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;

	std::cout << "Result is " << result2 << std::endl;
}
