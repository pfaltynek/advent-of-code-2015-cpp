#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

std::regex regex_rule("^(\\w+): capacity (-?\\d+), durability (-?\\d+), flavor (-?\\d+), texture (-?\\d+), calories (-?\\d+)$");

const int TEASPOONS_MAX = 100;
const int CALORIES = 500;

typedef struct {
	std::string name;
	int capacity, durability, flavor, texture, calories;
} INGREDIENCE;

bool DecodeIngredience(std::string line, INGREDIENCE &ingredience) {
	std::smatch sm;

	if (!regex_match(line, sm, regex_rule)) {
		return false;
	}
	ingredience.name = sm.str(1);
	ingredience.capacity = atoi(sm.str(2).c_str());
	ingredience.durability = atoi(sm.str(3).c_str());
	ingredience.flavor = atoi(sm.str(4).c_str());
	ingredience.texture = atoi(sm.str(5).c_str());
	ingredience.calories = atoi(sm.str(6).c_str());

	return true;
}

void GetRecipeScore(std::vector<INGREDIENCE> ingrediences, std::vector<int> recipe, long &score, int &calories) {
	long cap = 0, dur = 0, fla = 0, tex = 0, cal = 0;

	for (int i = 0; i < recipe.size(); i++) {
		cap += ingrediences[i].capacity * recipe[i];
		dur += ingrediences[i].durability * recipe[i];
		fla += ingrediences[i].flavor * recipe[i];
		tex += ingrediences[i].texture * recipe[i];
		cal += ingrediences[i].calories * recipe[i];
	}
	if ((cap < 0) || (dur < 0) || (fla < 0) || (tex < 0)) {
		score = 0;
	} else {
		score = cap * dur * fla * tex;
	}
	calories = cal;
}

void FindAllAvailableRecipes(std::vector<int> &recipe, int sum, int idx, std::vector<std::vector<int>> &recipes) {
	if ((idx + 1) == recipe.size()) {
		recipe[idx] = TEASPOONS_MAX - sum;
		recipes.push_back(recipe);
	} else {
		for (int j = 0; j < TEASPOONS_MAX - sum; j++) {
			recipe[idx] = j;
			FindAllAvailableRecipes(recipe, sum + j, idx + 1, recipes);
		}
	}
}

void ExploreAllRecipes(std::vector<INGREDIENCE> ingrediences, long &result1, long &result2) {
	std::vector<int> recipe(ingrediences.size(), 0);
	std::vector<std::vector<int>> recipes;
	long score;
	int calories;

	FindAllAvailableRecipes(recipe, 0, 0, recipes);

	for (int i = 0; i < recipes.size(); i++) {
		GetRecipeScore(ingrediences, recipes[i], score, calories);
		if (score > result1) {
			result1 = score;
		}
		if ((calories == CALORIES) && (score > result2)) {
			result2 = score;
		}
	}
}

int main(void) {
	long result1, result2;
	int cnt;
	std::ifstream ifs;
	std::vector<INGREDIENCE> ingrediences;
	std::string line;

	std::cout << "=== Advent of Code - day 15 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	result2 = result1 = cnt = 0;

	ifs.open("input.txt", std::ifstream::in);

	if (ifs.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	while (std::getline(ifs, line)) {
		cnt++;
		INGREDIENCE ingredience;
		if (DecodeIngredience(line, ingredience)) {
			ingrediences.push_back(ingredience);
		} else {
			std::cout << "Error decoding input line " << cnt << std::endl;
			return -1;
		}
	}

	if (ifs.is_open()) {
		ifs.close();
	}

	ExploreAllRecipes(ingrediences, result1, result2);

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
