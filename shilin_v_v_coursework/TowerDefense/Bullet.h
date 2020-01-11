#ifndef TD_BULLET_H
#define TD_BULLET_H

#include "Enemy.h"
#include <SFML/Graphics.hpp>

//! \brief Снаряд.
class Bullet{
public:

  //! \brief Умолчательный конструктор.
  Bullet() = default;

  //! \brief Конструирование снаряда по параметрам.
  //! \param ind - индекс снаряда
  //! \param damage - наносимый снарядом урон
  //! \param towerPostition - координаты башни, выпускающей снаряд
  //! \param enemyToFireAt - указатель на атакуемого NPC
  //! \param tType - тип башни, выпускающей снаряд
	Bullet(int ind, int damage, sf::Vector2f towerPosition,
	  std::weak_ptr<Enemy> enemyToFireAt, TowerType tType);

  //! \brief Деструктор.
	~Bullet() = default;
  
  //! \brief Отображение снаряда.
	void drawBullet(std::shared_ptr<sf::RenderWindow> _window);
  
  //! \brief Перемещение снаряда по пути к атакуемому NPC.
	void moveObjectTowardsEnemy(sf::Vector2f enemyPos);

  //! \brief Расстояние до атакуемого NPC.
	float DistanceFromEnemy(sf::Vector2f enemy); 

  //! \brief Возвращает true, если снаряд достаточно близок к атакуемому NPC.
	bool bulletEnemyCollision(sf::Vector2f enemy);

  //! \brief Обеспечение плавного перемещения снаряда.
  //! \return сдвиг на следующее положение снаряда.
	sf::Vector2f normalize(sf::Vector2f v);

  //! \brief Позиция снаряда.
	sf::Vector2f getBulletPosition();

  //! \brief Скорость снаряда.
	float getSpeed();

  //! \brief Атакуемый NPC.
	std::weak_ptr<Enemy> getEnemyTarget();

  //! \brief Наносимый снарядом урон.
	int getDamage();

  //! \brief Координаты центра снаряда.
	sf::Vector2f getBulletCenter();

  //! \brief Тип атакуемого NPC.
  TowerType getType();

private:
  TowerType type{ TowerType::empty };
  int index{ 0 };
  int damage{ 0 };
  sf::Texture bulletTexture;
  sf::RectangleShape bulletShape;
  sf::Vector2f bulletPosition;
  sf::Vector2f bulletCenter;
  float speed{ 0.0f };
  std::weak_ptr<Enemy> enemyTarget;
};

#endif
