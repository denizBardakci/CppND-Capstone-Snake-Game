#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  SDL_Point prev_cell{static_cast<int>(head_x_), static_cast<int>(head_y_)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{static_cast<int>(head_x_), static_cast<int>(head_y_)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction_) {
    case Direction::kUp:
      head_y_ -= GetSpeed();
      break;

    case Direction::kDown:
      head_y_ +=  GetSpeed();
      break;

    case Direction::kLeft:
      head_x_ -=  GetSpeed();
      break;

    case Direction::kRight:
      head_x_ +=  GetSpeed();
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x_ = fmod(GetHeadX() + grid_width_, grid_width_);
  head_y_ = fmod(GetHeadY() + grid_height_, grid_height_);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body_.push_back(prev_head_cell);

  if (!growing_) {
    // Remove the tail from the vector.
    body_.erase(body_.begin());
  } else {
    growing_ = false;
    size_++;
  }

  // Check if the snake has died.
  for (auto const &item : body_) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive_ = false;
    }
  }
}

void Snake::GrowBody() { growing_ = true; }

// increase the speed of the snake under the guard of lock_guard
void Snake::IncreaseSnakeSpeed(float increment){
   	std::lock_guard<std::mutex> lck(mutex_);
	speed_ += increment;
}
// assigning a new snake direction is now guarded
void Snake::SetSnakeDirection(const Snake::Direction& input){
    std::lock_guard<std::mutex> lck(mutex_);
	direction_ = input;
}

void Snake::KillSnake(){
  std::lock_guard<std::mutex> lck (mutex_);
  alive_ = false;
}

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x_) && y == static_cast<int>(head_y_)) {
    return true;
  }
  for (auto const &item : body_) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}