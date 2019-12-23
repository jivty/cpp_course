#ifndef TD_BULLET_H
#define TD_BULLET_H
#include "SFML/Graphics.hpp"
#include "Tower.h"
#include "Enemy.h"

class Bullet{
public:
	Bullet(int ind, int damage, sf::Vector2f towerPosition,
	  std::weak_ptr<Enemy> enemyToFireAt, TowerType tType);
	~Bullet() = default;
	void drawBullet(sf::RenderWindow* _window);
	//using enemy position, heatseeks towards the enemy until collision occurs
	void moveObjectTowardsEnemy(sf::Vector2f enemyPos);
	float DistanceFromEnemy(sf::Vector2f enemy); // returns distance between two points
	bool bulletEnemyCollision(sf::Vector2f enemy); // collision detection between two objects, using the distance function
	void dealDamage(); //deals the damage associated with the bullet
	sf::Vector2f normalize(sf::Vector2f v);

	//Accessors:
	std::string getBulletImage();
	sf::Vector2f getBulletPosition();
	float getSpeed();
	std::weak_ptr<Enemy> getEnemyTarget();
	int getDamage();
	sf::Vector2f getBulletCenter();
  TowerType getType();

private:
  TowerType type;
	int index;
	int damage;
	sf::Texture bulletTexture;
	sf::RectangleShape bulletShape;
	sf::Vector2f bulletPosition;
	sf::Vector2f bulletCenter;
	float speed;
  std::string bulletImage{ "images/bullets/bulletU.png" };
	std::weak_ptr<Enemy> enemyTarget;
};

#endif
