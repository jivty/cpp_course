#include "Bullet.h"

//creates a Bullet object
Bullet::Bullet(int ind, int _damage,
		sf::Vector2f towerPosition, weak_ptr<Enemy> enemyToFireAt, TowerType tType) 
  :  index(ind)
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
	//bulletShape.setSize(sf::Vector2f(30.0f, 30.0f)); //size of bullet
 
	bulletShape.setPosition(towerPosition + sf::Vector2f(12.5f, 12.5f));
	if (!bulletTexture.loadFromFile(bulletImage)) {
		std::cerr << "Error finding image\n";
	} else {
		//bulletTexture.loadFromFile(bulletImage);
		bulletShape.setTexture(&bulletTexture);
	}
	bulletCenter = sf::Vector2f(towerPosition.x + 15.0f / 2.0f,
			towerPosition.y + 15.0f / 2.0f);
}

void Bullet::drawBullet(sf::RenderWindow* _window) {
	_window->draw(bulletShape);
}

//gets a vector of length 1, to be multipled by a speed
sf::Vector2f Bullet::normalize(sf::Vector2f v) {
	float len = float(sqrt((v.x * v.x) + (v.y * v.y)));
	if (len != 0) {
		v.x = v.x / len;
		v.y = v.y / len;
	}
	return v;
}

//draws the bullet to the window
void Bullet::moveObjectTowardsEnemy(sf::Vector2f enemyPos) {
	sf::Vector2f movePos = normalize(enemyPos - bulletPosition);
	bulletShape.move(movePos * getSpeed()); //using the x,y positions, moves at a percentage towards the enemy object
	bulletPosition = bulletPosition + movePos * getSpeed();
	bulletCenter = bulletCenter + movePos * getSpeed();
}

// returns distance between two points
float Bullet::DistanceFromEnemy(sf::Vector2f enemy) {
	//use abs to prevent a negative distance
	float x = abs(
			(enemy.x - bulletPosition.x)
					* (enemy.x - bulletPosition.x));
	float y = abs(
			(enemy.y - bulletPosition.y)
					* (enemy.y - bulletPosition.y));
	return (int) (powf(x + y, 0.5)); //square root ( x^2+y^2 )
}
bool Bullet::bulletEnemyCollision(sf::Vector2f enemy) // simple collision detection between two circles
		{
	return DistanceFromEnemy(enemy) < 20;
	//return DistanceFromEnemy(enemy) < bulletShape.getSize().x || DistanceFromEnemy(enemy) < bulletShape.getSize().y;// if dist < tower range we have a collision
} //will always do for < 10

//Accessors:
weak_ptr<Enemy> Bullet::getEnemyTarget() {
	return enemyTarget;
}
string Bullet::getBulletImage() {
	return bulletImage;
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
