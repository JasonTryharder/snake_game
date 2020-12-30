#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
    public:
    void HandleInput(bool &running, Snake &snake) const;
    void SpeedInput(bool &running, Snake &snake) const;
    private:
    void ChangeDirection(Snake &snake, Snake::Direction input,Snake::Direction opposite) const;
    void ChangeSpeed(Snake &snake, Snake::Direction input) const;

};

#endif