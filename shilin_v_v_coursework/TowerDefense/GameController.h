#ifndef TD_GAME_CONTROLLER_H
#define TD_GAME_CONTROLLER_H

#include "GameState.h"
#include "TowerController.h"
#include "MenuButton.h"

//! \brief Взаимодействие с игровым полем.
class GameBoard {
public:
  
  //! \brief Конструирование по параметрам.
  //!
  //! \param widthInPixels - ширина игрового пространства.
  GameBoard(std::shared_ptr<GameState> gameState,
    std::shared_ptr<TowerController> towerController,
    int widthInPixels, std::shared_ptr<sf::RenderWindow>& window);

  //! \brief Деструктор.
  ~GameBoard() = default;

  //! \brief Обрабатывание события.
  void process(sf::Event event, sf::Vector2i mousePos);

  //! \brief Отображение игрового поля.
  void render();

  //! \brief Отображение параметров состояния игры.
  //!
  //! Отображение количества монет, жизней и номера волны
  void renderLabels();

  //! \brief Отображение радиуса поражения башни.
  void renderRange(int mouseX, int mouseY, int range, TowerType type);

  //! \brief Отображение потенциального места установки башни.
  void renderShadow(int mouseX, int mouseY, int range);

  int gridStatus[32][18] = { 0 }; //!< Состояние клеток игрового поля.

  //! \brief Вызывает главное меню.
  void menu();

  //! \brief Вызывает меню выбора уровня сложности.
  void menuNewGame();

  //! \brief Вызывает диалоговое окно подтверждения начала новой игры.
  void menuConfirmation();

  //! \brief Вызывает диалоговое окно с предложением сохранить игру.
  void menuSaving();

  //! \brief Состояние окончания игры.
  void deathloop();

  //! \brief Отображение главного меню.
  void showMenu(const bool cont);

  //! \brief Отображение меню выбора уровня сложности.
  void showMenuNewGame();

  //! \brief Отображение диалогового окна.
  //!
  //! \param SaveConf - true, если предлагается сохранение игры,
  //! false, если подтверждается начало новой игры
  void showMenuAsking(const bool SaveConf);

  //! \brief Отображение экрана загрузки.
  void showLoading();

  //! \brief Сохранение состояния музыкального сопровождения.
  void saveMusicSettings();

  //! \brief Загрузка состояния музыкального сопровождения.
  bool loadMusicSettings();

  //! \brief Сохранение параметров состояния игры.
  bool saveData(const std::string path);

  //! \brief Загрузка параметров состояния игры.
  bool loadData(const std::string path);

  //! \brief Обновление параметров состояния игры.
  void updCounters();

  //! \brief Установка начальных параметров состояния игры.
  void setDefault();

  sf::RectangleShape helpScreen; //!< Экран справки.
  bool isMenu{ true }; //!< Состояние главного меню.
  bool isMenuNewGame{ false }; //!< Состояние меню выбора уровня сложности.
  bool isRunning{ false }; //!< Состояние игрового процесса.
  bool isEndGame{ false }; //!< Состояние проигрыша.
  bool isRestarted{ false }; //!< Необходимость перезапуска.
  bool isMenuAsking{ false }; //!< Состояние меню подтверждения.
  bool isSaveAndQuit{ false }; //!< Необходимость сохранения и завершения.
  int difficulty{ 0 }; //!< Сложность игры.
  const std::vector<sf::Vector2f> path = { sf::Vector2f(15, 0), sf::Vector2f(15, 4),
      sf::Vector2f(20, 4), sf::Vector2f(22, 4), sf::Vector2f(22, 8), sf::Vector2f(10, 8),
      sf::Vector2f(10, 6), sf::Vector2f(4, 6), sf::Vector2f(4, 13), sf::Vector2f(12, 13),
      sf::Vector2f(12, 15), sf::Vector2f(17, 15), sf::Vector2f(17, 12), sf::Vector2f(21, 12),
      sf::Vector2f(21, 18) }; //!< Путь перемещения NPC.

private:
  std::shared_ptr<sf::RenderWindow> window;
  std::shared_ptr<GameState> gameState;
  std::shared_ptr<TowerController> towerController;
  std::shared_ptr<VolumeButton> buttonSound;
  sf::Text goldText;
  sf::Text waveText;
  sf::Text waveWord;
  sf::Text healthText;
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
  int width;
};

#endif
