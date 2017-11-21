#include "Spaceship.h"

Spaceship::Spaceship()
{
}

Spaceship::~Spaceship()
{
}

void Spaceship::move() {
  setcordinates(getcordinates() + (direction*speed));
}

void Spaceship::setdirection(sf::Vector2i indirection) {
 if (indirection.x != 1 && indirection.x !=0 )
    direction.x = indirection.x/abs(indirection.x);
 else
    direction.x=indirection.x;
 if (indirection.y != 1 && indirection.y != 0)
   direction.y = indirection.y / abs(indirection.y);
 else
   direction.y = indirection.y;
}

void Spaceship::setlaserdirection(sf::Vector2i indirection) {
  if (indirection.x != 1 && indirection.x != 0)
    laserdirection.x = indirection.x / abs(indirection.x);
  else
    laserdirection.x = indirection.x;
  if (indirection.y != 1 && indirection.y != 0)
    laserdirection.y = indirection.y / abs(indirection.y);
  else
    laserdirection.y = indirection.y;
}

void Spaceship::setlaserdamage(int indamage) {
  laserdamage = (indamage>0)? indamage : 1;
}

Projectile Spaceship::shoot() {
  Projectile proj("D:\Projectile.png",laserdamage,5,laserdirection, sf::Vector2i(getcordinates().x + getsize().x/2,getcordinates().y - 3));
  return proj;
}