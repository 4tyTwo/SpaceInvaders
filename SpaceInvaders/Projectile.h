#pragma once
#include "GameObj.h"
class Projectile :  public GameObj
{
public:
  Projectile();
  Projectile(std::string texturepath, int indamage,int inspeed,sf::Vector2i indirection,sf::Vector2i incordinates);
  void move();
  bool checkcollision(GameObj object);
  inline int getdamage() { return damage; };
  ~Projectile();
private:
  int damage,speed;
  sf::Vector2i direction;
};

