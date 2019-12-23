#ifndef TD_ENEMY_H
#define TD_ENEMY_H
#include <SFML/Graphics.hpp>
#include "GameState.h"

class Enemy {
public:
	// The actual texture definition occurs within the enemyController
	Enemy() = default;
	Enemy(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture,
			int _tam, int _health, int _damage, float _pixelSpeed, EnemyType type);
	virtual ~Enemy();
  void setFrames(sf::Texture* texture, EnemyType type);
  void nextFrame();

	// Game logic functions
	void update();
	void render(sf::RenderWindow* window);

	EnemyType getEnemyType() const;

	// Accessors
	int getTamValue();
	int getHealth();
	int getDamage();
	int getPixelSpeed();
	int getPathIndex();
	sf::Vector2f getPosition();
	sf::Vector2f getCenterPosition();
	void setPosition(sf::Vector2f position);
	// The enemy controller will use these to change animations
	sf::IntRect getTextureRect();
	void setTextureRect(sf::IntRect textureRect);
	// This returns the resulting health of the enemy
	int reduceHealth(int damage);
	// Bumps the point by one
	void increasePathIndex();
  bool dir{ true };

private:
  int currentFrame{ 0 };
  sf::RectangleShape shape;
  // The enemy controller will determine which specific enemy
  // spritesheet to use. The enemy object is only responsible
  // for changing specific directions, etc.
  sf::Texture* texture;
  sf::IntRect textureRect;

  // Internal game attributes
  int tamValue;
  // Decreases when attacked by a tower
  int health;
  // This determines how much health is lost when it crosses the finish
  int damage;
  // Pixels moved after each update()
  float pixelSpeed;
  EnemyType type;
  // The index of the path that it is moving towards
  // Reaching the final index means clearing the map
  int targetPathPoint;

  std::vector<sf::RectangleShape> frames;

  // To handle movement, I can have a reference to the array
  // of points, and then a current pathIndex. Once the point is reached,
  // I move to the next index. To check end of screen, have the controller
  // read the pathIndex, and delete it once the final index is reached.
};

#endif
