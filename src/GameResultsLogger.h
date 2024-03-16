/**
 * @file GameResultsLogger.h
 * @brief Declaration of the GameResultsLogger class for logging game results.
 */

#ifndef GAMERESULTSLOGGER_H
#define GAMERESULTSLOGGER_H

#include <string>
#include <fstream>
#include <ctime>
#include <memory>

/**
 * @brief The GameResultsLogger class handles logging game results to a file.
 */
class GameResultsLogger {
public:
    /**
     * @brief Constructor for GameResultsLogger. Opens a file stream for writing.
     */
    GameResultsLogger();

    /**
     * @brief Destructor for GameResultsLogger. Ensures the file stream is closed upon destruction.
     */
    ~GameResultsLogger();

    /**
     * @brief Logs game results to the file.
     * @param score The game score.
     * @param size The game size.
     * @param causeOfDeath The cause of death in the game.
     */
    void logGameResults(int score, int size, const std::string& causeOfDeath);

private:
    std::ofstream outputFile; /**< A file stream used for writing game results to a file. */

    /**
     * @brief Obtains the current date and time in a formatted string.
     * @return A formatted string representing the current date and time.
     */
    std::string getCurrentDateTime();
};

#endif // GAMERESULTSLOGGER_H
