#pragma once
#include <string>
#include <vector>

class HighScoreManager {
private:
    struct HighScore {
        int score;
        int level;
        std::string date;
    };
    std::vector<HighScore> highScores;
    const std::string filename = "highscores.txt";

public:
    HighScoreManager();
    void saveHighScore(int score, int level);

private:
    void loadHighScores();
    void saveHighScores();
};