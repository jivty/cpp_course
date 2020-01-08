#ifndef TD_TOWER_BUTTON_H
#define TD_TOWER_BUTTON_H

#include "Clickable.h"
#include "GameState.h"

class TowerButton: public Clickable {
public:
	TowerButton(sf::Vector2f _position, int _radius, std::shared_ptr<sf::Texture> _texture,
			std::string inText, std::string in, TowerType _type,
    std::shared_ptr<GameState> _gameState, std::shared_ptr<sf::Texture> _menutexture);
	void setTextureRect(const sf::IntRect& rect);
	virtual ~TowerButton();
	TowerType getTowerType();
	void setTransparency(const int transparency);

	void update() override;
	void render(sf::RenderWindow& _window) override;
	void renderText(sf::RenderWindow& _window) ;

private:
	TowerType towerType;
	std::shared_ptr<GameState> gameState;
  sf::Font font;

	void onClick() override;
	void onMouseEnter() override;
	void onMousePressed() override;
	void onMouseLeave() override;
	sf::CircleShape graphic;
	bool displayText;
	sf::Text towerButtonText;
	sf::Text towerButtonText2;
	sf::RectangleShape towerTextBack;
};

#endif
