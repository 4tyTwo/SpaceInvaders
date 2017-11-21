#include "Enemy.h"



Enemy::Enemy()
{
}

void Enemy::trytoshoot(std::vector<Projectile> &vect) {
  if (((((clock() - lastshot) + 0.0) / CLOCKS_PER_SEC) * 1000 >= 4200) && rand()%200 > 195){
    lastshot=clock();
    vect.push_back(shoot());
  }
}
Enemy::~Enemy()
{
}
