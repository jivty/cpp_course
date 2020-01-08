#ifndef TD_ENEMY_H
#define TD_ENEMY_H

#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <fstream>

class Enemy {
public:
  Enemy() = default;
	Enemy(sf::Vector2f position, sf::Vector2f size, std::shared_ptr<sf::Texture> texture,
			int _gold, int _health, int _damage, float _pixelSpeed, EnemyType type, int targetPath);
  ~Enemy() = default;
  void setFrames(std::shared_ptr<sf::Texture> texture, EnemyType type);
  void nextFrame();
	void render(std::shared_ptr<sf::RenderWindow> window);

	EnemyType getEnemyType() const;

	int getGoldValue();
	int getHealth();
	int getDamage();
	int getPixelSpeed();
	int getPathIndex();
	sf::Vector2f getPosition();
	sf::Vector2f getCenterPosition();
	void setPosition(sf::Vector2f position);
	sf::IntRect getTextureRect();
	void setTextureRect(sf::IntRect textureRect);
	int reduceHealth(int damage);
	void increasePathIndex();
  bool dir{ true };

private:
  int currentFrame{ 0 };
  sf::RectangleShape shape{ sf::RectangleShape(sf::Vector2f(0, 0)) };
  std::shared_ptr<sf::Texture> texture;
  sf::IntRect textureRect{ sf::IntRect(0,0,0,0) };

  int goldValue{ 0 };
  int health{ 0 };
  int damage{ 0 };
  float pixelSpeed{ 0 };
  EnemyType type{ EnemyType::empty };
  int targetPathPoint{ 0 };

  std::vector<sf::RectangleShape> frames;
};

#endif
