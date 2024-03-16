#include "GameResultsLogger.h"
#include <iostream>

GameResultsLogger::GameResultsLogger() {
    std::string fileName = "results.txt";
    outputFile.open(fileName, std::ios::app);

    if (!outputFile.is_open()) {
        std::cerr << "Unable to open the file for writing." << std::endl;
    }
}

GameResultsLogger::~GameResultsLogger() {
    if (outputFile.is_open()) {
        outputFile.close();
    }
}

void GameResultsLogger::logGameResults(int score, int size, const std::string& causeOfDeath) {
    std::string formattedDateTime = getCurrentDateTime();

    outputFile << "Game has been played at " << formattedDateTime << std::endl;
    outputFile << "Score: " << score << std::endl;
    outputFile << "Size: " << size << std::endl;
    outputFile << causeOfDeath << std::endl;

    outputFile << "-------------------------" << std::endl;

    outputFile.flush();

    std::cout << "Results have been successfully recorded." << std::endl;
}

std::string GameResultsLogger::getCurrentDateTime() {
    time_t rawTime;
    time(&rawTime);

    std::unique_ptr<struct tm> timeInfo = std::make_unique<struct tm>();
    localtime_r(&rawTime, timeInfo.get());

    char dateBuffer[80];
    std::strftime(dateBuffer, sizeof(dateBuffer), "%a %b %d %H:%M:%S %Y", timeInfo.get());

    return std::string(dateBuffer);
}