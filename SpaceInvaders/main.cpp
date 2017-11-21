#include<iostream>
#include "Spaceship.h"
#include "Projectile.h"
#include <Windows.h>
#include <time.h>
//#include "Enemy.h"
#include "Controller.h"
void collisioncheck(std::vector<Enemy> &spaceshipvector, std::vector<Projectile> &laservector) {
  for (int i = 0; i < spaceshipvector.size() && laservector.size(); i++) {
    if (laservector[0].checkcollision(spaceshipvector[i])) {
      spaceshipvector[i].sufferdamage(laservector[0].getdamage());
      if (spaceshipvector[i].gethealth() <= 0)
        spaceshipvector.erase(spaceshipvector.begin() + i);
      laservector.pop_back();
      break;
    }
  }
}
void collisioncheck(std::vector<Spaceship> &spaceshipvector, std::vector<Projectile> &laservector) {
  for (int i = 0; i < spaceshipvector.size() && laservector.size(); i++) {
    if (laservector[0].checkcollision(spaceshipvector[i])) {
      spaceshipvector[i].sufferdamage(laservector[0].getdamage());
      if (spaceshipvector[i].gethealth() <= 0)
        spaceshipvector.erase(spaceshipvector.begin() + i);
      laservector.pop_back();
      break;
    }
  }
}
int main() {
  clock_t start, end,lastshot=0;
  sf::RenderWindow Window(sf::VideoMode(1000,600),"Space Invaders", sf::Style::Close);
  std::vector<Projectile> projectilevector,laservector;
  std::vector<Spaceship> spaceshipvector;
  std::vector<Enemy> matr;
  Spaceship gunship;
  Enemy enemy;
  Controller ctrl(1,1);
  gunship.settexture("D:\Gunship.png");
  gunship.setsize(98,62);
  gunship.setcordinates(1100,590);
  gunship.setspeed(10);
  gunship.sethealth(1);
  gunship.setlaserdamage(1);
  gunship.setlaserdirection(sf::Vector2i(0,-1));
  enemy.settexture("D:\Invader.jpg");
  enemy.setsize(48,48);
  enemy.setcordinates(300,250);
  enemy.setdirection(sf::Vector2i(1,0));
  enemy.setspeed(2);
  enemy.setlaserdirection(sf::Vector2i(0,1));
  enemy.sethealth(55);
  spaceshipvector.push_back(gunship);
  //matr.push_back(enemy);
  ctrl.matrix[0][0] = enemy;
  while (Window.isOpen()) {
    start = clock();
    Window.clear(sf::Color::Black);
    sf::Event Event;
    while (Window.pollEvent(Event)){
    if (Event.type == sf::Event::Closed)
      Window.close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && spaceshipvector.size()) {
         spaceshipvector[0].setdirection(sf::Vector2i(-1,0));
         spaceshipvector[0].move();
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && spaceshipvector.size()) {
          spaceshipvector[0].setdirection(sf::Vector2i(1, 0));
          spaceshipvector[0].move();
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !laservector.size() && spaceshipvector.size()){
          laservector.push_back(spaceshipvector[0].shoot());
      }
      for (int i = 0; i < matr.size(); i++) {//Выстрелы ботов (пока упрощенно, когда завезу матрицу будет лучше
        matr[i].trytoshoot(projectilevector);
      }
      for (int i = 0; i < projectilevector.size(); i++) {//Проверка
        projectilevector[i].move();
        if (!(projectilevector[0].getcordinates().y < 600 - projectilevector[0].getsize().y))
            projectilevector.erase(projectilevector.begin() + i--);
      }
      if (laservector.size()){//Проверка коллизии для снаряда игрока
        laservector[0].move();
        if (!(laservector[0].getcordinates().y > 0))
          laservector.pop_back();
        }
      collisioncheck(matr, laservector);
      collisioncheck(spaceshipvector, projectilevector);
      /*for (int i = 0; i < matr.size(); i++)
        Window.draw(matr[i].getsprite());*/
      ctrl.movecontrol();
      ctrl.render(&Window);
      for (int i = 0; i < laservector.size(); i++)
        Window.draw(laservector[i].getsprite());
      for (int i = 0; i < projectilevector.size(); i++)
        Window.draw(projectilevector[i].getsprite());
    if (spaceshipvector.size())
      Window.draw(spaceshipvector[0].getsprite());
    Window.display();
    end = clock();
    if ((int)((((end - start) + 0.0) / CLOCKS_PER_SEC) * 1000)<=20)
     Sleep(20 - (int)((((end - start) + 0.0) / CLOCKS_PER_SEC) * 1000));
  }
}