#pragma once
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

class Reading_writing {

	const char key{ 'Z' };
    const std::string file_name{ "Highscores.dat" };

    std::vector<int> scores{};

	std::string xorEncryptDecrypt(const std::string& input);
public:
    std::vector<int> read_highscores();
    void write_highscores(int new_score);
};

std::string Reading_writing::xorEncryptDecrypt(const std::string& input) {
    std::string output = input;
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = input[i] ^ key;
    }
    return output;
}


std::vector<int> Reading_writing::read_highscores() {
    std::ifstream inFile(file_name, std::ios::binary);

    if (!inFile) {
        std::cerr << "Файл отсутствует, создается новый.\n";
        return scores;
    }

    std::string encryptedScore;
    while (std::getline(inFile, encryptedScore)) {
        std::string decryptedScore = xorEncryptDecrypt(encryptedScore);
        scores.push_back(std::stoi(decryptedScore));
    }

    inFile.close();
    return scores;
}


void Reading_writing::write_highscores( int new_score) {
    std::vector<int> scores = read_highscores();
    if (scores.size() < 5) {
        scores.push_back(new_score);
        while (scores.size() < 5) {
            scores.push_back(0);
        }
    }
    else {
        if (new_score > scores.back()) {
            for (size_t i = 0; i < scores.size(); ++i) {
                if (scores[i] == new_score) {
                    break;
                }
                scores.back() = new_score;
            }
        }
    }
    std::sort(scores.rbegin(), scores.rend()); // Сортируем по убыванию

    std::ofstream outFile(file_name, std::ios::binary);
    if (!outFile) {
        std::cerr << "Ошибка: невозможно записать в файл.\n";
        return;
    }
    for (int score : scores) {
        std::string encryptedScore = xorEncryptDecrypt(std::to_string(score));
        outFile << encryptedScore << "\n";
    }

    outFile.close();  
}