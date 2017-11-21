#pragma once
#include "Spaceship.h"
class Enemy :
  public Spaceship
{
public:
  Enemy();
  virtual void trytoshoot(std::vector<Projectile> &vect);
  ~Enemy();
private:
  int lastshot;
};

