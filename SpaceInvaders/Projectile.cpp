#include "Projectile.h"



Projectile::Projectile()
{
}

Projectile::Projectile(std::string texturepath, int indamage, int inspeed, sf::Vector2i indirection, sf::Vector2i incordinates) {
  settexture(texturepath);
  setsize(6,10);
  damage = indamage;
  speed = inspeed;
  direction = indirection;
  setcordinates(incordinates);
}

Projectile::~Projectile()
{

}

void Projectile::move() {
  setcordinates(getcordinates() + (direction*speed));
}

bool Projectile::checkcollision(GameObj object) {
  if (direction == sf::Vector2i(0, -1)) {//Снизу вверх
    if (cord.y < object.getcordinates().y + object.getsize().y && (cord.x + size.x >= object.getcordinates().x && cord.x <= object.getcordinates().x + 
    object.getsize().x))
        return true;
     else
        return false;
    }
    if (direction == sf::Vector2i(0, 1)) {
      if (cord.y + size.y > object.getcordinates().y && (cord.x + size.x >= object.getcordinates().x && cord.x <= object.getcordinates().x +
        object.getsize().x))
        return true;
      else
        return false;
    }
}