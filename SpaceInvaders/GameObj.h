#pragma once
#include<sfml/Graphics.hpp>
#include <list>
class GameObj //Абстрактный класс, от которого будут наследоваться остальные объекты
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
  /*virtual sf::Vector2i getdirection();
  virtual void setdirection(sf::Vector2i indirection);
  virtual int getspeed();
  virtual void setspeed(int inspeed);
  virtual sf::Vector2i getlaserdirection();
  virtual void setlaserdirection(sf::Vector2i indirection);
  virtual int getlaserdamage();
  virtual void setlaserdamage(int indamage);*/
  sf::Sprite getsprite();
  virtual ~GameObj();
  std::string type;
protected:
  sf::Texture texture;//Текстура объекта
  sf::Vector2i size,cord; //Размеры (высота, ширина) и кординаты (x,y)
  int health, reward;//Запас прочности объекта и награда за разрушение объекта
};

