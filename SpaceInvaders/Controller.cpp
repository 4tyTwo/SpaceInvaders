#include "Controller.h"

Controller::Controller()//задает 1/1
{
  direction = sf::Vector2i(-1,0);
  globalspeed = 30;
  lag = 1700;
  laststep = clock();
  matrix = std::vector< std::vector<Enemy> >(1, std::vector<Enemy>(1));
}

Controller::Controller(int rows, int collumns) {
  direction = sf::Vector2i(-1, 0);
  globalspeed = 30;
  lag = 1500;
  laststep = clock();
  std::vector< std::vector< Enemy > > item(rows, std::vector<Enemy>(collumns));
  matrix = item;
}

void Controller::initialize() {
  std::vector< std::vector< Enemy > > item(5, std::vector<Enemy>(10));
  matrix = item;
  int span = 30,basex,basey = 60,sizex = 39, sizey = 28;
  basex = window->getSize().x - (sizex*matrix[0].size() + span*(matrix[0].size()-1));
  for (auto i = 0; i<matrix.size(); i++){
    for (auto j = 0; j < matrix[i].size(); j++) {
      matrix[i][j].setCordinates(basex + j*span + j*sizex,basey + i*(span/2) + i*sizey);
      matrix[i][j].setSize(48,48);
      matrix[i][j].setReward(matrix.size()*10 - i*10);
      matrix[i][j].setSpeed(50);
      matrix[i][j].setHealth(1);
      matrix[i][j].setLaserDamage(1);
      matrix[i][j].setLaserDirection(sf::Vector2i(0, 1));
      matrix[i][j].setTexture("C:\\Source\\Invader" + std::to_string(i)+".jpg");
    }
  }
  
}

bool Controller::isemptybelow(int row, int collumn) {
  if (row != matrix.size()-1)
    for (auto j = row+1; j < matrix.size(); j++)
      if (matrix[j][collumn].getHealth())
        return false;
  return true;      
}

int Controller::rightestcollumn() {
  for (int i = matrix[0].size() - 1; i > -1; i--) 
    for (int j = matrix.size()-1; j>-1;j--)
      if (matrix[j][i].getHealth())
        return i;
  return -1; //если пустая
}

int Controller::leftestcollumn() {
  for (int i = 0; i < matrix[0].size(); i++)
    for (int j = 0; j<matrix.size(); j++)
      if (matrix[j][i].getHealth())
        return i;
  return -1; //если пустая
}

int Controller::bottomrow() {
  for (int i = matrix.size()-1;i>-1;i--)
    for (int j=0;j<matrix[i].size();j++)
      if (matrix[i][j].getHealth())
        return i;
  return -1;
}


void Controller::fire(MyVector<Projectile>* proj) {
  for (int i=0;i<matrix.size();i++)
    for (int j=0;j<matrix[i].size();j++)
      if (isemptybelow(i,j) && matrix[i][j].getHealth())
        matrix[i][j].trytoshoot(*proj);
}

void Controller::moveLeft() {
  if (matrix[0][leftestcollumn()].getCordinates().x > 0 + matrix[0][leftestcollumn()].getSize().x)
    for (auto i=0;i<matrix.size();i++)
      for (auto j=0;j<matrix[i].size();j++){
          matrix[i][j].setSpeed(globalspeed);
          matrix[i][j].setdirection(direction);
          matrix[i][j].move();
          direction = sf::Vector2i(-1, 0);
      }
  else
    direction = sf::Vector2i(1, 0);
}

bool Controller::moveDown() {
  if (matrix[bottomrow()][0].getCordinates().y < window->getSize().y - 72 - matrix[bottomrow()][0].getSize().y){
    for (auto i = 0; i<matrix.size(); i++)
      for (auto j = 0; j<matrix[i].size(); j++) {
          matrix[i][j].setdirection(sf::Vector2i(0,1));
          matrix[i][j].setSpeed(60);//замени на константу
          matrix[i][j].move();
        }
    if (lag >= 720)//lag всегда хотя
      lag -= 220;
    if (matrix[bottomrow()][0].getCordinates().y + 60 < window->getSize().y - 90)
      return true;
    else
      return false;
  }
  else
    return false;
}

void Controller::moveRight() {
  if (matrix[0][rightestcollumn()].getCordinates().x + matrix[0][rightestcollumn()].getSize().x < window->getSize().x- matrix[0][rightestcollumn()].getSize().x)
    for (auto i = 0; i<matrix.size(); i++)
      for (auto j = 0; j<matrix[i].size(); j++) {
        matrix[i][j].setSpeed(globalspeed);
        matrix[i][j].setdirection(direction);
        matrix[i][j].move();
        direction = sf::Vector2i(1, 0);
      }
  else
    direction = sf::Vector2i(-1, 0);
}

bool Controller::moveControl() {
  clock_t curr = clock();
  if (curr > laststep + lag) {
    laststep = clock();
    switch (direction.x)
    {
    case -1: {
      moveLeft();
      if (direction.x == 1)
        if (moveDown()) {
          direction = sf::Vector2i(1,0);
          return true;
        }
          else
            return false;  
      else
          break;    
      }
    case 1: {
      moveRight();
      if (direction.x == -1)
        if (moveDown()) {
          direction = sf::Vector2i(-1, 0);
          return true;
        }
        else
          return false;
      else
        break;
     }
  }
}
}

void Controller::render() {
  for (auto i = 0; i<matrix.size(); i++)
    for (auto j = 0; j<matrix[i].size(); j++)
      if (matrix[i][j].getHealth())
        window->draw(matrix[i][j].getSprite());
}

int Controller::collision(MyVector<Projectile>& laser) {
  for (int i=matrix.size()-1;i >=0 && laser.size();i--)
    for (int j=0;j<matrix[i].size() && laser.size();j++)
      for (int k=0;k<laser.size();k++)
        if (laser[k].checkCollision(&matrix[i][j]) && matrix[i][j].getHealth()) {
          matrix[i][j].sufferdamage(laser[k].getdamage());
          laser.erase(k);
          return matrix[i][j].getreward();
      }
  return 0;
}

bool Controller::isEmpty() {
  for (int i=0;i<matrix.size();i++)
    for(int j=0;j<matrix[i].size();j++)
      if (matrix[i][j].getHealth())
        return false;
  return true;
}

Controller::~Controller()
{
}
