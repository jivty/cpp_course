#ifndef TD_GAMEMENU_CONTROLLER_H
#define TD_GAMEMENU_CONTROLLER_H

#include "MenuButton.h"
#include "TowerButton.h"

//! \brief Управление игровым меню.
class GameMenuController {
public:

  //! \brief Конструирование контроллера по параметрам.
	GameMenuController(std::shared_ptr<sf::RenderWindow> windowPointer, 
    std::shared_ptr<GameState> gameState);

  //! \brief Деструктор.
	~GameMenuController() = default;

  //! \brief Обрабатывание события.
	void process(sf::Event event, sf::Vector2i mousePos);

  //! \brief Обновление игрового меню.
	void update();

  //! \brief Отображение игрового меню.
	void render();

  //! \brief Позиция игрового меню.
	sf::Vector2f getMenuPos();

private:
	std::vector<std::shared_ptr<sf::Drawable>> drawVec;
	std::vector<std::shared_ptr<TowerButton>> towerButtonVec;
	std::vector<std::shared_ptr<Clickable>> clickVec;
	std::vector<std::shared_ptr<sf::Texture>> texturesVector;
	std::shared_ptr<sf::RenderWindow> windowPointer;
	std::shared_ptr<GameState> gameState;
	sf::Vector2f gameSize, menuPos;
	sf::Vector2f menuPosition(float xCubits, float yCubits);
  std::shared_ptr<sf::Music> music;
	std::shared_ptr<UpgradeButton> upgradeButton;
};

#endif
