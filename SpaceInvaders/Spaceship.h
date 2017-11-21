#pragma once
#include "GameObj.h"
#include "Projectile.h"
class Spaceship : public GameObj //����� ��������� ��� ������� ������, ��� � ����������, �.�. � �������� ��� ����� �� ����������
{
public:
Spaceship();
virtual void move();
virtual void setdirection(sf::Vector2i indirection);
virtual inline sf::Vector2i getdirection() { return direction; };
virtual inline void setspeed(int inspeed) { speed = abs(inspeed); };
virtual inline int getspeed() { return speed; };
virtual inline sf::Vector2i getlaserdirection() { return laserdirection; };
virtual void setlaserdirection(sf::Vector2i indirection);
virtual inline int getlaserdamage() { return laserdamage; } ;
virtual void setlaserdamage(int indamage);
Projectile shoot();
~Spaceship();
private:
sf::Vector2i direction, laserdirection;
int speed, laserdamage;
};

