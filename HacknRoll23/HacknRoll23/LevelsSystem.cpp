#include "LevelsSystem.h"

#include <iostream>

LevelsSystem::LevelsSystem() {
    readFile();
}

LevelsSystem::~LevelsSystem() {}

std::vector<int> LevelsSystem::getNumMeleeEnemies() const
{
    return this->numMeleeEnemies;
}

std::vector<int> LevelsSystem::getNumRangedEnemies() const
{
    return this->numRangedEnemies;
}

void LevelsSystem::readFile() {
    std::ifstream fin("Resources/res/input.txt");

    if (!fin) {
        std::cout << "Error in opening the file" << std::endl;
    }

    int a, b;

    while (fin >> a >> b) {
        numMeleeEnemies.push_back(a);
        numRangedEnemies.push_back(b);

        // Read in the new data for the next loop iteration.
    }
}

