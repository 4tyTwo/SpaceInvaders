#pragma once
#include "Enemy.h"
class Controller
{
public:
  Controller();
  Controller(int rows,int collumns);
  bool isemptybelow(int row,int collumn); //Проверка пусто ли под кораблем (чтобы стрелять)
  void render(); //Отрисовать все корабли в матрице
  void moveLeft(); //Шаг влево
  bool moveDown(); //Шаг вниз
  void moveRight(); //Шаг вправо
  bool moveControl();//Сама решает когда и куда идти
  int rightestcollumn();//Самый правый столбец с живыми кораблями
  int leftestcollumn();//Аналогично предыдущему
  int bottomrow();//Самый нижний ряд с живыми кораблями
  void initialize();//Создает самую обычную матрицу, с заранее придуманным объектом
  void fire(MyVector<Projectile>* proj);
  sf::RenderWindow* window; // Доступ к окну
  int collision(MyVector<Projectile>& laser);
  bool isEmpty();
  ~Controller();
private:
  std::vector<std::vector<Enemy>> matrix;
  int globalspeed;
  clock_t laststep,lag;//laststep - время последнего движения. lag - задержка между движением
  sf::Vector2i direction;
};

