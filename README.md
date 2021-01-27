# Snake Game Project

<img src="/snake_game.gif"/>

## Basic Build Instructions for Ubuntu 19.04

This program requires *SDL2, SDL2_image* and *SDL2_mixer* libraries. we can use the `apt-get` method to install them for Linux OS.

```
sudo apt-get install libsdl2-dev

sudo apt-get install libsdl2-image-dev

sudo apt-get install libsdl2-mixer-dev
```

To build the executable, we can follow the steps below:

1. Clone the starter repository.
2. Make a build directory in the top level directory: `mkdir build_Linux && cd build_Linux`
3. Compile: `cmake .. && make`
4. Run it: `cd .. && ./build_Linux/SnakeGame`

## Project Description

I modified starter codes in the [CppND-Capstone-Snake-Game](https://github.com/udacity/CppND-Capstone-Snake-Game) GitHub repository to add some obstacles on the map, so when the
Snake hits it, Snake dies. Program will check and make sure spawned food on on obstacle as well 

The Snake game code consists of four main classes: `Game`, `Snake`, `Controller`, `MessageQueue`, `Renderer` and `Obstacle`.

1. To begin, `main` creates a `Controller`, a `Game`, a `Renderer`, and a `Obstacle` object. `Game` stores a `Snake` object as part of the state.
2. `main` calls `Game::Run` to start the background music and game loop.
3. `Controller` accepts directional input as well as speed input
4. `MessageQueue` acts as signal channel to send signal to thread and starts the `RampUp` and `RampUp_counter`, it will counts down 3 seconds before speed increase 

# 5 total criteria from the rest of the rubric are addressed

1. A variety of control structures are used in the project.
2. The project accepts input from a user.
3. The project code is organized into classes.
4. All class data members are explicitly specified.
5. Class constructors utilize member initialization lists.
6. At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor.
7. For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object.
8. The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers.
9. A std::condition_variable is used in the project code to synchronize thread execution.

Criterion `1` is implemented in `renderer.cpp` at line `55 `, in `Obstacle` at line `10`,`17`,`33`, and `35`

Criterion `2` is implemented in `snake.cpp` at line `107 `.

Criterion `3` is implemented that the Snake game code consists of four main classes: `Game`, `Snake`, `Controller`,  `Renderer` and `Obstacle`.

Criterion `4` is implemented in `obstacle.h` in line `9` and `20`.

Criterion `5`  is implemented in `obstacle.h` in line `10` through `15`.

Criterion `6` is implemented in `game.cpp` in line `28`.

Criterion `7` is implemented in `snake.cpp` in line `7` through `24`.

Criterion `8` is implemented in `game.cpp` in line `28`.

Criterion `9` is implemented in `snake.cpp` in line `7` through `24`.

