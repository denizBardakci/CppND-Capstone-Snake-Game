# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

# Project Contributions related to Rubrics

## Loops, Functions, I/O:

### 2.2) File I/O:
- The project now stores game results in a file (result.txt) under the build folder.
- Each game result includes the score and timestamp.
- A statement is added in case the user dies due to eating a deadly fruit.

### 2.3) Keyboard Commands:
- The project accepts keyboard commands such as arrows for user input.

### 2.4) Constructor Argument Change:
- In the Render class constructor, the argument has been changed to `const Snake&` to introduce an immutable variable.

## Object-oriented programming:

### 3.1.1) Access Specifiers:
- The Snake class now uses appropriate access specifiers for class members (changed from public to private).
  
### 3.1.2) New Feature: Deadly Red Fruit:
- Added a new feature where, in addition to normal food, a deadly red fruit is introduced.
- If the snake eats the deadly fruit, the game ends.
- Modifications made in `Game::DeadlyFoodTimer line 68, Game::DeadlyFood() line 88',  
- Modifications made in handling in `Controller::HandleInput() line 13`. When snake eats a deadly food, game ends.

### 3.2.1) Type Casting in Constructor:
- In the Snake constructor, `head_x` and `head_y` are now explicitly shown as floats with `static_cast<float>`.

### 3.2.2) Member Initializer List:
- The Snake constructor utilizes the member initializer list approach to prevent reverse commands when the size is 1.

### 3.3) Classes abstract implementation details from their interfaces.
  GameResultsLogger Class:
- A new class called `GameResultsLogger` is introduced to abstract the implementation details from other classes.
- Source and header files are located under the src folder. In header file of this class, details are enriched with their briefs.

### 3.3.1) Snake Class Re-organization:
- The Snake class is re-organized, and briefs have been added.
- The class's private members are abstracted for other classes and can only be accessed via getters and setters.

### 3.3.2) Game.h is also enriched with its briefs.

## Memory Management:

### 4.1) Use of References:
- References are used in many places in the project.

### 4.2) Proper Use of Destructors:
- The project uses destructors properly.

### 4.6) Use of Smart Pointers:
- Unique_ptr is used in the project (e.g., for recording game time in the GameResultsLogger class in GameResultsLogger::getCurrentDateTime function line 34).

## Concurrency:

### 5.2.) The submitted project effectively integrates multithreading by utilizing a thread within the Game::CreateDeadlyFood method in game.cpp line 88

### 5.3) Lock Guards:
- In `game.cpp`, food creation is guarded by `lock_guard` to prevent simultaneous creation of regular food and deadly food.
- In `snake.cpp`, `Snake::IncreaseSnakeSpeed line 64` and `Snake::SetSnakeDirection line 69` are introduced with lock guards to prevent simultaneous execution.

### 5.4) Condition Variables:
- `Game::DeadlyFoodTimer line 68 in game.cpp` and `Game::CreateDeadlyFood line 88 in game.cpp` use condition_variable to synchronize operations.

## Note for Users:
- Close the `result.txt` file before playing to ensure proper recording of results.
