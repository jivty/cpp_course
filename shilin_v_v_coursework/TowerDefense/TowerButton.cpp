#include "Tower.h"
#include "TowerButton.h"
#include "Clickable.h"
#include <SFML/Graphics.hpp>
#include <iostream>

TowerButton::TowerButton(sf::Vector2f _position, int _radius,
		std::shared_ptr<sf::Texture> _texture, std::string inText, std::string inText2, 
  TowerType _type, std::shared_ptr<GameState> _gameState, std::shared_ptr<sf::Texture> _menutexture)
  :	towerType(_type)
  , gameState(_gameState) {
	if (!font.loadFromFile("font/georgia.ttf")) {
	}

	graphic = sf::CircleShape(_radius);
	setPosition(_position);
	setSize(sf::Vector2f(_radius * 2, _radius * 2));
	graphic.setTexture(_texture.get());
	graphic.setFillColor(sf::Color(255, 255, 255, 180));
	graphic.setOutlineColor(sf::Color(95, 72, 43)); 

	displayText = false;
	towerButtonText = sf::Text();
	towerButtonText.setString(inText);
	towerButtonText.setCharacterSize(30);
	towerButtonText2 = sf::Text();
	towerButtonText2.setString(inText2);
	towerButtonText2.setCharacterSize(15);
  towerTextBack = sf::RectangleShape(sf::Vector2f(3.0f * _radius, 1.5f *_radius));
	towerTextBack.setTexture(_menutexture.get());
	towerTextBack.setTextureRect(sf::IntRect(1056, 165, 320, 128));
	int baseY = 20, baseX = 1036;
	if (_type == TowerType::physic) {
    baseY += 2 * _radius;
	} else if (_type == TowerType::magic) {
		baseY += 4*_radius;
	} else if (_type == TowerType::ultimate) {
		baseY += 6*_radius;
	}
  towerButtonText.setPosition(baseX + 0.6f * _radius, baseY + 0.4f * _radius);
	towerButtonText2.setPosition(baseX + 1.4f * _radius, baseY + 0.5f * _radius);
	towerTextBack.setPosition(baseX, baseY);

	update();
}

TowerType TowerButton::getTowerType() {
	return this->towerType;
}

void TowerButton::setTransparency(const int transparency) {
	graphic.setFillColor(sf::Color(255, 255, 255, transparency));
}

void TowerButton::setTextureRect(const sf::IntRect& rect) {
	graphic.setTextureRect(rect);
}

void TowerButton::update() {
	graphic.setPosition(getPosition());
}
void TowerButton::render(sf::RenderWindow& _window) {
	_window.draw(graphic);
}
void TowerButton::renderText(sf::RenderWindow& _window){
	towerButtonText.setFont(font);
	towerButtonText2.setFont(font);
	if (displayText) {
			_window.draw(towerTextBack);
			_window.draw(towerButtonText);
			_window.draw(towerButtonText2);
		}
}

void TowerButton::onClick() {
	graphic.setOutlineThickness(0);
	gameState->setPurchaseTower(this->towerType);
	gameState->setBoardTower(nullptr);
}

void TowerButton::onMouseEnter() {
	graphic.setFillColor(sf::Color(255, 255, 255, 255));
	displayText = true;
}

void TowerButton::onMousePressed() {
	graphic.setOutlineThickness(5);
}

void TowerButton::onMouseLeave() {
	graphic.setOutlineThickness(0);
	graphic.setFillColor(sf::Color(255, 255, 255, 180));
	displayText = false;
}
