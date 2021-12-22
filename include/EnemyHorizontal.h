#pragma once

#include "Enemy.h"


class EnemyHorizontal : public Enemy {

public:
	EnemyHorizontal(float x, float y);
	virtual void move(sf::Time deltaTime) override;

	//void handleCollision(Wall& obj);

};


