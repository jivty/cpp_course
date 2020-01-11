#include "Bullet.h"

Bullet::Bullet(int ind, int _damage,
		sf::Vector2f towerPosition, std::weak_ptr<Enemy> enemyToFireAt, TowerType tType) 
  : index(ind)
  , damage(_damage)
  , bulletPosition(towerPosition)
  , enemyTarget(enemyToFireAt)
  , type(tType) {
	speed = 10.0f;
	if (auto enemy = enemyToFireAt.lock()) {
		if (enemy->getPixelSpeed() > speed - 3.5) {
			speed = enemy->getPixelSpeed() + 3.5;
		}
	}
	bulletShape = sf::RectangleShape(sf::Vector2f(15.0f, 15.0f));
 
	bulletShape.setPosition(towerPosition + sf::Vector2f(12.5f, 12.5f));
	if (!bulletTexture.loadFromFile("images/bullets/bullet.png")) {
		std::cerr << "Error finding image\n";
	} else {
		bulletShape.setTexture(&bulletTexture);
	}
	bulletCenter = sf::Vector2f(towerPosition.x + 15.0f / 2.0f,
			towerPosition.y + 15.0f / 2.0f);
}

void Bullet::drawBullet(std::shared_ptr<sf::RenderWindow> _window) {
	_window->draw(bulletShape);
}

sf::Vector2f Bullet::normalize(sf::Vector2f v) {
	float len = float(sqrt((v.x * v.x) + (v.y * v.y)));
	if (len != 0) {
		v.x = v.x / len;
		v.y = v.y / len;
	}
	return v;
}

void Bullet::moveObjectTowardsEnemy(sf::Vector2f enemyPos) {
	sf::Vector2f movePos = normalize(enemyPos - bulletPosition);
	bulletShape.move(movePos * getSpeed());
	bulletPosition = bulletPosition + movePos * getSpeed();
	bulletCenter = bulletCenter + movePos * getSpeed();
}

float Bullet::DistanceFromEnemy(sf::Vector2f enemy) {
	float x = abs(
			(enemy.x - bulletPosition.x)
					* (enemy.x - bulletPosition.x));
	float y = abs(
			(enemy.y - bulletPosition.y)
					* (enemy.y - bulletPosition.y));
	return (int) (powf(x + y, 0.5));
}

bool Bullet::bulletEnemyCollision(sf::Vector2f enemy) {
	return DistanceFromEnemy(enemy) < 20;
} 

std::weak_ptr<Enemy> Bullet::getEnemyTarget() {
	return enemyTarget;
}

sf::Vector2f Bullet::getBulletPosition() {
	return bulletPosition;
}

float Bullet::getSpeed() {
	return speed;
}

int Bullet::getDamage() {
	return damage;
}

sf::Vector2f Bullet::getBulletCenter() {
	return bulletCenter;
}

TowerType Bullet::getType() {
  return type;
}
