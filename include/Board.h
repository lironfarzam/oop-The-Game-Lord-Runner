#pragma once

#include <vector>
#include <memory>

#include "Levels.h"
#include "NonMovableObject.h"
#include "Wall.h"
#include "Coin.h"
#include "Gift.h"
#include "Ladder.h"
#include "Pole.h"

#include "constants.h"

#include <SFML/Graphics.hpp>

class MovableObject;

class Board {
public:
	Board(sf::RenderWindow*);

	// maps
	bool loadNextMap();
	void loadCurrentMap();
	int getCurrentLevel() const;
	void setCurrentLevel(int) ;

	// factory for loading maps
	void createObject(char type, float x, float y);

	void restartGame(); // initialize game

	// main operation after move  
	void updateGameObjects();

	// the game flow
	void handleCollisions(WorldObject& gameObject);
	void checkBoardState();

	// display game
	void drawMap(sf::RenderWindow& m_window);
	void printStats();

	// utils for game strategy
	void applyGravity(MovableObject* mov, sf::Time deltaTime) const;
	bool isObstacleBelow(MovableObject* movable) const;
	bool nothingBelow(MovableObject* movable) const;
	bool nothingBelow(MovableObject* movable, MovableObject::Direction dir) const;
	bool canGoUp(MovableObject* movable) const;
	bool canGoDown(MovableObject* movable) const;
	void digHole(MovableObject* movable, MovableObject::Direction dir);
	bool isCollision(MovableObject& movable) const;

	// the SFML window
	float getWindowHeight() const;
	float getWindowWidth() const;
	void resetWindowSize();

	// player - a pointer in m_movables
	Player* getPlayer() const;
	void setPlayerDirection(sf::Keyboard::Key key);

	// the game clock
	bool timeIsOver() const;
	void resetGameClock();
	int getGameClock();

	// used for bad gift
	void addEnemy();
	bool gameIsOver() const;
	void setGameOver(bool b);


private:
	// all maps of chars
	Levels m_levels;

	sf::Clock m_gameClock; // curent level time
	sf::Clock m_animClock; // for smooth animation

	// our main data structures (player is in m_unmovables)
	std::vector<std::unique_ptr<MovableObject>> m_movables;
	std::vector<std::unique_ptr<NonMovableObject>> m_unmovables;

	// build the movable/unmovable data structures from the game map
	void loadMapObjects();

	// the drawing window
	sf::RenderWindow * m_window;

	// a pointer to the player in un_movables
	Player* m_player = NULL;

	// utility functoin
	bool canGoDirection(MovableObject* movable, MovableObject::Direction dir) const;

	bool m_gameIsOver = false;
};
