#include "EnemyHorizontal.h"
#include "Board.h"

EnemyHorizontal::EnemyHorizontal(float x, float y): Enemy(x,y)
{
	m_dir = Direction::Right;
}

void EnemyHorizontal::move(sf::Time deltaTime)
{
	if (getBoard() == NULL)
		return;

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

//void EnemyHorizontal::handleCollision(Wall& obj)
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

