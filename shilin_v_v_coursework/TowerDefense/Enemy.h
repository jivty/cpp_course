#ifndef TD_ENEMY_H
#define TD_ENEMY_H

#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <fstream>

//! \brief Враждебный NPC.
class Enemy {
public:

  //! \brief Умолчательный конструктор.
  Enemy() = default;

  //! \brief Конструитровение NPC по параметрам.
  //!
  //! \param position - начальная позиция
  //! \param size - размер
  //! \param texture - текстура
  //! \param _gold - получаемое количество монет за уничтожение NPC
  //! \param _health - здоровье
  //! \param _damage - наносимый урон игроку по завершении пути
  //! \param _pixelSpeed - скорость передвижения
  //! \param type - тип NPC
  //! \param targetPath - индекс участка пути
	Enemy(sf::Vector2f position, sf::Vector2f size, std::shared_ptr<sf::Texture> texture,
			int _gold, int _health, int _damage, float _pixelSpeed, EnemyType type, int targetPath = 0);

  //! \brief Деструктор.
  ~Enemy() = default;

  //! \brief Установка кадров анимации при перемещении.
  void setFrames(std::shared_ptr<sf::Texture> texture, EnemyType type);

  //! \brief Установка следующая кадра.
  void nextFrame();

  //! \brief Отображение NPC.
	void render(std::shared_ptr<sf::RenderWindow> window);

  //! \brief Получение типа NPC.
	EnemyType getEnemyType() const;

  //! \brief Получаемое количество монет за уничтожение NPC.
	int getGoldValue();

  //! \brief Здоровье NPC.
	int getHealth();

  //! \brief Наносимый урон игркоку по заверешнии пути.
	int getDamage();

  //! \brief Скорость передвижения.
	int getPixelSpeed();

  //! \brief Индекс участка пути.
	int getPathIndex();

  //! \brief Позиция NPC.
	sf::Vector2f getPosition();

  //! \brief Позиция центра NPC.
	sf::Vector2f getCenterPosition();

  //! \brief Установка позиции NPC.
	void setPosition(sf::Vector2f position);

  //! \brief Прямоугольный участок текстуры.
	sf::IntRect getTextureRect();

  //! \brief Установка прямоугольного участка текстуры.
	void setTextureRect(sf::IntRect textureRect);

  //! \brief Уменьшение здоровья NPC.
	int reduceHealth(int damage);

  //! \brief Индексное продвижение по участкам пути.
	void increasePathIndex();

  //! \brief Горизонтальное направление движения.
  //!
  //! true - последнее горизонтальное движение было вправо
  //! false - последнее горизонтальное движение было влево
  bool dir{ true };

private:
  EnemyType type{ EnemyType::empty };
  sf::RectangleShape shape{ sf::RectangleShape(sf::Vector2f(0, 0)) };
  std::shared_ptr<sf::Texture> texture;
  sf::IntRect textureRect{ sf::IntRect(0,0,0,0) };
  std::vector<sf::RectangleShape> frames;
  int currentFrame{ 0 };
  int goldValue{ 0 };
  int health{ 0 };
  int damage{ 0 };
  float pixelSpeed{ 0 };
  int targetPathPoint{ 0 };
};

#endif
