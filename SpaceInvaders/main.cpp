#include<iostream>
#include "Spaceship.h"
#include "Projectile.h"
#include <Windows.h>
#include <time.h>
#include "MyVectror.h"
#include "Controller.h"
#include <Windows.h>


void collisionCheck(MyVector<Spaceship>* spaceship_vector,MyVector<Projectile>* laser_vector) {
  for (auto i = 0; i < laser_vector->size() && spaceship_vector->size(); i++) {
    if (laser_vector->get(i).checkCollision(&spaceship_vector->get(0))) {
      spaceship_vector->get(0).sufferdamage(laser_vector->get(i).getdamage());
      if (spaceship_vector->get(0).getHealth() <= 0)
        spaceship_vector->pop();
      laser_vector->erase(i);
      break;
    }
  }
}

Spaceship createship() {
  Spaceship tmp;
  tmp.setTexture("C:\\Source\\Gunship.png");
  tmp.setSize(98, 62);
  tmp.setCordinates(551, 690 - 72);
  tmp.setSpeed(10);
  tmp.setHealth(3);
  tmp.setLaserDamage(1);
  tmp.setLaserDirection(sf::Vector2i(0, -1));
  return tmp;
}


int WINAPI WinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance,   LPSTR lpCmdLine,  int nCmdShow){
  srand(time(NULL));
  sf::Font font;
  font.loadFromFile("C:\\Source\\Pixeled.ttf");
  clock_t start, end,lastshot = 0;
  sf::RenderWindow Window(sf::VideoMode(1200,690),"Space Invaders", sf::Style::Close);
  Window.setPosition(sf::Vector2i(0,0));                        
  sf::String info;
  bool gameon = true;
  int score = 0;
  MyVector<Projectile> projectile_vector, laser_vector;
  MyVector<Spaceship> spaceship_vector;
  Controller ctrl;
  spaceship_vector.add(createship());
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
    if (spaceship_vector.size())
      info = "Lives: " + std::to_string(spaceship_vector[0].getHealth());
    else
      info = "Lives: " + std::to_string(0);
    InfoText.setPosition(Window.getSize().x - 200.0, 25.0);
    Window.draw(InfoText);
    InfoText.setPosition(50, 25);
    InfoText.setString(info);
    Window.draw(InfoText);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && spaceship_vector.size()) {
         spaceship_vector[0].setdirection(sf::Vector2i(-1,0));
         spaceship_vector[0].move();
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && spaceship_vector.size()) {
          spaceship_vector[0].setdirection(sf::Vector2i(1, 0));
          spaceship_vector[0].move();
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !laser_vector.size() && spaceship_vector.size()){
          laser_vector.add(spaceship_vector[0].shoot());
      }
      for (auto i = 0; i < projectile_vector.size(); i++) {//Проверка
        projectile_vector[i].move();
        if (!(projectile_vector[0].getCordinates().y < Window.getSize().y - projectile_vector[0].getSize().y))
            projectile_vector.erase(i--);
      }
      if (laser_vector.size()){//Проверка коллизии для снаряда игрока
        laser_vector[0].move();
        if (!(laser_vector[0].getCordinates().y > 0))
          laser_vector.pop();
        }
      gameon = ctrl.moveControl();
      score += ctrl.collision(laser_vector);
      if (ctrl.isEmpty()){
        ctrl.initialize();
        spaceship_vector[0].setHealth(spaceship_vector[0].getHealth()+1);
      }
      ctrl.render();
      ctrl.fire(&projectile_vector);
      collisionCheck(&spaceship_vector, &projectile_vector);
      gameon = gameon && spaceship_vector.size();
      for (auto i = 0; i < laser_vector.size(); i++)
        Window.draw(laser_vector[i].getSprite());
      for (auto i = 0; i < projectile_vector.size(); i++)
        Window.draw(projectile_vector[i].getSprite());
    if (spaceship_vector.size())
      Window.draw(spaceship_vector[0].getSprite());
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
        spaceship_vector.clear();
        spaceship_vector.add(createship());
        ctrl.initialize();
        laser_vector.clear();
        projectile_vector.clear();
        score = 0;
      }
      }
    Window.display();
}
}