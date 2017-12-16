#include "GameObj.h"

GameObj::GameObj(){

}

void GameObj::setTexture(std::string path) {
  texture.loadFromFile(path);
}

sf::Sprite GameObj::getSprite() {
  sf::Sprite objsprite;
  objsprite.setTexture(texture);
  objsprite.setPosition(sf::Vector2f(cord));
  return objsprite;
}

void GameObj::setCordinates(sf::Vector2i cordinates) {
  cord = cordinates;
  if (cord.x < 0)
      cord.x=0;
  if (cord.x > 1200-size.x)
      cord.x=1200-size.x;
  if (cord.y < 0)
    cord.y = 0;
  if (cord.y > 690 - size.y)
    cord.y = 690 - size.y;
}

void GameObj::setSize(int x, int y) {
  size=sf::Vector2i(x,y);
}

void GameObj::setHealth(int inhealth) {
  health = (inhealth>0)? inhealth : 1;
}

void GameObj::setSize(sf::Vector2i inSize) {
  size = inSize;
}

void GameObj::setCordinates(int x, int y) {
  setCordinates(sf::Vector2i(x,y));
}
