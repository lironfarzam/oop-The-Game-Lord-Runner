#include "EnemyRandom.h"
#include "Board.h"

EnemyRandom::EnemyRandom(float x, float y):Enemy(x, y)
{
	m_steps = 50;
}

void EnemyRandom::move(sf::Time deltaTime)
{
	if (getBoard() == NULL)
		return;

	m_steps--;

	if (m_steps == 0) {
		m_steps = 500;
		int dir = rand() % 10;
		if (dir < 5)
			m_dir = Direction::Left;
		else
			m_dir = Direction::Right;
	}

	// check if we have floor
	switch (m_dir) {
	case Direction::Left:
		if (getBoard()->nothingBelow(this, Direction::Left))
			m_dir = Direction::Right;
		break;
	case Direction::Right:
		if (getBoard()->nothingBelow(this, Direction::Right))
			m_dir = Direction::Left;
		break;
	case Direction::Down:
	case Direction::Up:
	default:
		return;
	}

	MovableObject::move(deltaTime);
}

//void EnemyRandom::handleCollision(Wall& obj)
//{
//	switch (m_dir) {
//	case Direction::Left:
//		m_x = obj.getX() + ShapeWidth;
//		m_dir = Direction::Right;
//		break;
//	case Direction::Right:
//		m_x = obj.getX() - ShapeWidth;
//		m_dir = Direction::Left;
//		break;
//	case Direction::Down:
//	case Direction::Up:
//	default:
//		return;
//	}
//}