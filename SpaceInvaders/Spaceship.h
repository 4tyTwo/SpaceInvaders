#pragma once
#include "GameObj.h"
#include "Projectile.h"
class Spaceship : public GameObj //Класс описывает как корабль игрока, так и противника, т.к. в сущности они ничем не отличаются
{
public:
Spaceship();
virtual void move();
void setdirection(sf::Vector2i indirection);
inline sf::Vector2i getdirection() { return direction; };
inline void setspeed(int inspeed) { speed = abs(inspeed); };
inline int getspeed() { return speed; };
inline sf::Vector2i getlaserdirection() { return laserdirection; };
void setlaserdirection(sf::Vector2i indirection);
inline int getlaserdamage() { return laserdamage; } ;
void setlaserdamage(int indamage);
virtual Projectile shoot();
virtual ~Spaceship();
private:
sf::Vector2i direction, laserdirection;
int speed, laserdamage;
};

