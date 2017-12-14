#pragma once
#include "Spaceship.h"
#include "MyVectror.h"
class Enemy :
  public Spaceship
{
public:
  Enemy();
  virtual void trytoshoot(MyVector<Projectile> &vect);
  virtual Projectile shoot();
  virtual ~Enemy();
private:
  int lastshot, damage;
};

