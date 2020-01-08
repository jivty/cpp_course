#ifndef TD_GAME_CONTROLLER_H
#define TD_GAME_CONTROLLER_H

#include "GameState.h"
#include "Tower.h"
#include "TowerController.h"
#include "MenuButton.h"

class GameBoard {
public:
  GameBoard(std::shared_ptr<GameState> gameState,
    std::shared_ptr<TowerController> towerController,
    int widthInPixels, std::shared_ptr<sf::RenderWindow>& window);
  ~GameBoard() = default;
  void process(sf::Event event, sf::Vector2i mousePos);
  void render();
  void renderLabels();
  void renderRange(int mouseX, int mouseY, int range, TowerType type);
  void renderShadow(int mouseX, int mouseY, int range);
  int gridStatus[32][18] = { 0 };
  void menu();
  void menuNewGame();
  void menuConfirmation();
  void menuSaving();
  void deathloop();
  void showMenu(const bool cont);
  void showMenuNewGame();
  void showMenuAsking(const bool SaveConf);
  void showLoading();
  void saveMusicSettings();
  bool loadMusicSettings();
  bool saveData(const std::string path);
  bool loadData(const std::string path);
  void updCounters();
  void setDefault();
  sf::Text goldText, waveText, waveWord, healthText, text;

  sf::RectangleShape helpScreen;
  bool isMenu{ true };
  bool isMenuNewGame{ false };
  bool isRunning{ false };
  bool isEndGame{ false };
  bool isRestarted{ false };
  bool isMenuAsking{ false };
  bool isSaveAndQuit{ false };
  int difficulty{ 0 };
  const std::vector<sf::Vector2f> path = { sf::Vector2f(15, 0), sf::Vector2f(15, 4),
      sf::Vector2f(20, 4), sf::Vector2f(22, 4), sf::Vector2f(22, 8), sf::Vector2f(10, 8),
      sf::Vector2f(10, 6), sf::Vector2f(4, 6), sf::Vector2f(4, 13), sf::Vector2f(12, 13),
      sf::Vector2f(12, 15), sf::Vector2f(17, 15), sf::Vector2f(17, 12), sf::Vector2f(21, 12),
      sf::Vector2f(21, 18) };

private:
  std::shared_ptr<sf::RenderWindow> window;
  std::shared_ptr<GameState> gameState;
  std::shared_ptr<TowerController> towerController;
  std::shared_ptr<VolumeButton> buttonSound;
  int width;
  
  sf::RectangleShape groundTile;
  sf::CircleShape hoverRange;
  sf::RectangleShape shadowTile;
  std::unique_ptr<sf::RectangleShape> _goldCounter;
  std::unique_ptr<sf::RectangleShape> _livesCounter;
  std::unique_ptr<sf::RectangleShape> _wavesCounter;
  sf::RectangleShape background;
  sf::RectangleShape deathScreen;
  std::shared_ptr<sf::Texture> _menuTexture{ std::make_shared<sf::Texture>() };
  std::shared_ptr<sf::Texture> _backTexture{ std::make_shared<sf::Texture>() };
  std::shared_ptr<sf::Texture> _groundTexture{ std::make_shared<sf::Texture>() }; 
  std::unique_ptr<sf::Texture> deathscreentexture{ std::make_unique<sf::Texture>() };
  sf::Font font;
  sf::RectangleShape menuBackground;
  sf::RectangleShape buttonNewGame;
  sf::RectangleShape buttonCloseGame;
  sf::RectangleShape buttonContGame;
  sf::Text textNewGame;
  sf::Text textCloseGame;
  sf::Text textContGame;
  sf::Text textLoading;
  sf::RectangleShape buttonLevel1;
  sf::RectangleShape buttonLevel2;
  sf::RectangleShape buttonLevel3;
  sf::RectangleShape buttonLevel4;
  sf::Text textLevel1;
  sf::Text textLevel2;
  sf::Text textLevel3;
  sf::Text textLevel4;
  sf::Text textBack;
  sf::RectangleShape menuAsking;
  sf::RectangleShape buttonYes;
  sf::RectangleShape buttonNo;
  sf::RectangleShape buttonCancel;
  sf::Text textSaving;
  sf::Text textConfirmation;
  sf::Text textYes;
  sf::Text textNo;
  sf::Text textCancel;

  bool gridSpaceAvailable(int gridX, int gridY);
  bool towerIsPurchasable(TowerType type);
};

#endif
