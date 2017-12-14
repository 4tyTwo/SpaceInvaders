#pragma once
#include<sfml/Graphics.hpp>
#include <list>
class GameObj //����������� �����, �� �������� ����� ������������� ��������� �������
{
public:
  GameObj();
  inline sf::Vector2i getsize() { return size; };
  inline sf::Vector2i getcordinates() { return cord; };
  inline int gethealth() { return health ;};
  inline int getreward() { return reward; };
  void setsize(sf::Vector2i inSize);
  void setsize(int x, int y);
  void setcordinates(sf::Vector2i cordinates);
  void setcordinates(int x, int y);
  void sethealth(int inhealth);
  inline void setreward(int inreward) {reward = inreward;};
  void settexture(std::string path);
  virtual void move();
  inline void sufferdamage(int damage) { health-=damage; };
  sf::Sprite getsprite();
  virtual ~GameObj() = 0 {}
protected:
  sf::Texture texture;//�������� �������
  sf::Vector2i size,cord; //������� (������, ������) � ��������� (x,y)
  int health, reward;//����� ��������� ������� � ������� �� ���������� �������
};

