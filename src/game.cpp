#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, deadly_food_);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  std::lock_guard<std::mutex> lck(mutex_);
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}
void Game::DeadlyFoodTimer()
{
  const int deadlySeconds = 10;
  auto startTime = std::chrono::high_resolution_clock::now();
  std::unique_lock<std::mutex> lock(mutex_);
  while (true)
  {
    condition_var_.wait(lock, [this]{return is_deadly_food_active_;});
    auto current_Time = std::chrono::high_resolution_clock::now();
    auto elapsed_Seconds = std::chrono::duration_cast<std::chrono::seconds>(current_Time - startTime).count();
    if (elapsed_Seconds >= deadlySeconds)
    {
      // Deadly food time is up
      is_deadly_food_active_ = false;
      break;
    }
    // Wait for a short interval 
    condition_var_.wait_for(lock, std::chrono::milliseconds(800));
  }
}
void Game::CreateDeadlyFood(){
  std::lock_guard<std::mutex> lck(mutex_);
  
  if (!is_deadly_food_active_)
    {
      deadlyFoodThread_ = std::thread(&Game::DeadlyFoodTimer, this);
      deadlyFoodThread_.detach();
   
      int x = random_w(engine);
      int y = random_h(engine);

    if (!snake.SnakeCell(x, y)) {
       deadly_food_.x = x;
       deadly_food_.y = y;
    	} 
      is_deadly_food_active_ = true;
      condition_var_.notify_one();
    }
}
void Game::Update() {
  if (!snake.IsSnakeAlive()) return;

  snake.Update();

  int new_x = static_cast<int>(snake.GetHeadX());
  int new_y = static_cast<int>(snake.GetHeadY());

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
 	snake.IncreaseSnakeSpeed(0.02);
  }
    // each successful food creation, create new deadly food
    CreateDeadlyFood();
  // Check if there's food over here
  if (deadly_food_.x == new_x && deadly_food_.y == new_y) {
    cause_of_death = "You ate a deadly food, you died hehehe :)";
  	snake.KillSnake();
    std::cout << "You ate a deadly food, you died hehehe :) \n";
  }
}
std::string Game::CauseOfDeath() const{ return cause_of_death ;}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.GetSizeOfSnake(); }