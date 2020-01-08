#include "MenuButton.h"
#include "Clickable.h"
#include <SFML/Graphics.hpp>
#include <iostream>

MenuButton::MenuButton(sf::Vector2f _position, int _sizex, int _sizey,
  std::shared_ptr<sf::Texture> _texture) 
  :	Clickable(_position, sf::Vector2f(_sizex, _sizey)) {
	graphic = sf::RectangleShape(sf::Vector2f(_sizex, _sizey));
	setPosition(_position);
	graphic.setTexture(_texture.get());
	graphic.setFillColor(sf::Color(255, 255, 255, 180));
	update();
}

void MenuButton::setTextureRect(const sf::IntRect& rect) {
	graphic.setTextureRect(rect);
}

void MenuButton::setTransparency(const int transparency) {
	graphic.setFillColor(sf::Color(255, 255, 255, transparency));
}

void MenuButton::update() {
	graphic.setPosition(getPosition());
}

void MenuButton::render(sf::RenderWindow& _window) {
	_window.draw(graphic);
}

void MenuButton::onClick() {
}

void MenuButton::onMouseEnter() {
	graphic.setFillColor(sf::Color(255, 255, 255, 255));
  turnColor(onoff);
}

void MenuButton::onMousePressed() {
}

void MenuButton::onMouseLeave() {
	graphic.setOutlineThickness(0);
	graphic.setFillColor(sf::Color(255, 255, 255, 180));
}

void MenuButton::turnColor(const bool onoff) {
  this->onoff = onoff;
  if (onoff) {
    graphic.setFillColor(sf::Color(230, 255, 230));
  } else {
    graphic.setFillColor(sf::Color(255, 230, 230));
  }
}

VolumeButton::VolumeButton(sf::Vector2f _position, int _sizex, int _sizey,
  std::shared_ptr<sf::Texture> _texture,
  std::shared_ptr<sf::Music> music)
  : MenuButton(_position, _sizex, _sizey, _texture)
  , music(music) {
  isPlaying = music.get()->getStatus() == sf::SoundSource::Status::Playing ? true : false;
  turnColor(isPlaying);
  setTransparency(180);
}

void VolumeButton::onClick() {
  isPlaying = music.get()->getStatus() == sf::SoundSource::Status::Playing ? false : true;
	if (!isPlaying) {
    music->pause();
	} else {
    music->play();
	}
  this->turnColor(isPlaying);
}

void VolumeButton::onMouseEnter() {
  isPlaying = music.get()->getStatus() == sf::SoundSource::Status::Playing ? true : false;
  turnColor(isPlaying);
}

InfoButton::InfoButton(sf::Vector2f _position, int _sizex, int _sizey,
		std::shared_ptr<sf::Texture> _texture, 
  std::shared_ptr<GameState> gameState) :
		MenuButton(_position, _sizex, _sizey, _texture), gameState(gameState) {
}

void InfoButton::onClick() {
	gameState->toggleHelpScreen();
}

PauseButton::PauseButton(sf::Vector2f _position, int _sizex, int _sizey,
		std::shared_ptr<sf::Texture> _texture, 
  std::shared_ptr<Timer> timer) :
		MenuButton(_position, _sizex, _sizey, _texture), timer(timer) {
}

void PauseButton::onClick() {
	if (timer->isRunning()) {
		setTextureRect(sf::IntRect(896, 384, 128, 128));
		timer->stop();
    turnColor(false);
	} else {
		setTextureRect(sf::IntRect(897, 256, 128, 128));
		timer->start();
    turnColor(true);
	}
}

UpgradeButton::UpgradeButton(sf::Vector2f _position, int _sizex, int _sizey,
  std::shared_ptr<sf::Texture> _texture,
  std::shared_ptr<GameState> _gameState) :
  MenuButton(_position, _sizex, _sizey, _texture), gameState(_gameState) {

  selected = false;
}

bool UpgradeButton::getCanUpgrade() {
	return this->canUpgrade;
}

void UpgradeButton::setCanUpgrade(bool status) {
	this->canUpgrade = status;
}

void UpgradeButton::onClick() {
	if (gameState->getBoardTower() != nullptr && canUpgrade) {
		gameState->updateGoldBy(-(gameState->getBoardTower()->getUpgradeCost()));
		gameState->getBoardTower()->upgrade();
	}
}

void UpgradeButton::onMouseEnter() {
}

void UpgradeButton::onMouseLeave() {
}
