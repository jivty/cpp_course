#include "Tower.h"
#include <SFML/Graphics.hpp>
using namespace std;
typedef sf::IntRect* srcArrayPtr;

Tower::Tower(const sf::Vector2f position, sf::Texture* _texture, TowerType _type,
		int damage, int range, int cooldown) :
		Clickable(position, sf::Vector2f(Clickable::gridSize, gridSize)), coordinate(position), towerPos(position), texture(
				_texture), type(_type), towerDamage(damage), towerRange(range), baseCooldown(
				cooldown) {
	// these can be changed to adapt to whichever tower spritesheet we are using
	// and to their sizes, as well as the coordinate
	// construct current sprite on the given position
	srcSprite = new srcArrayPtr[numPers];
	int x = 5;
	int y = -2;
	for (int i = 0; i < numPers; i++) {
		srcSprite[i] = new sf::IntRect[numFrame];
		for (int j = 0; j < numFrame; j++) {
			srcSprite[i][j] = sf::IntRect(x, y, 75, 86);
			x += 40;
		}
		y += 60;
		x = 0;
	}
	
	currentSprite = srcSprite[0][0];
	towerSprite = sf::Sprite(*texture, currentSprite);
	towerSprite.setPosition(towerPos.x, towerPos.y);
  towerSprite.setScale(float(Clickable::gridSize) / float(currentSprite.width),
    float(Clickable::gridSize) / float(currentSprite.height));

	// set initial attributes
	mode = 'a';
	direction = 'r';
	currentCooldown = 0;
	wasClicked = false;
	upgradeCost = 20;
}

Tower::~Tower() {
	for (int i = 0; i < numPers; i++) {
		delete[] srcSprite[i];
		srcSprite[i] = nullptr;
	}
	delete[] srcSprite;
	srcSprite = nullptr;
}

TowerType Tower::getTowerType() const {
	return this->type;
}

// test heap functions
void Tower::setPosition(sf::Vector2f newPosition) {
	towerSprite.setPosition(newPosition);
}

void Tower::setMode(char AorS) {
	mode = AorS;
}

char Tower::getDirection() const {
	return direction;
}

char Tower::getMode() const {
	return mode;
}

void Tower::setDirection(char UDLR) {
	direction = UDLR;
}

void Tower::decreaseCooldown() {
	this->currentCooldown--;
}
void Tower::resetCooldown() {
	this->currentCooldown = this->baseCooldown;
}

void Tower::update() {
}
void Tower::render(sf::RenderWindow& _window) {
	_window.draw(this->towerSprite);
}

void Tower::onClick() {
	this->wasClicked = true;
}

sf::Vector2f Tower::getPosition() const {
	return towerPos;
}

sf::Vector2f Tower::getCenterPosition() const {
	sf::Vector2f center = this->towerSprite.getPosition();
  center.x += Clickable::gridSize / 2;
	center.y += Clickable::gridSize / 2;
	return center;
}

float Tower::getDamage() const {
	return this->towerDamage;
}
float Tower::getRange() const {
	return this->towerRange;
}

int Tower::getCooldown() {
	return this->currentCooldown;
}

int Tower::getUpgradeCost() {
	return this->upgradeCost;
}

void Tower::enemyDirection(sf::Vector2f enemyPos) {
	float dx = coordinate.x - enemyPos.x;
	float dy = coordinate.y - enemyPos.y;
	if ((dy > 0 && (dx >= 0 && dx < dy)) || (dy > 0 && (dx < 0 && -dx <= dy))) {
		if (direction != 'u') {
			setDirection('u');
			//cout << "direction up" << endl;
		}
	}
	else if ((dy > 0 && (dx <= 0 && dx < dy)) || (dy > 0 && (dx < 0 && -dx <= dy))) {
		if (direction != 'r') {
			setDirection('r');
			//cout << "direction right" << endl;
		}
	}
	else if ((dy < 0 && (dx >= 0 && dx <= -dy)) || (dy < 0 && (dx < 0 && dx > dy))) {
		if (direction != 'd') {
			setDirection('d');
			//cout << "direction down" << endl;
		}
	}
	else if ((dx > 0 && (dy >= 0 && dx >= dy)) || (dx > 0 && (dy < 0 && dx > -dy))) {
		if (direction != 'l') {
			setDirection('l');
			//cout << "direction left" << endl;
		}
	}
	else {
		setDirection('d');
	}
}

sf::Sprite Tower::getTowerSprite() const {
	return towerSprite;
}

sf::Vector2f Tower::getOriginalTowerPosition()
{
	return coordinate;
}

void resetSpriteRange() {

}
//
//void Tower::flipSprite() {
//	towerSprite.setScale(-1.0, 1.0);
//	towerSprite.setPosition(towerPos.x +128, towerPos.y);
//}
//void Tower::flipBack() {
//	towerSprite.setScale(1.0, 1.0);
//	towerSprite.setPosition(towerPos.x, towerPos.y);
//}

float Tower::enemyDistance(sf::Vector2f enemy) // returns distance between two points
		{
	float x = (coordinate.x - enemy.x) * (coordinate.x - enemy.x);
	float y = (coordinate.y - enemy.y) * (coordinate.y - enemy.y);
	float xPlusY = x + y;
	return (float) (powf(xPlusY, 0.5)); //returns hypotenuse , ie. distance between points
}

bool Tower::enemyCollides(sf::Vector2f enemy) // simple collision detection between two circles
{
	float dist = enemyDistance(enemy); // gets distance between circles
	return dist < towerRange; // if dist < tower range we have a collision
}

void Tower::Attack() {
	// (myClock.getElapsedClick() > attackSpeeck) or whatever,
	// waiting for the "click" done by the controller class
	// use another layer of conditional to determine which direction is facing
	// i.e. switch (direction) {case 'l': //sth; case 'r': //sth; ...}
	// where "sth" is using the logic bellow to loop through its sprites
	//spriteCooldownSwitch starts at 15, each tick represents one cycle
	/*switch (direction) {
	case 'u':
		if (spriteFrame){
			towerSprite.setTextureRect(srcSprite[1][0]);
			spriteFrame = false;
		}
		else {
			towerSprite.setTextureRect(srcSprite[1][1]);
			spriteFrame = true;
		}
		break;
	case 'd':
		if (spriteFrame) {
			towerSprite.setTextureRect(srcSprite[0][0]);
			spriteFrame = false;
		}
		else{
			towerSprite.setTextureRect(srcSprite[0][1]);
			spriteFrame = true;
		}
		break;
	case 'l':
		if (spriteFrame) {
			towerSprite.setTextureRect(srcSprite[2][0]);
			spriteFrame = false;
			flipSprite();
		}
		else {
			towerSprite.setTextureRect(srcSprite[2][1]);
			spriteFrame = true;
			flipSprite();
		}
		break;
	case 'r':
		if (spriteFrame) {
			towerSprite.setTextureRect(srcSprite[2][0]);
			spriteFrame = false;
			flipBack();
		}
		else{
			towerSprite.setTextureRect(srcSprite[2][1]);
			spriteFrame = true;
			flipBack();
		}
		break;*/
	//} // end switch
}

//void Tower::Attack() {
//	// (myClock.getElapsedClick() > attackSpeeck) or whatever,
//	// waiting for the "click" done by the controller class
//	// use another layer of conditional to determine which direction is facing
//	// i.e. switch (direction) {case 'l': //sth; case 'r': //sth; ...}
//	// where "sth" is using the logic bellow to loop through its sprites
//	//spriteCooldownSwitch starts at 15, each tick represents one cycle
//	spriteCooldownSwitch= spriteCooldownSwitch-3;
//	if (spriteCooldownSwitch < 0)
//		spriteCooldownSwitch = 30;
//	switch (direction) {
//	case 'u':
//		if (spriteCooldownSwitch <= 30 && spriteCooldownSwitch > 15)
//			towerSprite.setTextureRect(srcSprite[1][0]);
//		else if (spriteCooldownSwitch < 15)
//			towerSprite.setTextureRect(srcSprite[1][1]);
//		break;
//	case 'd':
//		if (spriteCooldownSwitch <= 30 && spriteCooldownSwitch > 15)
//			towerSprite.setTextureRect(srcSprite[0][0]);
//		else if (spriteCooldownSwitch < 15)
//			towerSprite.setTextureRect(srcSprite[0][1]);
//		break;
//	case 'l':
//		if (spriteCooldownSwitch <= 30 && spriteCooldownSwitch > 15) {
//			towerSprite.setTextureRect(srcSprite[2][0]);
//			//if (spriteCooldownSwitch == 15)
//			flipSprite();
//		}
//		else if (spriteCooldownSwitch < 15) {
//			towerSprite.setTextureRect(srcSprite[2][1]);
//			//if ()
//			flipSprite();
//		}
//		break;
//	case 'r':
//		if (spriteCooldownSwitch <= 30 && spriteCooldownSwitch > 15) {
//			towerSprite.setTextureRect(srcSprite[2][0]);
//			flipBack();
//		}	
//		else if (spriteCooldownSwitch < 15) {
//			towerSprite.setTextureRect(srcSprite[2][1]);
//			flipBack();
//		}
//			
//		break;
//	} // end switch
//}

void Tower::StopAttack() {
	currentSprite = srcSprite[0][0];
	towerSprite.setTextureRect(currentSprite);
}

void Tower::upgrade() {
	this->towerDamage *= 1.2;
	this->towerRange *= 1.2;
	this->currentCooldown *= 1.1;
	this->upgradeCost*= 1.8;
}

srcArrayPtr* Tower::getIntRects() const {
	srcArrayPtr* newArr = new srcArrayPtr[numPers];
	for (int i = 0; i < numPers; i++) {
		newArr[i] = new sf::IntRect[numFrame];
		for (int j = 0; j < numFrame; j++) {
			newArr[i][j] = srcSprite[i][j];
		}
	}
	return newArr;
}

/*

 DONE THROWING FREC
 ==================
 Start Ultimate Tower

 */
//
//UltimateTower::UltimateTower(const std::vector<float> coordinateV) {
//	/* These should all go into the three child classes
//	 // for each of the child classes:
//	 - set position from parameter -DONE
//	 - set texture of the file from its path -DONE
//	 - define the IntRect for each sprite from the spritesheet -DONE
//	 - define the IntRect for the default sprite (when not attacking) -DONE
//	 - define attack speed (to "tick")
//
//	 # Note: the sf::Clock thing should probably be gone
//	 # since we are matching the time to a "tick"
//	 */
//
//	// these can be changed to adapt to whichever tower spritesheet we are using
//	// and to their sizes, as well as the coordinate
//	towerTexture.loadFromFile(
//			"images/towers/towerU.png");
//
//	// set coordinate
//	coordinate = coordinateV;
//
//	// construct current sprite on the given position
//	srcSprite = new srcArrayPtr[numPers];
//	int x = 10;
//	int y = 0;
//	for (int i = 0; i < numPers; i++) {
//		srcSprite[i] = new sf::IntRect[numFrame];
//		for (int j = 0; j < numFrame; j++) {
//			srcSprite[i][j] = sf::IntRect(x, y, 80, 86);
//			x += 60;
//		}
//		y += 60;
//		x = 0;
//	}
//	currentSprite = srcSprite[0][0];
//	// direction = 'd';
//	// mode = 'S';
//	towerSprite.setTexture(towerTexture);
//	towerSprite.setTextureRect(currentSprite);
//  towerSprite.setScale(0.9f, 0.9f);
//	towerSprite.setPosition(coordinate[0], coordinate[1]);
//	towerAttributes = new float[3];
//	towerAttributes[0] = 10.25f; // speed
//	towerAttributes[1] = 2.0; // range
//	towerAttributes[2] = 1.0; // damage
//}
//
//void UltimateTower::Attack() {
//	// (myClock.getElapsedClick() > attackSpeeck) or whatever, 
//	// waiting for the "click" done by the controller class
//	if (animationClock.getElapsedTime().asSeconds() > towerAttributes[0]) {
//		// use another layer of conditional to determine which direction is facing
//		// i.e. switch (direction) {case 'l': //sth; case 'r': //sth; ...}
//		// where "sth" is using the logic bellow to loop through its sprites
//
//		//switch (direction) {
//		//case 'u':
//		//	if (currentSprite == srcSprite[1][0]) {
//		//		currentSprite = srcSprite[1][1];
//		//		towerSprite.setTextureRect(currentSprite);
//		//	} else {
//		//		currentSprite = srcSprite[1][0];
//		//		towerSprite.setTextureRect(currentSprite);
//		//	} // end if else
//		//	break;
//		//case 'd':
//		//	if (currentSprite == srcSprite[0][0]) {
//		//		currentSprite = srcSprite[0][1];
//		//		towerSprite.setTextureRect(currentSprite);
//		//	} else {
//		//		currentSprite = srcSprite[0][0];
//		//		towerSprite.setTextureRect(currentSprite);
//		//	} // end if else
//		//	break;
//		//case 'l':
//		//	if (currentSprite == srcSprite[2][0]) {
//		//		currentSprite = srcSprite[2][1];
//		//		towerSprite.setTextureRect(currentSprite);
//		//		//towerSprite.setScale(-1.0,1.0);
//		//	} else {
//		//		currentSprite = srcSprite[2][0];
//		//		towerSprite.setTextureRect(currentSprite);
//		//		flipSprite();
//		//	} // end if else
//		//	break;
//		//case 'r':
//		//	if (currentSprite == srcSprite[2][0]) {
//		//		currentSprite = srcSprite[2][1];
//		//		towerSprite.setTextureRect(currentSprite);
//		//		//towerSprite.setScale(1.0, 1.0);
//		//	} else {
//		//		currentSprite = srcSprite[2][0];
//		//		towerSprite.setTextureRect(currentSprite);
//		//		flipBack();
//		//	}
//		//	break;
//		//} // end switch
//		animationClock.restart();
//	} // end switching figuresprite
//}
//
//void UltimateTower::StopAttack() {
//	currentSprite = srcSprite[0][0];
//	towerSprite.setTextureRect(currentSprite);
//}
//
//void UltimateTower::setMode(char AorS) {
//	mode = AorS;
//}
//
//char UltimateTower::getMode() const {
//	return mode;
//}
//
//void UltimateTower::setDirection(char UDLR) {
//	direction = UDLR;
//}
//
//char UltimateTower::getDirection() const {
//	return direction;
//}
////
////void UltimateTower::enemyDirection(sf::Vector2f enemyPos) {
////	float dx = towerPos.x - enemyPos.x;
////	float dy = towerPos.y - enemyPos.y;
////	if (dy > 0 && dy > dx && dx < -dy)
////		setDirection('u');
////	else if (dx < 0 && -dx > dy && dy >= dx)
////		setDirection('r');
////	else if (dy < 0 && dy < dx && -dy >= dx)
////		setDirection('d');
////	else
////		setDirection('l');
////}
//
//sf::Sprite UltimateTower::getTowerSprite() const {
//	return towerSprite;
//}
///*
//void UltimateTower::flipSprite() {
//	towerSprite.setScale(-1.0, 1.0);
//	towerSprite.setPosition(coordinate[0] + 128, coordinate[1]);
//}
//void UltimateTower::flipBack() {
//	towerSprite.setScale(1.0, 1.0);
//	towerSprite.setPosition(coordinate[0], coordinate[1]);
//}*/
//
//// new
//sf::Vector2f UltimateTower::gettowerPosition() const {
//	return towerPos;
//}
//
//// new
//float UltimateTower::getDamage() const {
//	return towerAttributes[2];
//}
//
//// new
//float UltimateTower::enemyDistance(sf::Vector2f enemy) // returns distance between two points
//		{
//	float x = (towerPos.x - enemy.x) * (towerPos.x - enemy.x);
//	float y = (towerPos.y - enemy.y) * (towerPos.y - enemy.y);
//	float xPlusY = x + y;
//	return (float) (powf(xPlusY, 0.5)); //returns hypotenuse , ie. distance between points
//}
//
//// new
//bool UltimateTower::enemyCollides(sf::Vector2f enemy) // simple collision detection between two circles
//		{
//	float dist = enemyDistance(enemy); // gets distance between circles
//	return dist < towerAttributes[1]; // if dist < tower range we have a collision
//}
//
//// new
//void UltimateTower::upgrade() {
//
//}
//
///*
//
// DONE THROWING FREC
// ==================
// Start Ultimate Tower
//
// */
//
//MagicTower::MagicTower(const std::vector<float> coordinateV) {
//	/* These should all go into the three child classes
//	 // for each of the child classes:
//	 - set position from parameter -DONE
//	 - set texture of the file from its path -DONE
//	 - define the IntRect for each sprite from the spritesheet -DONE
//	 - define the IntRect for the default sprite (when not attacking) -DONE
//	 - define attack speed (to "tick")
//
//	 # Note: the sf::Clock thing should probably be gone
//	 # since we are matching the time to a "tick"
//	 */
//
//	// these can be changed to adapt to whichever tower spritesheet we are using
//	// and to their sizes, as well as the coordinate
//	towerTexture.loadFromFile(
//			"C:\\VisualStudioWork\\TryAnimation\\SwingTowerSprite.png");
//
//	// set coordinate
//	coordinate = coordinateV;
//
//	// construct current sprite on the given position
//	srcSprite = new srcArrayPtr[numPers];
//	int x = 10;
//	int y = 0;
//	for (int i = 0; i < numPers; i++) {
//		srcSprite[i] = new sf::IntRect[numFrame];
//		for (int j = 0; j < numFrame; j++) {
//			srcSprite[i][j] = sf::IntRect(x, y, 128, 128);
//			x += 128;
//		}
//		y += 128;
//		x = 0;
//	}
//	currentSprite = srcSprite[0][0];
//	// direction = 'd';
//	// mode = 'S';
//	towerSprite.setTexture(towerTexture);
//	towerSprite.setTextureRect(currentSprite);
//  towerSprite.setScale(0.9f, 0.9f);
//	towerSprite.setPosition(coordinate[0], coordinate[1]);
//	towerAttributes = new float[3];
//	towerAttributes[0] = 0.25f; // speed
//	towerAttributes[1] = 2.0; // range
//	towerAttributes[2] = 1.0; // damage
//}
//
//void MagicTower::Attack() {
//	// (myClock.getElapsedClick() > attackSpeeck) or whatever, 
//	// waiting for the "click" done by the controller class
//	//if (animationClock.getElapsedTime().asSeconds() > towerAttributes[0]) {
//		// use another layer of conditional to determine which direction is facing
//		// i.e. switch (direction) {case 'l': //sth; case 'r': //sth; ...}
//		// where "sth" is using the logic bellow to loop through its sprites
//
//	//	switch (direction) {
//	//	case 'u':
//	//		if (currentSprite == srcSprite[1][0]) {
//	//			currentSprite = srcSprite[1][1];
//	//			towerSprite.setTextureRect(currentSprite);
//	//		} else {
//	//			currentSprite = srcSprite[1][0];
//	//			towerSprite.setTextureRect(currentSprite);
//	//		} // end if else
//	//		break;
//	//	case 'd':
//	//		if (currentSprite == srcSprite[0][0]) {
//	//			currentSprite = srcSprite[0][1];
//	//			towerSprite.setTextureRect(currentSprite);
//	//		} else {
//	//			currentSprite = srcSprite[0][0];
//	//			towerSprite.setTextureRect(currentSprite);
//	//		} // end if else
//	//		break;
//	//	case 'l':
//	//		if (currentSprite == srcSprite[2][0]) {
//	//			currentSprite = srcSprite[2][1];
//	//			towerSprite.setTextureRect(currentSprite);
//	//			//towerSprite.setScale(-1.0,1.0);
//	//		} else {
//	//			currentSprite = srcSprite[2][0];
//	//			towerSprite.setTextureRect(currentSprite);
//	//			flipSprite();
//	//		} // end if else
//	//		break;
//	//	case 'r':
//	//		if (currentSprite == srcSprite[2][0]) {
//	//			currentSprite = srcSprite[2][1];
//	//			towerSprite.setTextureRect(currentSprite);
//	//			//towerSprite.setScale(1.0, 1.0);
//	//		} else {
//	//			currentSprite = srcSprite[2][0];
//	//			towerSprite.setTextureRect(currentSprite);
//	//			flipBack();
//	//		}
//	//		break;
//	//	} // end switch condition
//	//	//animationClock.restart();
//	////} // end switching figuresprite
//}
//
//void MagicTower::StopAttack() {
//	currentSprite = srcSprite[0][0];
//	towerSprite.setTextureRect(currentSprite);
//	mode = 'S';
//}
//
//void MagicTower::setMode(char AorS) {
//	mode = AorS;
//}
//
//char MagicTower::getMode() const {
//	return mode;
//}
//
//void MagicTower::setDirection(char UDLR) {
//	direction = UDLR;
//}
//
//char MagicTower::getDirection() const {
//	return direction;
//}
////
////void MagicTower::enemyDirection(sf::Vector2f enemyPos) {
////	float dx = towerPos.x - enemyPos.x;
////	float dy = towerPos.y - enemyPos.y;
////	if (dy > 0 && dy > dx && dx < -dy)
////		setDirection('u');
////	else if (dx < 0 && -dx > dy && dy >= dx)
////		setDirection('r');
////	else if (dy < 0 && dy < dx && -dy >= dx)
////		setDirection('d');
////	else
////		setDirection('l');
////}
//
//sf::Sprite MagicTower::getTowerSprite() const {
//	return towerSprite;
//}
//
//void MagicTower::flipSprite() {
//	towerSprite.setScale(-1.0, 1.0);
//	towerSprite.setPosition(coordinate[0] + 128, coordinate[1]);
//}
//
//void MagicTower::flipBack() {
//	towerSprite.setScale(1.0, 1.0);
//	towerSprite.setPosition(coordinate[0], coordinate[1]);
//}
//
//// new
//sf::Vector2f MagicTower::gettowerPosition() const {
//	return towerPos;
//}
//
//// new
//float MagicTower::getDamage() const {
//	return towerAttributes[2];
//}
//
//// new
//float MagicTower::enemyDistance(sf::Vector2f enemy) // returns distance between two points
//		{
//	float x = (towerPos.x - enemy.x) * (towerPos.x - enemy.x);
//	float y = (towerPos.y - enemy.y) * (towerPos.y - enemy.y);
//	float xPlusY = x + y;
//	return (float) (powf(xPlusY, 0.5)); //returns hypotenuse , ie. distance between points
//}
//
//// new
//bool MagicTower::enemyCollides(sf::Vector2f enemy) // simple collision detection between two circles
//		{
//	float dist = enemyDistance(enemy); // gets distance between circles
//	return dist < towerAttributes[1]; // if dist < tower range we have a collision
//}
//
//// new
//void MagicTower::upgrade() {
//
//}
