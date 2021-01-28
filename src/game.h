#ifndef GAME_H
#define GAME_H

#include <random>
#include <thread>
#include <mutex>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "obstacle.h"
#include "MessageQueue.h"
class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, Obstacle &obstacle);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  // void Run(Controller &controller, Renderer &renderer,
  // std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;
  Obstacle obstacle;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int counter;
  int rampUp_counter;
  void PlaceFood();
  void Update();
  void RampUp();
  std::mutex _mtxSpped;
  std::shared_ptr<MessageQueue<int>> queue;
};

#endif