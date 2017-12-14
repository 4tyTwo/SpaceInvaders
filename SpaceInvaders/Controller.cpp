#include "Controller.h"



Controller::Controller()
{
  direction = sf::Vector2i(-1,0);
  globalspeed = 30;
  lag = 1700;
  laststep = clock();
}

Controller::Controller(int rows, int collumns) {
  direction = sf::Vector2i(-1, 0);
  globalspeed = 30;
  lag = 1500;
  laststep = clock();
  for (int i=0;i<rows;i++)
    matrix.push_back(std::vector<Enemy>(collumns));
}

void Controller::initialize() {
  std::vector< std::vector< Enemy > > item(5, std::vector<Enemy>(10));
  matrix = item;
  int span = 30,basex,basey = 60,sizex = 39, sizey = 28;
  basex = window->getSize().x - (sizex*matrix[0].size() + span*(matrix[0].size()-1));
  for (int i = 0; i<matrix.size(); i++){
    for (int j = 0; j < matrix[i].size(); j++) {
      matrix[i][j].setcordinates(basex + j*span + j*sizex,basey + i*(span/2) + i*sizey);
      matrix[i][j].setsize(48,48);
      matrix[i][j].setreward(matrix.size()*10 - i*10);
      matrix[i][j].setspeed(50);
      matrix[i][j].sethealth(1);
      matrix[i][j].setlaserdamage(1);
      matrix[i][j].setlaserdirection(sf::Vector2i(0, 1));
      matrix[i][j].settexture("D:\\Source\\Invader" + std::to_string(i)+".jpg");
    }
  }
  
}

bool Controller::isemptybelow(int row, int collumn) {
  if (row != matrix.size()-1)
    for (int j = row+1; j < matrix.size(); j++)
      if (matrix[j][collumn].gethealth())
        return false;
  return true;      
}

int Controller::rightestcollumn() {
  for (int i = matrix[0].size() - 1; i > -1; i--) 
    for (int j = matrix.size()-1; j>-1;j--)
      if (matrix[j][i].gethealth())
        return i;
  return -1; //если пустая
}

int Controller::leftestcollumn() {
  for (int i = 0; i < matrix[0].size(); i++)
    for (int j = 0; j<matrix.size(); j++)
      if (matrix[j][i].gethealth())
        return i;
  return -1; //если пустая
}

int Controller::bottomrow() {
  for (int i = matrix.size()-1;i>-1;i--)
    for (int j=0;j<matrix[i].size();j++)
      if (matrix[i][j].gethealth())
        return i;
  return -1;
}


void Controller::fire(MyVector<Projectile>* proj) {
  for (int i=0;i<matrix.size();i++)
    for (int j=0;j<matrix[i].size();j++)
      if (isemptybelow(i,j) && matrix[i][j].gethealth())
        matrix[i][j].trytoshoot(*proj);
}

void Controller::moveleft() {
  if (matrix[0][leftestcollumn()].getcordinates().x > 0 + matrix[0][leftestcollumn()].getsize().x)
    for (int i=0;i<matrix.size();i++)
      for (int j=0;j<matrix[i].size();j++){
          matrix[i][j].setspeed(globalspeed);
          matrix[i][j].setdirection(direction);
          matrix[i][j].move();
          direction = sf::Vector2i(-1, 0);
      }
  else
    direction = sf::Vector2i(1, 0);
}

bool Controller::movedown() {
  if (matrix[bottomrow()][0].getcordinates().y < window->getSize().y - 72 - matrix[bottomrow()][0].getsize().y){
    for (int i = 0; i<matrix.size(); i++)
      for (int j = 0; j<matrix[i].size(); j++) {
          matrix[i][j].setdirection(sf::Vector2i(0,1));
          matrix[i][j].setspeed(60);//замени на константу
          matrix[i][j].move();
        }
    if (lag >= 720)//lag всегда хотя
      lag -= 220;
    if (matrix[bottomrow()][0].getcordinates().y + 60 < window->getSize().y - 90)
      return true;
    else
      return false;
  }
  else
    return false;
}

void Controller::moveright() {
  if (matrix[0][rightestcollumn()].getcordinates().x + matrix[0][rightestcollumn()].getsize().x < window->getSize().x- matrix[0][rightestcollumn()].getsize().x)
    for (int i = 0; i<matrix.size(); i++)
      for (int j = 0; j<matrix[i].size(); j++) {
        matrix[i][j].setspeed(globalspeed);
        matrix[i][j].setdirection(direction);
        matrix[i][j].move();
        direction = sf::Vector2i(1, 0);
      }
  else
    direction = sf::Vector2i(-1, 0);
}

bool Controller::movecontrol() {
  clock_t curr = clock();
  if (curr > laststep + lag) {
    laststep = clock();
    switch (direction.x)
    {
    case -1: {
      moveleft();
      if (direction.x == 1)
        if (movedown()) {
          direction = sf::Vector2i(1,0);
          return true;
        }
          else
            return false;  
      else
          break;    
      }
    case 1: {
      moveright();
      if (direction.x == -1)
        if (movedown()) {
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
  for (int i = 0; i<matrix.size(); i++)
    for (int j = 0; j<matrix[i].size(); j++)
      if (matrix[i][j].gethealth())
        window->draw(matrix[i][j].getsprite());
}

int Controller::collision(MyVector<Projectile>& laser) {
  for (int i=matrix.size()-1;i >=0 && laser.size();i--)
    for (int j=0;j<matrix[i].size() && laser.size();j++)
      for (int k=0;k<laser.size();k++)
        if (laser[k].checkcollision(&matrix[i][j]) && matrix[i][j].gethealth()) {
          matrix[i][j].sufferdamage(laser[k].getdamage());
          laser.erase(k);
          return matrix[i][j].getreward();
      }
  return 0;
}

bool Controller::isEmpty() {
  for (int i=0;i<matrix.size();i++)
    for(int j=0;j<matrix[i].size();j++)
      if (matrix[i][j].gethealth())
        return false;
  return true;
}

Controller::~Controller()
{
}
