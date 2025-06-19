
/*
 * Team: Team 404
 * Members: Rana Hanan Shafique (24I-3169), Mohib Ahmad (24I-3101), Nisar Ahmed (24I-3131)
 * Hackathon: Object Oriented Programming Hackathon - Spring 2025
 * Project: BRICK BREAKER GAME WITH ADVANCED GRAPHICS
 */

#include "HighScoreManager.h"
#include <fstream>
#include <sstream>
#include <algorithm>

HighScoreManager::HighScoreManager() {
    loadHighScores();
}

void HighScoreManager::saveHighScore(int score, int level) {
    HighScore newScore;
    newScore.score = score;
    newScore.level = level;
    newScore.date = "2025-06-19";
    highScores.push_back(newScore);
    std::sort(highScores.begin(), highScores.end(),
        [](const HighScore& a, const HighScore& b) {
            return a.score > b.score;
        });
    if (highScores.size() > 10) {
        highScores.resize(10);
    }
    saveHighScores();
}

void HighScoreManager::loadHighScores() {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        HighScore score;
        if (iss >> score.score >> score.level >> score.date) {
            highScores.push_back(score);
        }
    }
    file.close();
}

void HighScoreManager::saveHighScores() {
    std::ofstream file(filename);
    if (!file.is_open()) return;
    for (const auto& score : highScores) {
        file << score.score << " " << score.level << " " << score.date << "\n";
    }
    file.close();
}