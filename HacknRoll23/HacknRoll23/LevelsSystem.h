#pragma once
#include <vector>
#include <fstream>


class LevelsSystem
{
protected:
	std::vector<int> numMeleeEnemies;
	std::vector<int> numRangedEnemies;
public:
	LevelsSystem();
	~LevelsSystem();

	std::vector<int> getNumMeleeEnemies() const;
	std::vector<int> getNumRangedEnemies() const;

	void readFile();
};
