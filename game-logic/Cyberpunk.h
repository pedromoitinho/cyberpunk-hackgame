#pragma once
#include <array>
#include <string>
#include <random>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>

class Cyberpunk {
public:
    std::array<std::array<std::string, 5>, 5> gameFormat;
    std::unordered_map<std::string, std::vector<std::string>> gameAnswers;

    void generateGame();
    void generateAnswers();

    void play(int maxTries = 12);

    void printGameFormat();
    void printAnswers();

    bool inputVerification(std::string& input);
    void difficultyVerification();
};