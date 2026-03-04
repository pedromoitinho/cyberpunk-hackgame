#include "./Cyberpunk.h"

static std::random_device rd;
static std::mt19937 gen(rd());

static const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const std::string digits = "0123456789";

static int activeIndex = 0;
static bool isRowMode = true;

static std::vector<std::string> userTries;
static std::unordered_map<std::string, bool> gameStep = { {"Easy", false}, {"Medium", false}, {"Hard", false} };

void Cyberpunk::generateGame() {
    std::uniform_int_distribution<> letterDist(0, 25);
    std::uniform_int_distribution<> digitDist(0, 9);
    std::uniform_int_distribution<> orderDist(0, 1);

    for (auto& row : gameFormat) {
        for (std::string& cell : row) {
            char l = letters[letterDist(gen)];
            char d = digits[digitDist(gen)];

            if (orderDist(gen) == 0) {
                cell = { l , d };
            }
            else {
                cell = { d, l };
            }
        }
    }
}

void Cyberpunk::generateAnswers() {
    std::uniform_int_distribution<> indexDist(0, 4);

    auto getSequence = [&](int length) {
        std::vector<std::string> seq;
        int r = 0;
        int c = indexDist(gen);
        seq.push_back(gameFormat[r][c]);
        bool isRow = false;

        for (int i = 1; i < length; ++i) {
            if (isRow) {
                int new_c;
                do { new_c = indexDist(gen); } while (new_c == c);
                c = new_c;
            }
            else {
                int new_r;
                do { new_r = indexDist(gen); } while (new_r == r);
                r = new_r;
            }
            seq.push_back(gameFormat[r][c]);
            isRow = !isRow;
        }
        return seq;
        };

    gameAnswers["Easy"] = getSequence(3);
    gameAnswers["Medium"] = getSequence(4);
    gameAnswers["Hard"] = getSequence(5);
}

void Cyberpunk::printGameFormat() {
    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 5; ++c) {
            if (gameFormat[r][c] == "--") std::cout << "[  ] ";
            else std::cout << "[" << gameFormat[r][c] << "] ";
        }
        if (isRowMode && activeIndex == r) std::cout << " *";
        std::cout << '\n';
    }

    if (!isRowMode) {
        for (int c = 0; c < 5; ++c) {
            if (activeIndex == c) std::cout << "  * ";
            else std::cout << "     ";
        }
        std::cout << '\n';
    }
    std::cout << "--------------------------\n";
}

void Cyberpunk::printAnswers() {
    std::vector<std::string> order = { "Easy", "Medium", "Hard" };

    for (const std::string& difficulty : order) {
        if (gameAnswers.find(difficulty) != gameAnswers.end()) {
            std::cout << "Answers - " << difficulty << " - ";

            for (const auto& cell : gameAnswers[difficulty]) {
                bool found = std::find(userTries.begin(), userTries.end(), cell) != userTries.end();

                if (found) {
                    std::cout << "[X]  ";
                }
                else {
                    std::cout << "[" << cell << "]  ";
                }
            }

            if (gameStep[difficulty]) std::cout << " COMPLETE!";
            std::cout << "\n---------------------\n";
        }
    }
}

bool Cyberpunk::inputVerification(std::string& input) {
    if (input.empty()) {
        isRowMode = !isRowMode;
        return true;
    }

    for (auto& c : input) {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }

    if (isRowMode) {
        for (int col = 0; col < 5; ++col) {
            if (gameFormat[activeIndex][col] == input) {
                gameFormat[activeIndex][col] = "--";
                activeIndex = col;
                isRowMode = false;
                return true;
            }
        }
    }
    else {
        for (int row = 0; row < 5; ++row) {
            if (gameFormat[row][activeIndex] == input) {
                gameFormat[row][activeIndex] = "--";
                activeIndex = row;
                isRowMode = true;
                return true;
            }
        }
    }

    return false;
}

void Cyberpunk::difficultyVerification() {
    for (auto& [difficulty, solved] : gameStep) {
        if (solved) continue;

        const auto& target = gameAnswers[difficulty];
        if (userTries.size() < target.size()) continue;

        for (size_t i = 0; i <= userTries.size() - target.size(); ++i) {
            bool match = true;
            for (size_t j = 0; j < target.size(); ++j) {
                if (userTries[i + j] != target[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                solved = true;
                break;
            }
        }
    }
}

void Cyberpunk::play(int maxTries) {
    std::string userInput;
    generateGame();
    generateAnswers();

    while (maxTries > 0) {
#ifdef _WIN32
        std::system("cls");
#else
        std::system("clear");
#endif
        printGameFormat();
        printAnswers();
        std::cout << "Attempts left: " << maxTries << "\nEnter Code (or press Enter to skip): " << std::flush;

        std::getline(std::cin, userInput);

        while (!inputVerification(userInput)) {
            std::cout << "\nInvalid Input! Try Again!\n" << std::flush;
            std::getline(std::cin, userInput);
        }

        if (!userInput.empty()) {
            userTries.push_back(userInput);
            difficultyVerification();
        }

        maxTries--;

        if (gameStep["Easy"] && gameStep["Medium"] && gameStep["Hard"]) {
#ifdef _WIN32
            std::system("cls");
#else
            std::system("clear");
#endif
            printGameFormat();
            printAnswers();
            std::cout << "\nSYSTEM BREACHED: YOU WIN!\n";
            return;
        }
    }

    std::cout << "\nACCESS DENIED: NO ATTEMPTS LEFT.\n";
}