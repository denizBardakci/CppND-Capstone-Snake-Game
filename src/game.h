#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <mutex>
#include <thread>
#include <future>
#include <condition_variable>
#include <chrono>
#include <string>

class Game {
 public:
  /**
   * @brief Constructs a Game object with given grid dimensions.
   *
   * @param grid_width: Width of the game grid.
   * @param grid_height: Height of the game grid.
   */
  Game(std::size_t grid_width, std::size_t grid_height);

  /**
   * @brief Runs the game loop, taking input from the controller and rendering updates.
   *
   * @param controller: Controller object for user input.
   * @param renderer: Renderer object for displaying game elements.
   * @param target_frame_duration: Target duration for each frame in milliseconds.
   */
  void Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration);

  /**
   * @brief Gets the current score of the game.
   *
   * @return Current game score.
   */
  int GetScore() const;

  /**
   * @brief Gets the current size of the snake.
   *
   * @return Current size of the snake.
   */
  int GetSize() const;

  /**
   * @brief Gets the cause of the snake's death.
   *
   * @return A string describing the cause of death.
   */
  std::string CauseOfDeath() const;

 private:
  Snake snake;  // The snake object in the game.
  SDL_Point food;  // Current position of the regular food.
  SDL_Point deadly_food_;  // Current position of the deadly red fruit.

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::mutex mutex_;
  std::condition_variable condition_var_;
  std::thread deadlyFoodThread_;
  std::string cause_of_death {"Each life ends, this one lived long and it was a natural death"};
  bool is_deadly_food_active_{};

  int score{0};  // Current score of the game.

  /**
   * @brief Places regular food at a random location on the game grid.
   */
  void PlaceFood();

  /**
   * @brief Creates the deadly red fruit at a random location on the game grid.
   */
  void CreateDeadlyFood();

  /**
   * @brief Updates the game state, including snake movement and collision detection.
   */
  void Update();

  /**
   * @brief Timer function for the deadly red fruit, controls its appearance.
   */
  void DeadlyFoodTimer();
};

#endif
