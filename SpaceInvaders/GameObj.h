#pragma once
#include<sfml/Graphics.hpp>
#include <list>
class GameObj //����������� �����, �� �������� ����� ������������� ��������� �������
{
public:
  GameObj();
  inline sf::Vector2i getSize() { return size; };
  inline sf::Vector2i getCordinates() { return cord; };
  inline int getHealth() { return health ;};
  inline int getreward() { return reward; };
  void setSize(sf::Vector2i inSize);
  void setSize(int x, int y);
  void setCordinates(sf::Vector2i cordinates);
  void setCordinates(int x, int y);
  void setHealth(int inhealth);
  inline void setReward(int inreward) {reward = inreward;};
  void setTexture(std::string path);
  virtual void move() = 0;
  inline void sufferdamage(int damage) { health-=damage; };
  sf::Sprite getSprite();
  virtual ~GameObj() = 0 {}
protected:
  sf::Texture texture;//�������� �������
  sf::Vector2i size,cord; //������� (������, ������) � ��������� (x,y)
  int health, reward;//����� ��������� ������� � ������� �� ���������� �������
};

