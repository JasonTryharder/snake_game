#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <mutex>
#include <deque>
#include <thread>
#include <algorithm>
#include <condition_variable>
#include "SDL.h"
#include "obstacle.h"
template <class T>
class MessageQueue
{
public:
    // MessageQueue<T>();
    T receive();
    void send(T &&msg);
private:
    std::deque<T> _queue; // currently only one element in the queue
    std::condition_variable _cond;
    std::mutex _mutex;
};

class Snake : public std::enable_shared_from_this<Snake> {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight ,kW ,kS };

  Snake(int grid_width, int grid_height,Obstacle &obstacle)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2),
        obstacle(obstacle) {
        // SetInitialSpeed();
        }

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kLeft;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
  void SetInitialSpeed();
  
  bool growing{false};
  int grid_width;
  int grid_height;
  int speedType;
  Obstacle obstacle;
};

#endif