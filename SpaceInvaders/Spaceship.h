#pragma once
#include "GameObj.h"
#include "Projectile.h"
class Spaceship : public GameObj //����� ��������� ��� ������� ������, ��� � ����������, �.�. � �������� ��� ����� �� ����������
{
public:
Spaceship();
virtual void move();
void setdirection(sf::Vector2i indirection);
inline sf::Vector2i getdirection() { return direction; };
inline void setSpeed(int inspeed) { speed = abs(inspeed); };
inline int getspeed() { return speed; };
inline sf::Vector2i getlaserdirection() { return laserdirection; };
void setLaserDirection(sf::Vector2i indirection);
inline int getlaserdamage() { return laserdamage; } ;
void setLaserDamage(int indamage);
virtual Projectile shoot();
virtual ~Spaceship();
private:
sf::Vector2i direction, laserdirection;
int speed, laserdamage;
};

