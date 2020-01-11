#ifndef TD_GAMESTATE_H
#define TD_GAMESTATE_H

#include "Timer.h"
#include "Tower.h"
#include <SFML/Audio.hpp>
#include <iostream>

//! \brief Типы NPC.
enum class EnemyType {
	skeleton, demon, lancer, rhino, empty
};

//! \brief Состояние игры.
class GameState {
public:

  //! \brief Конструктор.
  GameState(std::shared_ptr<Timer> timer);

  //! \brief Виртуальный деструктор.
  virtual ~GameState();

  bool dirtyBit = true; //!< Наличие изменения игрового состояния.

  //! \brief Таймер.
  std::shared_ptr<Timer> timer;

  //! \brief Позиция игрового курсора.
  sf::Vector2i mousePos;

  //! \brief Здоровье игрока.
  int getHealth();

  //! \brief Количество монет.
  int getGold();

  //! \brief Номер волны NPC.
  int getCurrentWave();

  //! \brief Установка номера волны NPC.
  void setCurrentWave(int wave);

  //! \brief Состояние экрана справки.
  bool getHelperState();

  //! \brief Тип выбранной башни для покупки.
  TowerType getPurchaseTower();

  //! \brief Установить тип выбранной башний для покупки.
  void setPurchaseTower(TowerType towerType);

  //! \brief Выбранная башня на игровом поле.
  std::shared_ptr<Tower> getBoardTower();

  //! \brief Установить выбранную башню на игровом поле.
  void setBoardTower(std::shared_ptr<Tower> tower);

  //! \brief Установка начальных параметров игры.
  void setDefault();

  //! \brief Характеристика башни указанного типа.
  std::map<std::string, int> getTowerProps(TowerType type);

  //! \brief Характеристика NPC указанного типа.
  std::map<std::string, int> getEnemyProps(EnemyType type);

  //! \brief Музыкальное сопровождение.
  std::shared_ptr<sf::Music> getMusic();

  //! \brief Запуск игры.
  //!
  //! \param dif - уровень сложности игры
  void startGame(const int dif);

  //! \brief Изменение жизней игрока.
  //!
  //! \param update - количество инкрементируемых жизней
  void updateHealthBy(int update);

  //! \brief Изменение количества монет.
  //!
  //! \param update - количество инкрементируемых монет
  void updateGoldBy(int update);

  //! \brief Переключить состояние экрана справки.
  void toggleHelpScreen();

  //! \brief Состояние музыкального сопровождения.
  bool getMusicStatus();

  //! \brief Выбранный уровень сложности.
  const int getDifficulty() const;

  //! \brief Сохранение параметры игры.
  bool saveData(const std::string path);

  //! \brief Загрузка параметров игры.
  bool loadData(const std::string path);

private:
  std::map<TowerType, std::map<std::string, int>> towerProps;
  std::map<EnemyType, std::map<std::string, int>> enemyProps;
  std::shared_ptr<sf::Music> music;
  bool helperState{ false };
  int health{ 20 };
  int gold{ 1000 };
  int currentWave{ 1 };
  int difficulty{ 1 };
  TowerType purchaseTower = TowerType::empty;
  std::shared_ptr<Tower> boardTower{ nullptr };
};

#endif
