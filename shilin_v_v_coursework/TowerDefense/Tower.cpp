#include "Tower.h"
#include <SFML/Graphics.hpp>

Tower::Tower(const sf::Vector2f position, std::shared_ptr<sf::Texture> _texture, TowerType _type,
  int damage, float range, float cooldown, int upgCost = 20)
  : Clickable(position, sf::Vector2f(Clickable::gridSize, gridSize))
  , towerPos(position)
  , texture(_texture)
  , type(_type)
  , towerDamage(damage)
  , towerRange(range)
  , baseCooldown(cooldown)
  , upgradeCost(upgCost) {
  currentSprite = sf::IntRect(5, -2, 75, 86);
  towerSprite = sf::Sprite(*texture, currentSprite);
  towerSprite.setPosition(towerPos.x, towerPos.y);
  towerSprite.setScale(float(Clickable::gridSize) / float(currentSprite.width),
    float(Clickable::gridSize) / float(currentSprite.height));
  currentCooldown = 0;
  wasClicked = false;
}

TowerType Tower::getTowerType() const {
	return this->type;
}

void Tower::decreaseCooldown() {
	this->currentCooldown--;
}
void Tower::resetCooldown() {
	this->currentCooldown = this->baseCooldown;
}

void Tower::update() {
}

void Tower::render(sf::RenderWindow& _window) {
	_window.draw(this->towerSprite);
}

void Tower::onClick() {
	this->wasClicked = true;
}

sf::Vector2f Tower::getPosition() const {
	return towerPos;
}

sf::Vector2f Tower::getCenterPosition() const {
	sf::Vector2f center = this->towerSprite.getPosition();
  center.x += Clickable::gridSize / 2;
	center.y += Clickable::gridSize / 2;
	return center;
}

float Tower::getDamage() const {
	return this->towerDamage;
}
float Tower::getRange() const {
	return this->towerRange;
}

int Tower::getCooldown() {
	return this->currentCooldown;
}

int Tower::getUpgradeCost() {
	return this->upgradeCost;
}

sf::Sprite Tower::getTowerSprite() const {
	return towerSprite;
}

float Tower::enemyDistance(sf::Vector2f enemy)
		{
	float x = (towerPos.x - enemy.x) * (towerPos.x - enemy.x);
	float y = (towerPos.y - enemy.y) * (towerPos.y - enemy.y);
	float xPlusY = x + y;
	return (float) (powf(xPlusY, 0.5)); 
}

bool Tower::enemyCollides(sf::Vector2f enemy)
{
	float dist = enemyDistance(enemy);
	return dist < towerRange;
}

void Tower::upgrade() {
	this->towerDamage *= 1.2;
	this->towerRange *= 1.2;
	this->baseCooldown *= 1.1;
	this->upgradeCost *= 1.5;
  this->currentCooldown += 1;
}

bool Tower::saveData(const std::string path) {
  bool success(false);
  std::ofstream fout;
  fout.open(path, std::ofstream::binary | std::ofstream::out | std::ofstream::app);
  if (fout.is_open()
    && fout.write((char*)& towerPos, sizeof(towerPos))
    && fout.write((char*)& type, sizeof(type))
    && fout.write((char*)& towerDamage, sizeof(towerDamage))
    && fout.write((char*)& towerRange, sizeof(towerRange))
    && fout.write((char*)& baseCooldown, sizeof(baseCooldown))
    && fout.write((char*)& upgradeCost, sizeof(upgradeCost))) {
    success = true;
  }
  fout.close();
  return success;
}
