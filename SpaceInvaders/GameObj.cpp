#include "GameObj.h"

GameObj::GameObj(){

}

GameObj::~GameObj(){

}
void GameObj::settexture(std::string path) {
  texture.loadFromFile(path);
}

sf::Sprite GameObj::getsprite() {
  sf::Sprite objsprite;
  objsprite.setTexture(texture);
  objsprite.setPosition(sf::Vector2f(cord));
  return objsprite;
}

void GameObj::setcordinates(sf::Vector2i cordinates) {
  cord = cordinates;
  if (cord.x < 0)
      cord.x=0;
  if (cord.x > 1000-size.x)
      cord.x=1000-size.x;
  if (cord.y < 0)
    cord.y = 0;
  if (cord.y > 600 - size.y)
    cord.y = 600 - size.y;
}

void GameObj::setsize(int x, int y) {
  size=sf::Vector2i(x,y);
}

void GameObj::sethealth(int inhealth) {
  health = (inhealth>0)? inhealth : 1;
}

void GameObj::setsize(sf::Vector2i inSize) {
  size = inSize;
}

void GameObj::setcordinates(int x, int y) {
  setcordinates(sf::Vector2i(x,y));
}

void GameObj::move() {
  //Pass
}