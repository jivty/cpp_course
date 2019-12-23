#ifndef TD_ENEMY_CONTROLLER_H
#define TD_ENEMY_CONTROLLER_H
#include "Enemy.h"
#include "GameState.h"
#include "GameController.h"
#include <SFML/Graphics.hpp>

class EnemyController {
public:
	EnemyController() = default;
	EnemyController(sf::RenderWindow* window, GameState* gameState,
			const std::vector<sf::Vector2f> pathToFollow);
	// This destroys all the enemy that it contains
  ~EnemyController() = default;

	//void turnEnemy(std::shared_ptr<Enemy> enemy, sf::IntRect textureRect, int direction );
  
  //! \brief Spawns enemies
	std::shared_ptr<Enemy> spawnEnemy(sf::Vector2f position, EnemyType type);
	void updateEnemy();
	// This removes a enemy from the vector, setting it to null.
	void removeEnemy(std::shared_ptr<Enemy> targetEnemy);
	// Used by the attackController to deal damage. This function
	// is responsible for updating the state of the enemy, as well
	// as increasing the Tam value when a enemy is defeated
	void dealDamage(std::shared_ptr<Enemy> enemy, int damage);


	void enemyWave(EnemyType type);
	void waveOne();
	void waveTwo();
  void waveThree();
  void waveFour();
  void waveEND();
	// Game functions
	void update();
	// Displays all the contained enemy on the board
	void render();

	// Accessors
	float getModifier();
	void setModifier(float _modifier);
	std::vector<std::shared_ptr<Enemy>>* getEnemyVec();

private:
  sf::Texture* enemySpriteS;
  sf::Texture* enemySpriteD;
  sf::Texture* enemySpriteL;
  sf::Texture* enemySpriteR;
  sf::RenderWindow* window;
  GameState* gameState;

  std::vector<sf::RectangleShape> framesS;
  std::vector<sf::RectangleShape> framesD;
  std::vector<sf::RectangleShape> framesL;
  std::vector<sf::RectangleShape> framesR;

  sf::Vector2f enemyBaseSize = sf::Vector2f(Clickable::gridSize, Clickable::gridSize);
  // This is a difficulty modifer that affects the stats
  // of generated enemy. This is modified when waves change
  float modifier{ 1.0f };
  std::vector<std::shared_ptr<Enemy>>* enemyVec;
  const std::vector<sf::Vector2f> pathInCubits;
};

#endif
