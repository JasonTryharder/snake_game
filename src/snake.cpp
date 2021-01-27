#include "snake.h"
#include <cmath>
#include <iostream>

// create MessageQueue class to pass speed information into snake class to update snake moving speed 
template <typename T>
T MessageQueue<T>::receive()
{
  std::unique_lock<std::mutex>uLock(_mutex); // modify the speed info under the lock
  _cond.wait(uLock,[this]{return !_queue.empty();}); // lambda function pass to conditional variable to wait for notification
  T msg = std::move(_queue.front());
  _queue.pop_front();
  return std::move(msg);
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
  std::lock_guard<std::mutex> uLock(_mutex);
  _queue.emplace_back(msg);
  std::cout<<"count down to increase speed -3 Seconds"<<std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  _cond.notify_one();
}

void Snake::Update()
{
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)}; // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)}; // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y)
  {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead()
{
  switch (direction)
  {
  case Direction::kUp:
    head_y -= speed;
    break;

  case Direction::kDown:
    head_y += speed;
    break;

  case Direction::kLeft:
    head_x -= speed;
    break;

  case Direction::kRight:
    head_x += speed;
    break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell)
{
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing)
  {
    // Remove the tail from the vector.
    body.erase(body.begin());
  }
  else
  {
    growing = false;
    size++;
  }

  // Check if the snake has died by body.
  for (auto const &item : body)
  {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y)
    {
      alive = false;
    }
  }

  // Check if the snake has died by obstacle.
  for (auto const &item : obstacle.get_obstecle())
  {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y)
    {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y)
{
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y))
  {
    return true;
  }
  for (auto const &item : body)
  {
    if (x == item.x && y == item.y)
    {
      return true;
    }
  }
  return false;
}

void Snake::SetInitialSpeed()
{

  std::cout << "Select Snake Speed Level \n 1 - Fast \n 2 - Medium \n Any Key Slow \n";

  std::cin >> Snake::speedType;
  
  if (Snake::speedType == 1)
  {
    Snake::speed = 0.3f;
  }
  else if (Snake::speedType == 2)
  {
    Snake::speed = 0.2f;
  }

}

