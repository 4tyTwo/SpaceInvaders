#include "Enemy.h"



Enemy::Enemy()
{
}

void Enemy::trytoshoot(MyVector<Projectile> &vect) {
  if (((((clock() - lastshot) + 0.0) / CLOCKS_PER_SEC) * 1000 >=8000) && rand()%300 > 298){
    lastshot=clock();
    vect.add(shoot());
  }
}

Projectile Enemy::shoot() {
  Projectile proj("D:\\Projectile.png", getlaserdamage(), 5, sf::Vector2i(0,1), sf::Vector2i(getcordinates().x + getsize().x / 2, getcordinates().y + getsize().y -3));
  return proj;
}

Enemy::~Enemy()
{
}
