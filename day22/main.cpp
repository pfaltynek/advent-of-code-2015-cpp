#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

const std::string str_hit_pts = "Hit Points";
const std::string str_damage = "Damage";
const std::string str_magic_missile = "Magic Missile";
const std::string str_drain = "Drain";
const std::string str_shield = "Shield";
const std::string str_poison = "Poison";
const std::string str_recharge = "Recharge";

const int my_hit_pts_init = 100;

std::regex regex_rule("^(" + str_hit_pts + "|" + str_damage + "): (\\d+)$");

typedef struct {
	int boss_hit_pts, boss_damage, wizz_hit_pts, wizz_handicap, mana_spent, mana, shield_turns, poison_turns, recharge_turns;
} FIGHT_STATE;

typedef struct {
	int mana_cost, damage, armor, heal, mana_recharge, turns;
} SPELL_INFO;

bool DecodeBossParams(std::string line, std::string &param, int &value) {
	std::smatch sm;

	if (!regex_match(line, sm, regex_rule)) {
		return false;
	}

	param = sm.str(1);
	value = atoi(sm.str(2).c_str());

	return true;
}

void FillSpells(std::map<std::string, SPELL_INFO> &spells) {
	SPELL_INFO si;

	spells.clear();

	si.mana_cost = 53;
	si.damage = 4;
	si.armor = 0;
	si.heal = 0;
	si.mana_recharge = 0;
	si.turns = 0;
	spells[str_magic_missile] = si;

	si.mana_cost = 73;
	si.damage = 2;
	si.armor = 0;
	si.heal = 2;
	si.mana_recharge = 0;
	si.turns = 0;
	spells[str_drain] = si;

	si.mana_cost = 113;
	si.damage = 0;
	si.armor = 7;
	si.heal = 0;
	si.mana_recharge = 0;
	si.turns = 6;
	spells[str_shield] = si;

	si.mana_cost = 173;
	si.damage = 3;
	si.armor = 0;
	si.heal = 0;
	si.mana_recharge = 0;
	si.turns = 6;
	spells[str_poison] = si;

	si.mana_cost = 229;
	si.damage = 0;
	si.armor = 0;
	si.heal = 0;
	si.mana_recharge = 101;
	si.turns = 5;
	spells[str_recharge] = si;
}

bool PerformTurn(FIGHT_STATE &state, std::map<std::string, SPELL_INFO> spells, std::string spell, bool &boss_won) {
	int armor = 0;

	boss_won = false;

	if (!spell.empty() && state.wizz_handicap) {
		state.wizz_hit_pts -= state.wizz_handicap;
		if (state.wizz_hit_pts <= 0) {
			boss_won = true;
			return true;
		}
	}

	if (state.poison_turns) {
		state.poison_turns--;
		state.boss_hit_pts -= spells[str_poison].damage;

		if (state.boss_hit_pts <= 0) {
			return true;
		}
	}

	if (state.recharge_turns) {
		state.recharge_turns--;
		state.mana += spells[str_recharge].mana_recharge;
	}

	if (state.shield_turns) {
		state.shield_turns--;
		armor = spells[str_shield].armor;
	}

	if (spell.empty()) {
		if (armor >= state.boss_damage) {
			state.wizz_hit_pts--;
		} else {
			state.wizz_hit_pts -= (state.boss_damage - armor);
		}

		if (state.wizz_hit_pts <= 0) {
			boss_won = true;
			return true;
		}
	} else {
		if ((spell == str_poison) && (state.poison_turns)) {
			boss_won = true;
			return true;
		}
		if ((spell == str_recharge) && (state.recharge_turns)) {
			boss_won = true;
			return true;
		}
		if ((spell == str_shield) && (state.shield_turns)) {
			boss_won = true;
			return true;
		}

		state.mana -= spells[spell].mana_cost;

		if (state.mana < 0) {
			boss_won = true;
			return true;
		}

		state.mana_spent += spells[spell].mana_cost;

		switch (spell[0]) {
			case 'D': // Drain
				state.boss_hit_pts -= spells[spell].damage;
				state.wizz_hit_pts += spells[spell].heal;
				if (state.boss_hit_pts <= 0) {
					return true;
				}
				break;
			case 'M': // Magic Missile
				state.boss_hit_pts -= spells[spell].damage;
				if (state.boss_hit_pts <= 0) {
					return true;
				}
				break;
			case 'R': // Recharge
				state.recharge_turns = spells[str_recharge].turns;
				break;
			case 'S': // Shield
				state.shield_turns = spells[str_shield].turns;
				break;
			case 'P': // Poison
				state.poison_turns = spells[str_poison].turns;
				break;
			default:
				int bz = 16;
				break;
		}
	}

	return false;
}

void SimulateFight(FIGHT_STATE state, std::map<std::string, SPELL_INFO> &spells, int &result) {
	bool res;
	bool boss_won;

	for (auto it = spells.begin(); it != spells.end(); ++it) {
		FIGHT_STATE new_state = state;

		if (PerformTurn(new_state, spells, it->first, boss_won)) {
			if ((!boss_won) && (result > new_state.mana_spent)) {
				result = new_state.mana_spent;
			}
			continue;
		}

		if (PerformTurn(new_state, spells, "", boss_won)) {
			if ((!boss_won) && (result > new_state.mana_spent)) {
				result = new_state.mana_spent;
			}
			continue;
		}

		if (new_state.mana_spent < result) {
			SimulateFight(new_state, spells, result);
		}
	}
}

int main(void) {
	int result1, result2, cnt, value;
	std::ifstream ifs;
	std::string line, param;
	std::map<std::string, int> boss_cfg, active_effects;
	std::map<std::string, SPELL_INFO> spells;
	FIGHT_STATE state1, state2;

	std::cout << "=== Advent of Code - day 22 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	result1 = result2 = INT_MAX;
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

	if (boss_cfg.size() != 2) {
		std::cout << "Invalid or incomplette boss definition" << std::endl;
		return -1;
	}

	if (ifs.is_open()) {
		ifs.close();
	}

	FillSpells(spells);

	state1.boss_damage = boss_cfg[str_damage];
	state1.boss_hit_pts = boss_cfg[str_hit_pts];
	state1.mana = 500;
	state1.mana_spent = 0;
	state1.poison_turns = 0;
	state1.recharge_turns = 0;
	state1.shield_turns = 0;
	state1.wizz_hit_pts = 50;
	state1.wizz_handicap = 0;

	state2 = state1;

	/* tests
	state1.wizz_hit_pts = 10;
	state1.mana = 250;
	state1.boss_damage = 8;
	state1.boss_hit_pts = 13;
	bool res;

	res = PerformTurn(state1, spells, str_poison);
	res = PerformTurn(state1, spells, "");

	res = PerformTurn(state1, spells, str_magic_missile);
	res = PerformTurn(state1, spells, "");

	state1 = state2;
	state1.wizz_hit_pts = 10;
	state1.mana = 250;
	state1.boss_damage = 8;
	state1.boss_hit_pts = 14;

	res = PerformTurn(state1, spells, str_recharge);
	res = PerformTurn(state1, spells, "");

	res = PerformTurn(state1, spells, str_shield);
	res = PerformTurn(state1, spells, "");

	res = PerformTurn(state1, spells, str_drain);
	res = PerformTurn(state1, spells, "");

	res = PerformTurn(state1, spells, str_poison);
	res = PerformTurn(state1, spells, "");

	res = PerformTurn(state1, spells, str_magic_missile);
	res = PerformTurn(state1, spells, "");
*/
	SimulateFight(state1, spells, result1);

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;

	state2 = state1;
	state2.wizz_handicap = 1;

	SimulateFight(state2, spells, result2);

	std::cout << "Result is " << result2 << std::endl;
}

