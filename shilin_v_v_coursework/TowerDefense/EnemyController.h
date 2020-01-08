#ifndef TD_ENEMY_CONTROLLER_H
#define TD_ENEMY_CONTROLLER_H

#include "Enemy.h"
#include "GameState.h"
#include "GameController.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class EnemyController {
public:
	EnemyController(std::shared_ptr<sf::RenderWindow> window, 
    std::shared_ptr<GameState> gameState,
			const std::vector<sf::Vector2f> pathToFollow);
  ~EnemyController() = default;

	std::shared_ptr<Enemy> spawnEnemy(sf::Vector2f position, EnemyType type, 
    int health, int targetPath);
	void removeEnemy(std::shared_ptr<Enemy> targetEnemy);
	void dealDamage(std::shared_ptr<Enemy> enemy, int damage);

	void enemyWave(EnemyType type);
	void waveOne();
	void waveTwo();
  void waveThree();
  void waveFour();
  void waveEND();

	void update();
	void render();
  bool saveData(const std::string path);
  bool loadData(const std::string path);
  void setDefault();

	float getModifier();
	void setModifier(float _modifier);
	std::shared_ptr<std::vector<std::shared_ptr<Enemy>>> getEnemyVec() const;

private:
  sf::Texture enemySpriteS;
  sf::Texture enemySpriteD;
  sf::Texture enemySpriteL;
  sf::Texture enemySpriteR;
  std::shared_ptr<sf::RenderWindow> window;
  std::shared_ptr<GameState> gameState;

  std::vector<sf::RectangleShape> framesS;
  std::vector<sf::RectangleShape> framesD;
  std::vector<sf::RectangleShape> framesL;
  std::vector<sf::RectangleShape> framesR;

  sf::Vector2f enemyBaseSize{ sf::Vector2f(Clickable::gridSize, Clickable::gridSize) };

  int counter{ 0 };
  int wave{ 1 };
  float modifier{ 1.0f };
  std::shared_ptr<std::vector<std::shared_ptr<Enemy>>> enemyVec;
  const std::vector<sf::Vector2f> pathInCubits;
};

#endif
