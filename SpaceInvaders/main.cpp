#include<iostream>
#include "Spaceship.h"
#include "Projectile.h"
#include <Windows.h>
#include <time.h>
#include "MyVectror.h"
#include "Controller.h"


void collisioncheck(MyVector<Spaceship>* spaceshipvector,MyVector<Projectile>* laservector) {
  for (int i = 0; i < laservector->size() && spaceshipvector->size(); i++) {
    if (laservector->get(i).checkcollision(&spaceshipvector->get(0))) {
      spaceshipvector->get(0).sufferdamage(laservector->get(i).getdamage());
      if (spaceshipvector->get(0).gethealth() <= 0)
        spaceshipvector->pop();
      laservector->erase(i);
      break;
    }
  }
}

Spaceship createship() {
  Spaceship tmp;
  tmp.settexture("D:\\Gunship.png");
  tmp.setsize(98, 62);
  tmp.setcordinates(551, 690 - 72);
  tmp.setspeed(10);
  tmp.sethealth(3);
  tmp.setlaserdamage(1);
  tmp.setlaserdirection(sf::Vector2i(0, -1));
  return tmp;
}


int main() {
  srand(time(NULL));
  sf::Font font;
  font.loadFromFile("D:\\Source\\Pixeled.ttf");
  clock_t start, end,lastshot=0;
  sf::RenderWindow Window(sf::VideoMode(1200,690),"Space Invaders", sf::Style::Close);
  Window.setPosition(sf::Vector2i(0,0));
  sf::String info;
  bool gameon = true;
  int score = 0;
  MyVector<Projectile> projectilevector, laservector;
  MyVector<Spaceship> spaceshipvector;
  Controller ctrl;
  spaceshipvector.add(createship());
  sf::Text InfoText;
  InfoText.setFont(font);
  InfoText.setStyle(sf::Text::Regular);
  InfoText.setFillColor(sf::Color::White);
  InfoText.setCharacterSize(20);
  ctrl.window = &Window;
  ctrl.initialize();
  while (Window.isOpen()) {
    sf::Event Event;
    while (Window.pollEvent(Event)) {
      if (Event.type == sf::Event::Closed)
        Window.close();
    }
    start = clock();
    Window.clear(sf::Color::Black);
    if (gameon) {
    InfoText.setStyle(sf::Text::Regular);
    InfoText.setFillColor(sf::Color::White);
    InfoText.setCharacterSize(20);
    info = "Score: " + std::to_string(score);
    InfoText.setString(info);
    if (spaceshipvector.size())
      info = "Lifes: " + std::to_string(spaceshipvector[0].gethealth());
    else
      info = "Lifes: " + std::to_string(0);
    InfoText.setPosition(Window.getSize().x - 200.0, 25.0);
    Window.draw(InfoText);
    InfoText.setPosition(50, 25);
    InfoText.setString(info);
    Window.draw(InfoText);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && spaceshipvector.size()) {
         spaceshipvector[0].setdirection(sf::Vector2i(-1,0));
         spaceshipvector[0].move();
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && spaceshipvector.size()) {
          spaceshipvector[0].setdirection(sf::Vector2i(1, 0));
          spaceshipvector[0].move();
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !laservector.size() && spaceshipvector.size()){
          laservector.add(spaceshipvector[0].shoot());
      }
      for (int i = 0; i < projectilevector.size(); i++) {//Проверка
        projectilevector[i].move();
        if (!(projectilevector[0].getcordinates().y < Window.getSize().y - projectilevector[0].getsize().y))
            projectilevector.erase(i--);
      }
      if (laservector.size()){//Проверка коллизии для снаряда игрока
        laservector[0].move();
        if (!(laservector[0].getcordinates().y > 0))
          laservector.pop();
        }
      gameon = ctrl.movecontrol();
      score += ctrl.collision(laservector);
      if (ctrl.isEmpty()){
        ctrl.initialize();
        spaceshipvector[0].sethealth(spaceshipvector[0].gethealth()+1);
      }
      ctrl.render();
      ctrl.fire(&projectilevector);
      collisioncheck(&spaceshipvector, &projectilevector);
      gameon = gameon && spaceshipvector.size();
      for (int i = 0; i < laservector.size(); i++)
        Window.draw(laservector[i].getsprite());
      for (int i = 0; i < projectilevector.size(); i++)
        Window.draw(projectilevector[i].getsprite());
    if (spaceshipvector.size())
      Window.draw(spaceshipvector[0].getsprite());
    end = clock();
    if ((int)((((end - start) + 0.0) / CLOCKS_PER_SEC) * 1000)<=20)
     Sleep(20 - (int)((((end - start) + 0.0) / CLOCKS_PER_SEC) * 1000));
  }
    else {
      info = "GAME OVER";
      Window.clear(sf::Color::Black);
      sf::String retry = "Press Esc to play again",scoreinfo = "you scored "+std::to_string(score) + " points";
      InfoText.setStyle(sf::Text::Regular);
      InfoText.setFillColor(sf::Color::White);
      InfoText.setCharacterSize(20);
      InfoText.setPosition(425,350);
      InfoText.setString(scoreinfo);
      Window.draw(InfoText);
      InfoText.setPosition(425, 400);
      InfoText.setString(retry);
      Window.draw(InfoText);
      InfoText.setFillColor(sf::Color::Green);
      InfoText.setCharacterSize(60);
      InfoText.setPosition(360,250);
      InfoText.setString(info);
      Window.draw(InfoText);
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ) {
        gameon = true;
        spaceshipvector.clear();
        spaceshipvector.add(createship());
        ctrl.initialize();
        laservector.clear();
        projectilevector.clear();
        score = 0;
      }
      }
    Window.display();
}
}