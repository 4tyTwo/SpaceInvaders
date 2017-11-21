#pragma once
#include "Enemy.h"
class Controller
{
public:
  Controller();
  Controller(int rows,int collumns);
  bool isemptybelow(int row,int collumn);
  void render(sf::RenderWindow* window);
  bool iscollumnempty(int collumn);
  void moveleft();//—ама решает когда и куда идти
  bool movedown();
  void moveright();
  bool movecontrol();
  ~Controller();
  std::vector<std::vector<Enemy>> matrix;
private:
  int globalspeed;
  sf::Vector2i direction;
};

