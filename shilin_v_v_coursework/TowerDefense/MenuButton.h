#ifndef TD_MENUBUTTON_H
#define TD_MENUBUTTON_H

#include "Clickable.h"
#include "GameState.h"
#include "Timer.h"

class MenuButton: public Clickable {
public:
	MenuButton(sf::Vector2f _position, int _sizex, int _sizey,
			std::shared_ptr<sf::Texture> _texture);
  virtual ~MenuButton() = default;
	void setTextureRect(const sf::IntRect& rect);
	void setTransparency(const int transparency);
	void update() override;
	void render(sf::RenderWindow& _window) override;
  void turnColor(const bool onoff);

private:
  bool onoff{ false };
	void onClick() override;
	void onMouseEnter() override;
	void onMousePressed() override;
	void onMouseLeave() override;
	sf::RectangleShape graphic;
};

class VolumeButton: public MenuButton {
public:
	VolumeButton(sf::Vector2f _position, int _sizex, int _sizey,
    std::shared_ptr<sf::Texture> _texture, 
    std::shared_ptr<sf::Music> music);
  ~VolumeButton() = default;
  void getStatus();
  void updOnOff();
private:
	std::shared_ptr<sf::Music> music;
	bool isPlaying;
	void onClick() override;
  void onMouseEnter() override;
};

class InfoButton: public MenuButton {
public:
	InfoButton(sf::Vector2f _position, int _sizex, int _sizey,
		std::shared_ptr<sf::Texture> _texture, 
    std::shared_ptr<GameState> gameState);
  ~InfoButton() = default;
private:
	std::shared_ptr<GameState> gameState;
	void onClick() override;
};

class PauseButton: public MenuButton {
public:
	PauseButton(sf::Vector2f _position, int _sizex, int _sizey,
		std::shared_ptr<sf::Texture> _texture, 
    std::shared_ptr<Timer> timer);
  ~PauseButton() = default;
private:
	std::shared_ptr<Timer> timer;
	void onClick() override;
};

class UpgradeButton: public MenuButton {
public:
	UpgradeButton(sf::Vector2f _position, int _sizex, int _sizey,
  	std::shared_ptr<sf::Texture> _texture, 
    std::shared_ptr<GameState> gameState);
  ~UpgradeButton() = default;
	bool getCanUpgrade();
	void setCanUpgrade(bool status);
private:
	std::shared_ptr<GameState> gameState;
	bool selected;
	bool canUpgrade = true;

	void onClick() override;
	void onMouseEnter() override;
	void onMouseLeave() override;

};

#endif 
