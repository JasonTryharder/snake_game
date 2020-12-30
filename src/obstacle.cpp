#include "obstacle.h"
#include <iostream>
#include "SDL.h"

void Obstacle:: placeObstacle(){

    SDL_Point point;

// place 2 parallel obstacle lines 
    for(int i=0; i<grid_width/2; i++)
    {
        point.x = i + (grid_width/4);
        point.y = grid_height/3;
        obstaclePoints.push_back(point);
    }

    for(int i=0; i<grid_width/2; i++)
    {
        point.x = i + (grid_width/4);
        point.y = 2*(grid_height/3);
        obstaclePoints.push_back(point);
    }
     

}

// return obstacle points
 std::vector<SDL_Point> Obstacle:: get_obstecle(){
     return obstaclePoints;
 }

// check if hit obstacle
 bool Obstacle::ObstacleCell(int x, int y)
{
  for (auto const &item : obstaclePoints)
  {
    if (x == item.x && y == item.y)
    {
      return true;
    }
  }
  return false;
}