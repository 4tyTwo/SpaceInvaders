#pragma once
#include "Enemy.h"
class Controller
{
public:
  Controller();
  Controller(int rows,int collumns);
  bool isemptybelow(int row,int collumn); //�������� ����� �� ��� �������� (����� ��������)
  void render(); //���������� ��� ������� � �������
  void moveLeft(); //��� �����
  bool moveDown(); //��� ����
  void moveRight(); //��� ������
  bool moveControl();//���� ������ ����� � ���� ����
  int rightestcollumn();//����� ������ ������� � ������ ���������
  int leftestcollumn();//���������� �����������
  int bottomrow();//����� ������ ��� � ������ ���������
  void initialize();//������� ����� ������� �������, � ������� ����������� ��������
  void fire(MyVector<Projectile>* proj);
  sf::RenderWindow* window; // ������ � ����
  int collision(MyVector<Projectile>& laser);
  bool isEmpty();
  ~Controller();
private:
  std::vector<std::vector<Enemy>> matrix;
  int globalspeed;
  clock_t laststep,lag;//laststep - ����� ���������� ��������. lag - �������� ����� ���������
  sf::Vector2i direction;
};

