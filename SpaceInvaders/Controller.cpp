#include "Controller.h"



Controller::Controller()
{
  direction = sf::Vector2i(-1,0);
  globalspeed = 2;
}

Controller::Controller(int rows, int collumns) {
  direction = sf::Vector2i(-1, 0);
  globalspeed = 2;
  for (int i=0;i<rows;i++)
    matrix.push_back(std::vector<Enemy>(collumns));
}

bool Controller::isemptybelow(int row, int collumn) {
  for (int j = row; j < matrix.size(); j++)
    if (matrix[j][collumn].gethealth())
      return false;
  return true;      
}

bool Controller::iscollumnempty(int collumn) {
  if (collumn < 0 || collumn > matrix[0].size())
    return true;
  for (int i=0;i<matrix.size();i++)
    if (matrix[i][collumn].gethealth())
      return false;
  return true;
}

void Controller::moveleft() {
  for (int i=0;i<matrix.size();i++)
    for (int j=0;j<matrix[i].size();j++)
      if (matrix[i][j].getcordinates().x > 50) {
        matrix[i][j].setdirection(direction);
        matrix[i][j].move();
        }
        else{
          direction = sf::Vector2i(1, 0);
          return;
        }
  direction = sf::Vector2i(-1, 0);
}

bool Controller::movedown() {
  for (int i = 0; i<matrix.size(); i++)
    for (int j = 0; j<matrix[i].size(); j++)
      if (matrix[i][j].getcordinates().y < 590) {
        matrix[i][j].setdirection(sf::Vector2i(0,1));
        matrix[i][j].setspeed(40);
        matrix[i][j].move();
        matrix[i][j].setspeed(globalspeed++);
      }
      else
       return false;
  return true;
}

void Controller::moveright() {
  for (int i = 0; i<matrix.size(); i++)
    for (int j = 0; j<matrix[i].size(); j++)
      if (matrix[i][j].getcordinates().x < 950 + matrix[i][j].getspeed()){
        matrix[i][j].setdirection(direction);
        matrix[i][j].move();
      }
      else {
        direction = sf::Vector2i(-1, 0);
        return;
      }
  direction = sf::Vector2i(1,0);
}

bool Controller::movecontrol() {
  switch (direction.x)
  {
  case -1: {
    moveleft();
    if (direction.x == 1)
        return (movedown());
    else
        break;    
    }
  case 1: {
    moveright();
    if (direction.x == -1)
      return (movedown());
    else
      break;
   }
  }
}

void Controller::render(sf::RenderWindow* window) {
  for (int i = 0; i<matrix.size(); i++)
    for (int j = 0; j<matrix[i].size(); j++)
      window->draw(matrix[i][j].getsprite());
}


Controller::~Controller()
{
}
