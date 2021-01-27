#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  std::cout<< " snake direction is " << snake.speed << std::endl; 
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}
void Controller::ChangeSpeed(Snake &snake , Snake::Direction input) const
{
  std::cout<< " snake speed is " << snake.speed << std::endl; 
  if (snake.speed >= 0.02 && input == Snake::Direction::kS)
  {snake.speed = snake.speed - 0.01;}
  else if (input == Snake::Direction::kW)
  {snake.speed = snake.speed + 0.01;}
  return;
}

// void Controller::SpeedInput(bool &running, Snake &snake) const {
//   SDL_Event e;
//   while (SDL_PollEvent(&e)) {
//     if (e.type == SDL_QUIT) {
//       running = false;
//     } else if (e.type == SDL_KEYDOWN) {
//       switch (e.key.keysym.sym) {
//         case SDLK_w:
//           ChangeSpeed(snake,Snake::Direction::kW);
//           break;

//         case SDLK_s:
//           ChangeSpeed(snake, Snake::Direction::kS);
//           break;
//       }
//     }
//   }
// }

void Controller::HandleInput(bool &running, Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;

        case SDLK_w:
          ChangeSpeed(snake,Snake::Direction::kW);
          break;

        case SDLK_s:
          ChangeSpeed(snake, Snake::Direction::kS);
          break;
      }
    }
  }
}