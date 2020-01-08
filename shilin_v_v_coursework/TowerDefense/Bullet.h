#ifndef TD_BULLET_H
#define TD_BULLET_H

#include "Tower.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>

class Bullet{
public:
  Bullet() = default;
	Bullet(int ind, int damage, sf::Vector2f towerPosition,
	  std::weak_ptr<Enemy> enemyToFireAt, TowerType tType);
	~Bullet() = default;
  Bullet(const Bullet& bullet) = default;
	void drawBullet(std::shared_ptr<sf::RenderWindow> _window);
	void moveObjectTowardsEnemy(sf::Vector2f enemyPos);
	float DistanceFromEnemy(sf::Vector2f enemy); 
	bool bulletEnemyCollision(sf::Vector2f enemy);
	sf::Vector2f normalize(sf::Vector2f v);

	sf::Vector2f getBulletPosition();
	float getSpeed();
	std::weak_ptr<Enemy> getEnemyTarget();
	int getDamage();
	sf::Vector2f getBulletCenter();
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
