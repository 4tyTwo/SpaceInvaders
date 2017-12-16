#include "Projectile.h"

Projectile::Projectile()
{
}

Projectile::Projectile(std::string texturepath, int indamage, int inspeed, 
                       sf::Vector2i indirection, sf::Vector2i incordinates) {
  setTexture(texturepath);
  setSize(6,10);
  damage = indamage;
  speed = inspeed;
  direction = indirection;
  setCordinates(incordinates);
}

Projectile::~Projectile()
{

}

void Projectile::move() {
  setCordinates(getCordinates() + (direction*speed));
}

bool Projectile::checkCollision(GameObj* object) {
  if (direction == sf::Vector2i(0, -1)) {//Снизу вверх
    if (cord.y > object->getCordinates().y && cord.y < object->getCordinates().y + object->getSize().y 
    &&  (cord.x + size.x >= object->getCordinates().x && cord.x <= object->getCordinates().x +
    object->getSize().x))
        return true;
     else
        return false;
    }
    if (direction == sf::Vector2i(0, 1)) {
      if (cord.y + size.y > object->getCordinates().y && (cord.x + size.x >= object->getCordinates().x 
        && cord.x <= object->getCordinates().x +
        object->getSize().x))
        return true;
      else
        return false;
    }
}