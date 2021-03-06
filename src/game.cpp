#include "game.h"
#include <iostream>
#include "SDL.h"
#include <future>
// #include "MessageQueue.h"

// random generator could generate food outside of grid due to random_w/h range from 0-32, which 32 is should not be included, hence grid_width/height - 1
Game::Game(std::size_t grid_width, std::size_t grid_height,Obstacle &obstacle)
    : snake(grid_width, grid_height,obstacle), 
      engine(dev()),
      random_w(0, static_cast<int>(grid_width-1)),
      random_h(0, static_cast<int>(grid_height-1)),
      obstacle(obstacle) {
  PlaceFood();
}
// void Game::Run(Controller &controller, Renderer &renderer,
//                std::size_t target_frame_duration)
void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  rampUp_counter = 0;
  // renderer.Render(snake, food);
  // std::getchar();
  queue = std::make_shared<MessageQueue<int>>();
  while (running) {
    frame_start = SDL_GetTicks();
    // Input, Update, Render - the main game loop.
    // controller.SpeedInput(running, snake);
    controller.HandleInput(running, snake);
  // std::cout<< " i am here " << std::endl;
    Update();
    renderer.Render(snake, food);

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
    if (score - counter ==2)
    {
      //start timer
      rampUp_counter ++;
      std::future<void> t1 = std::async(std::launch::async,&MessageQueue<int>::send, queue, std::move(rampUp_counter));
      rampUp_counter = queue->receive();//permission granted 
      RampUp();
      std::cout << "speed increased! "<< std::endl;
      std::cout<< "rampUp counter is "<< rampUp_counter << std::endl;
      counter = score;}
  }
  // t1.join();
  
  
}

void Game::RampUp(){
  std::lock_guard<std::mutex> Speed_lock(_mtxSpped);
  snake.speed = snake.speed + 0.05;
}
void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    // also check location is not occupied by obstacle
    if (!snake.SnakeCell(x, y) & !obstacle.ObstacleCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }

    // if (!obstacle.ObstacleCell(x, y)) {
    //   food.x = x;
    //   food.y = y;
    //   return;
    // }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }