#ifndef TD_GAMEMENU_CONTROLLER_H
#define TD_GAMEMENU_CONTROLLER_H
#include "MenuButton.h"
#include "TowerButton.h"
#include <SFML/Audio.hpp>

class GameMenuController {
public:
	GameMenuController(sf::RenderWindow* windowPointer, GameState* gameState);
	virtual ~GameMenuController();

	void setDebug(bool mode);
	void initialize();
	void run();
	void process(sf::Event event, sf::Vector2i mousePos);
	void update();
	void render();
	sf::Vector2f getMenuPos();

private:
	std::vector<sf::Drawable*> drawVec;
	std::vector<TowerButton*> towerButtonVec;
	std::vector<Clickable*> clickVec;
	std::vector<sf::Texture*> texturesVector;
	sf::RenderWindow* windowPointer;
	sf::Music* music;
	GameState* gameState;
	sf::Vector2f gameSize, menuPos;
	sf::Vector2f menuPosition(float xCubits, float yCubits);

	UpgradeButton* upgradeButton;
};

#endif
