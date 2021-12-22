#pragma once

#include "Enemy.h"

class EnemyRandom : public Enemy {

public:
	EnemyRandom(float x, float y);
	virtual void move(sf::Time deltaTime) override;

private:
	int m_steps;
};


