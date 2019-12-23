#include "Enemy.h"

Enemy::Enemy(sf::Vector2f _position, sf::Vector2f _size, sf::Texture* _texture,
		int _tam, int _health, int _damage, float _pixelSpeed, EnemyType _type) :
		texture(_texture), tamValue(_tam), health(
				_health), damage(_damage), pixelSpeed(_pixelSpeed), type(_type) {
	// Map shape properties
  setFrames(_texture, type);
  currentFrame = 0;
  shape = frames[currentFrame];
	//shape = sf::RectangleShape(sf::Vector2f(_size.x, _size.y));
	shape.setPosition(_position);
	//shape.setSize(_size);
	//shape.setTexture(texture);
  //shape.setScale(float(Clickable::gridSize) / float(_size.x),
    //float(Clickable::gridSize) / float(_size.y));

	//shape.setType(type);

	shape.setFillColor(sf::Color(255, 255, 255, 255)); // Half transparency
	targetPathPoint = 0;
}

// EnemyController is responsible for creating and deleting objects
Enemy::~Enemy() {
}

void Enemy::setFrames(sf::Texture* texture, EnemyType type) {
  int size_x(0);
  int size_y(0);
  switch (type) {
  case EnemyType::skeleton:
    size_x = 40;
    size_y = 49;
    break;
  case EnemyType::rhino:
    size_x = 40;
    size_y = 49;
    break;
  case EnemyType::lancer:
    size_x = 60;
    size_y = 74;
    break;
  case EnemyType::demon:
    size_x = 68;
    size_y = 60;
    break;
  }
  sf::RectangleShape frameShape(sf::Vector2f(Clickable::gridSize, Clickable::gridSize));
  frames.push_back(frameShape);
  frames[0].setTexture(texture);
  frames[0].setTextureRect(sf::IntRect(0, 0, size_x, size_y));
  frames.push_back(frameShape);
  frames[1].setTexture(texture);
  frames[1].setTextureRect(sf::IntRect(size_x, 0, size_x, size_y));
  frames.push_back(frameShape);
  frames[2].setTexture(texture);
  frames[2].setTextureRect(sf::IntRect(size_x * 2, 0, size_x, size_y));
  frames.push_back(frameShape);
  frames[3].setTexture(texture);
  frames[3].setTextureRect(sf::IntRect(size_x * 3, 0, size_x, size_y));
  frames.push_back(frameShape);
  frames[4].setTexture(texture);
  frames[4].setTextureRect(sf::IntRect(size_x * 4, 0, size_x, size_y));
}

void Enemy::nextFrame() {
  currentFrame = (currentFrame + 1) % 5;
  shape = frames[currentFrame];
  if (!dir) {
    shape.setOrigin(shape.getLocalBounds().width, 0);
    shape.setScale(-1, 1);
  }
}

int Enemy::getTamValue() {
	return this->tamValue;
}
int Enemy::getHealth() {
	return this->health;
}
int Enemy::getDamage() {
	return this->damage;
}

sf::Vector2f Enemy::getPosition() {
	return this->shape.getPosition();
}

sf::Vector2f Enemy::getCenterPosition() {
	sf::Vector2f center = this->shape.getPosition();
	center.x += this->shape.getSize().x / 3;
	center.y += this->shape.getSize().y / 3;
	return center;
}

/*void Enemy::setEnemyType(EnemyType type) {
	return this->type;
	//this->shape.setType(type);
}*/

EnemyType Enemy::getEnemyType() const {
	return this->type;
}

void Enemy::setPosition(sf::Vector2f position) {
	this->shape.setPosition(position);
}

sf::IntRect Enemy::getTextureRect() {
	return this->textureRect;
}

void Enemy::setTextureRect(sf::IntRect textureRect) {
	this->textureRect = textureRect;
    this->shape.setTextureRect(textureRect);
}

int Enemy::reduceHealth(int damage) {
	this->health -= damage;
	return this->health;
}

int Enemy::getPixelSpeed() {
	return this->pixelSpeed;
}

int Enemy::getPathIndex() {
	return this->targetPathPoint;
}

void Enemy::increasePathIndex() {
	this->targetPathPoint++;
}

//	This is the movement logic that updates the position
void Enemy::update() {

}

void Enemy::render(sf::RenderWindow* window) {
	window->draw(shape);
}

