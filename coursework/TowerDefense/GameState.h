#ifndef TD_GAMESTATE_H
#define TD_GAMESTATE_H
#include "Timer.h"
#include "Tower.h"

enum class EnemyType {
	skeleton, demon, lancer, rhino
};

class GameState {
public:
	GameState(Timer* timer);
	virtual ~GameState();
	bool dirtyBit = true;
	Timer* timer;
	sf::Vector2i mousePos;

	//Accessors
	int getHealth();
	int getTams();
	int getCurrentWave();
	void setCurrentWave(int wave);
	int getEnemyRemaining();
	int getEnemyEliminated();
	bool getHelperState();
	// This is used by the GameMenuController to determine opacity,
	// as well as determining which tower the towerController should buy
	TowerType getPurchaseTower();
	void setPurchaseTower(TowerType towerType);
	Tower* getBoardTower();
	void setBoardTower(Tower* tower);

	std::map<string, int> getTowerProps(TowerType type);
	std::map<string, int> getEnemyProps(EnemyType type);

	void startGame();				// Starts game
	void endGame();					// Ends game
	void startWave();				// Starts wave
	void updateHealthBy(int update);	// Update player lives
	void updateTamBy(int update);		// Update player currency
	void toggleHelpScreen();

private:
  // This contains info about tower pricing, damage, etc
  std::map<TowerType, std::map<string, int>> towerProps;
  std::map<EnemyType, std::map<string, int>> enemyProps;

  // Should the help menu be active
  bool helperState{ false };

  int health = 20;
  int tams = 1000;
  int currentWave = 1;
  int enemyRemaining = -1;
  int enemyEliminated = 0;

  TowerType purchaseTower = TowerType::empty;
  // This is used by the upgrade button
  Tower* boardTower = nullptr;

};

#endif
