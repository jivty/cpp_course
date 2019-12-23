#ifndef TD_GAME_CONTROLLER_H
#define TD_GAME_CONTROLLER_H

#include "GameState.h"
#include "Tower.h"
#include "TowerController.h"

// Game Controller keeps all Game State Variables Running and Updated
class GameController {
private:

public:
	GameController();

	void process();
	void update();
	void render();
};

// Game Board generates the map, and handles interactions
// for any entities sitting on the map
class GameBoard {
public:
	GameBoard(GameState* gameState, TowerController* towerController,
			int widthInPixels);

	bool validatePos(int mouseX, int mouseY, int range);
	void process(sf::Event event, sf::Vector2i mousePos);
	void update();
	void render();		// Render board
	void renderLabels();
	void renderRange(int mouseX, int mouseY, int range);
	void renderShadow(int mouseX, int mouseY, int range);
	int gridStatus[32][18] = { 0 };
  void menu(sf::RenderWindow* win);

private:
  GameState* gameState;
  TowerController* towerController;
  int width;

  // Helper functions
  bool gridSpaceAvailable(int gridX, int gridY);
  bool towerIsPurchasable(TowerType type);
};

#endif
