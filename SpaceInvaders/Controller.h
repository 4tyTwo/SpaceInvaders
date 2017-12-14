#pragma once
#include "Enemy.h"
class Controller
{
public:
  Controller();
  Controller(int rows,int collumns);
  bool isemptybelow(int row,int collumn);
  void render();
  void moveleft();
  bool movedown();
  void moveright();
  bool movecontrol();//���� ������ ����� � ���� ����
  int rightestcollumn();
  int leftestcollumn();
  int bottomrow();
  ~Controller();
  void initialize();//������� ����� ������� �������, � ������� ����������� ��������
  void fire(MyVector<Projectile>* proj);
  std::vector<std::vector<Enemy>> matrix;
  sf::RenderWindow* window;
  int collision(MyVector<Projectile>& laser);
  bool isEmpty();
private:
  int globalspeed;
  clock_t laststep,lag;//laststep - ����� ���������� ��������. lag - �������� ����� ���������
  sf::Vector2i direction;
};

