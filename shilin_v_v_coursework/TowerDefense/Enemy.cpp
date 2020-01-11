#include "Enemy.h"

Enemy::Enemy(sf::Vector2f _position, sf::Vector2f _size, std::shared_ptr<sf::Texture> _texture,
		int _gold, int _health, int _damage, float _pixelSpeed, EnemyType _type, int targetPath)
  :	texture(_texture)
  , goldValue(_gold)
  , health(_health)
  , damage(_damage)
  , pixelSpeed(_pixelSpeed)
  , type(_type)
  , targetPathPoint(targetPath) {
  setFrames(_texture, type);
  currentFrame = 0;
  shape = frames[currentFrame];
	shape.setPosition(_position);

	shape.setFillColor(sf::Color(255, 255, 255, 255));
} 

void Enemy::setFrames(std::shared_ptr<sf::Texture> texture, EnemyType type) {
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
  for (int i(0); i < 5; ++i) {
    frames.push_back(frameShape);
    frames[i].setTexture(texture.get());
    frames[i].setTextureRect(sf::IntRect(i * size_x, 0, size_x, size_y));
  }
}

void Enemy::nextFrame() {
  currentFrame = (currentFrame + 1) % 5;
  shape = frames[currentFrame];
  if (!dir) {
    shape.setOrigin(shape.getLocalBounds().width, 0);
    shape.setScale(-1, 1);
  }
}

int Enemy::getGoldValue() {
	return this->goldValue;
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

void Enemy::render(std::shared_ptr<sf::RenderWindow> window) {
	window->draw(shape);
}
