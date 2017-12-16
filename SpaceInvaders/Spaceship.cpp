#include "Spaceship.h"

Spaceship::Spaceship(){
}

Spaceship::~Spaceship(){
}

void Spaceship::move() {
  setCordinates(getCordinates() + (direction*speed));
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

void Spaceship::setLaserDirection(sf::Vector2i indirection) {
  if (indirection.x != 1 && indirection.x != 0)
    laserdirection.x = indirection.x / abs(indirection.x);
  else
    laserdirection.x = indirection.x;
  if (indirection.y != 1 && indirection.y != 0)
    laserdirection.y = indirection.y / abs(indirection.y);
  else
    laserdirection.y = indirection.y;
}

void Spaceship::setLaserDamage(int indamage) {
  laserdamage = (indamage>0)? indamage : 1;
}

Projectile Spaceship::shoot() {
  Projectile proj("C:\\Source\\Projectile.png",laserdamage,7,laserdirection, sf::Vector2i(getCordinates().x + getSize().x/2,getCordinates().y - 3));
  return proj;
}