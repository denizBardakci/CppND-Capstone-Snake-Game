#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include <mutex>

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  // Constructor
  Snake(int grid_width, int grid_height)
      : grid_width_(grid_width),
        grid_height_(grid_height),
        head_x_(static_cast<float>(grid_width) / 2),
        head_y_(static_cast<float>(grid_height) / 2) {}

  // Update function
  void Update();

  // Grow the snake's body
  void GrowBody();

  // Check if a cell is part of the snake
  bool SnakeCell(int x, int y);

  // Getters of Snake class
  Direction GetDirection() const { return direction_; };
  float GetSpeed() const { return speed_; };
  int GetSize() const { return size_; };
  float GetHeadX() const { return head_x_; };
  float GetHeadY() const { return head_y_; };
  std::vector<SDL_Point> GetBody() const { return body_; };
  int GetSizeOfSnake() const { return size_; }
  bool IsSnakeAlive() const { return alive_; };
  
  // Kill the snake
  void KillSnake();
  
  // Set the snake's direction
  void SetSnakeDirection(const Snake::Direction& input);

  /**
  * @brief Increases the snake agent's speed
  * 
  * This function takes an increment argument and increases the agent speed.
  *
  * @param increment: Amount of speed increase 
  **/
  void IncreaseSnakeSpeed(float increment);

 private:
  // Update the head of the snake
  void UpdateHead();

  // Update the body of the snake
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  std::mutex mutex_;

  Direction direction_ = Direction::kUp;
  std::vector<SDL_Point> body_;
  float speed_{0.1f};
  float head_x_;
  float head_y_;
  int size_{1};
  int grid_width_;
  int grid_height_;
  bool alive_{true};
  bool growing_{false};
};

#endif
