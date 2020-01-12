#ifndef TD_MENUBUTTON_H
#define TD_MENUBUTTON_H

#include "Clickable.h"
#include "GameState.h"
#include "Timer.h"

//! \brief Кнопка меню.
class MenuButton: public Clickable {
public:

  //! \brief Конструирование кнопки меню по параметрам.
  //!
  //! \param _position - позиция кнопки
  //! \param _sizex - размер по горизонтали
  //! \param _sizey - размер по вертикали
  //! \param _texture - текстура
	MenuButton(sf::Vector2f _position, int _sizex, int _sizey,
			std::shared_ptr<sf::Texture> _texture);

  //! \brief Деструктор.
  ~MenuButton() = default;

  //! \brief Установка прямоугольного участка текстуры.
	void setTextureRect(const sf::IntRect& rect);

  //! \brief Установка степени прозрачности.
	void setTransparency(const int transparency);

  //! \brief Обновление положения кнопки меню.
	void update() override;

  //! \brief Отображение кнопки меню.
	void render(sf::RenderWindow& _window) override;

  //! \brief Смена состояния и оттенка цвета.
  //!
  //! \param onoff - если true, то вкл., если false, то выкл.
  void turnColor(const bool onoff);

private:
  bool onoff{ false };
	void onClick() override;
	void onMouseEnter() override;
	void onMousePressed() override;
	void onMouseLeave() override;
	sf::RectangleShape graphic;
};

//! \brief Кнопка музыкального сопровождения.
class VolumeButton: public MenuButton {
public:

  //! \brief Конструирование кнопки музыкального сопровождения.
  //!
  //! \param _position - позиция кнопки
  //! \param _sizex - размер по горизонтали
  //! \param _sizey - размер по вертикали
  //! \param _texture - текстура
  //! \param music - музыкальный плеер
	VolumeButton(sf::Vector2f _position, int _sizex, int _sizey,
    std::shared_ptr<sf::Texture> _texture, 
    std::shared_ptr<sf::Music> music);

  //! \brief Деструктор.
  ~VolumeButton() = default;

private:
	std::shared_ptr<sf::Music> music;
	bool isPlaying;
	void onClick() override;
  void onMouseEnter() override;
};

//! \brief Кнопка справки.
class InfoButton: public MenuButton {
public:

  //! \brief Конструирование кнопки справки.
  //!
  //! \param _position - позиция кнопки
  //! \param _sizex - размер по горизонтали
  //! \param _sizey - размер по вертикали
  //! \param _texture - текстура
	InfoButton(sf::Vector2f _position, int _sizex, int _sizey,
		std::shared_ptr<sf::Texture> _texture, 
    std::shared_ptr<GameState> gameState);

  //! \brief Деструктор.
  ~InfoButton() = default;

private:
	std::shared_ptr<GameState> gameState;
	void onClick() override;
};

//! \brief Кнопка паузы.
class PauseButton: public MenuButton {
public:

  //! \brief Конструирование кнопки паузы.
  //!
  //! \param _position - позиция кнопки
  //! \param _sizex - размер по горизонтали
  //! \param _sizey - размер по вертикали
  //! \param _texture - текстура
	PauseButton(sf::Vector2f _position, int _sizex, int _sizey,
		std::shared_ptr<sf::Texture> _texture, 
    std::shared_ptr<Timer> timer);

  //! \brief Деструктор.
  ~PauseButton() = default;

private:
	std::shared_ptr<Timer> timer;
	void onClick() override;
};

//! \brief Кнопка улучшения.
class UpgradeButton: public MenuButton {
public:

  //! \brief Конструирование кнопки улучшения.
  //!
  //! \param _position - позиция кнопки
  //! \param _sizex - размер по горизонтали
  //! \param _sizey - размер по вертикали
  //! \param _texture - текстура
	UpgradeButton(sf::Vector2f _position, int _sizex, int _sizey,
  	std::shared_ptr<sf::Texture> _texture, 
    std::shared_ptr<GameState> gameState);

  //! \brief Деструктор.
  ~UpgradeButton() = default;

  //! \brief Возможность улучшения.
	bool getCanUpgrade();

  //! \brief Установка возможности улучшения.
	void setCanUpgrade(bool status);

private:
	std::shared_ptr<GameState> gameState;
  bool selected{ false };
  bool canUpgrade{ true };
	void onClick() override;
	void onMouseEnter() override;
	void onMouseLeave() override;
};

#endif 
