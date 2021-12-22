
#include "Enemy.h"
#include "Player.h"
#include "Board.h"



Enemy::Enemy(float x, float y) : MovableObject(x, y)
{
    m_sprite = sf::Sprite(Resources::instance().getImage(GUARD_IMG));
    m_sprite.setTextureRect(m_rectSourceSprite);
	m_sprite.setPosition(x, y);
}

void Enemy::draw(sf::RenderWindow& window)
{
    sf::IntRect r = m_sprite.getTextureRect();

    if (m_dir == Direction::Left)
        m_rectSourceSprite.left = (int) ShapeWidth * 2;
    else
        m_rectSourceSprite.left = 0;

    if (m_rectSourceSprite.left > r.left || (m_rectSourceSprite.left + m_rectSourceSprite.width) < r.left)
        r.left = m_rectSourceSprite.left;

    // rotate on 3 images in PNG file
    if (m_clock.getElapsedTime().asSeconds() > ANIMATION_SPEED) 
    {
        if (r.left >= m_rectSourceSprite.left + (ShapeWidth * 2))
            r.left = m_rectSourceSprite.left;
        else
            r.left += (int) ShapeWidth;

        m_sprite.setTextureRect(r);
        m_clock.restart();
    }
    MovableObject::draw(window);
}

void Enemy::handleCollision(WorldObject& obj)
{
	if (&obj == this) return;
	//double dispatch
	obj.handleCollision(*this);
}


void Enemy::handleCollision(Wall& obj)
{
    switch (m_dir) {
    case Direction::Left:
        m_x = obj.getX() + ShapeWidth;
        m_dir = Direction::Right;
        break;
    case Direction::Right:
        m_x = obj.getX() - ShapeWidth;
        m_dir = Direction::Left;
        break;
    case Direction::Down:
    case Direction::Up:
    default:
        return;
    }
}

void Enemy::handleCollision(Enemy& )
{
}

void Enemy::handleCollision(Player& obj)
{
	obj.handleCollision(*this);
}

void Enemy::handleCollision(Ladder& )
{
}

void Enemy::handleCollision(Coin& )
{
}

void Enemy::handleCollision(Gift& )
{
}

void Enemy::handleCollision(Pole& )
{
}

void Enemy::handleCollision(GiftAddEnemy& )
{
}

void Enemy::handleCollision(GiftAddLive& )
{
}

void Enemy::handleCollision(GiftAddBonus& )
{
}

void Enemy::handleCollision(GiftAddTime& )
{
}
