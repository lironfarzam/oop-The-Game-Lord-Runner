
#include "Player.h"
#include "Board.h"

#include <iostream>


Player::Player(float x, float y):  MovableObject(x, y)
{
    m_sprite_default.setTexture(Resources::instance().getImage(PLAYER_IMG));
    m_sprite_default.setPosition(x, y);

    m_sprite.setTexture(Resources::instance().getImage(RUNNER_IMG));
    m_sprite.setTextureRect(m_rectSourceSprite);
	m_sprite.setPosition(x, y);

    setSpeed(ShapeWidth *4);
    m_isdead = false;
}


void Player::draw(sf::RenderWindow& window) 
{
    sf::IntRect r = m_sprite.getTextureRect();
    m_rectSourceSprite.top = 0;
    m_rectSourceSprite.left = 0;

    if (m_dir == Direction::Stay) {
        m_sprite_default.setPosition(m_x, m_y);
        window.draw(m_sprite_default);
        return;
    }

    if (m_dir == Direction::Left)
        m_rectSourceSprite.left = (int) ShapeWidth * 2;
    else
    if (m_dir == Direction::Right) 
        m_rectSourceSprite.left = 0;
    else
        if (getState() == State::onLadder) {
            m_rectSourceSprite.left = (int) ShapeWidth * 5;
        }

    // check if we changed state/position, reset the starting image
    if (m_rectSourceSprite.left > r.left || (m_rectSourceSprite.left + m_rectSourceSprite.width) < r.left
        || r.top < m_rectSourceSprite.top || r.top >(m_rectSourceSprite.top + ShapeHeight))
    {
        r.left = m_rectSourceSprite.left;
        r.top = m_rectSourceSprite.top;
    }

    // rotate on 3 images in PNG file
    if (m_clock.getElapsedTime().asSeconds() > ANIMATION_SPEED) {

        if ( r.left >= m_rectSourceSprite.left + (ShapeWidth * 2))
            r.left  = (int) m_rectSourceSprite.left;
        else
            r.left += (int) ShapeWidth;

        m_sprite.setTextureRect(r);
        m_clock.restart();
    } 
    MovableObject::draw(window);
}

void Player::move(sf::Time deltaTime)
{
    if (m_dir == Direction::DigLeft) {
        m_boardGame->digHole(this, MovableObject::Direction::Left);
        setDirection(MovableObject::Direction::Stay);
    } 
    else 
    if (m_dir == Direction::DigRight) {
        m_boardGame->digHole(this, MovableObject::Direction::Right);
        setDirection(MovableObject::Direction::Stay);
    } 
    else
        MovableObject::move(deltaTime);
}

void Player::handleCollision(WorldObject& obj)
{
    if (&obj == this) return;
    //double dispatch
    obj.handleCollision(*this);
}

void Player::handleCollision(Wall& obj)
{
    // collision with hole
    if (m_x == obj.getX() && m_y == obj.getY())
    {
        // we are in hole - go up
        m_y = m_y - ShapeHeight;
    }

    else {
        if (m_dir == Direction::Up)
        {
            m_y = obj.getY() + ShapeHeight;
        }
        else if (m_dir == Direction::Down)
        {
            m_y = obj.getY() - ShapeHeight;
            setState(MovableObject::State::onGround);
        }
        else if (m_dir == Direction::Left)
        {
            m_x = obj.getX() + ShapeWidth;
        }
        else if (m_dir == Direction::Right)
        {
            m_x = obj.getX() - ShapeWidth;
        }
    }
    m_sprite.setPosition(m_x, m_y);

    m_dir = Direction::Stay; // could be falling???
}

void Player::handleCollision(Enemy& )
{
    Resources::instance().playSound(DEAD_SOUND);

    //std::cout << "Player::handleCollision(Enemy& obj)" << std::endl;
    decreaseLives();
    m_isdead = true;
}

void Player::handleCollision(Player& )
{
}

void Player::handleCollision(Ladder& obj)
{

    // Pole collision has priority
    if (m_state == State::onPole && (m_x - obj.getX() > ShapeWidth / 2 || obj.getX() - m_x > ShapeWidth / 2)) {
        return;
    }

    m_state = State::onLadder;

    // TEST - ON LADDER ONLY WHEN UP/DOWN
    if (m_dir == Direction::Down || m_dir == Direction::Up) {
        m_x = obj.getX(); // align when climbing
    }

    float dy = obj.getY() - m_y ;

    // standing on top of ladder
    if ((m_dir == Direction::Up && !m_boardGame->canGoUp(this))) {

        if (dy >= (ShapeHeight - 3.0f) && dy <= (ShapeHeight + 3.0f)) {
            m_y = obj.getY() - ShapeHeight;
            m_state = State::onGround;
            m_dir = m_dir = Direction::Stay;
            //std::cout << "\\\ on top of ladder ///" << std::endl;
        }
    }

    m_sprite.setPosition(m_x, m_y);

}

void Player::handleCollision(Coin& )
{
    Resources::instance().playSound(GET_GOLD_SOUND);
    setScore(m_score + 2 * (m_boardGame->getCurrentLevel() + 1));
}

void Player::handleCollision(Gift& )
{

}

void Player::handleCollision(Pole& obj)
{

    //float dx = m_x - obj.getX();

    if (m_dir == Direction::Left || m_dir == Direction::Right) {
        m_y = obj.getY();

        m_sprite.setPosition(m_x, m_y);
        m_state = State::onPole; // TEST
        return;
    }

    float dy = m_y - obj.getY();
    if (dy <= 0 && dy > -1.f) {  // landing on a pole

        if (m_y != obj.getY())
            Resources::instance().playSound(DOWN_SOUND);

        m_y = obj.getY(); // align

        m_dir = Direction::Stay;
        setState(MovableObject::State::onPole);

    } 
    else if (dy >= 0) {
        if (m_dir == Direction::Down) { // jump off -> down

            m_y = obj.getY() + ShapeHeight;

            setState(MovableObject::State::onPole);
            m_isFalling = true;
            Resources::instance().playSound(FALL_SOUND);
        }
    }

    m_sprite.setPosition(m_x, m_y);
}

void Player::handleCollision(GiftAddEnemy& )
{
    Resources::instance().playSound(GET_GOLD_SOUND);
    m_boardGame->addEnemy();
}

void Player::handleCollision(GiftAddLive& )
{
    Resources::instance().playSound(GET_GOLD_SOUND);
    setLives(getLives() + BONUS_TO_LIVES);
}

void Player::handleCollision(GiftAddBonus& )
{
    Resources::instance().playSound(GET_GOLD_SOUND);
    setScore(getScore() + BONUS_TO_SCORE);
}

void Player::handleCollision(GiftAddTime& )
{
    Resources::instance().playSound(GET_GOLD_SOUND);
    m_boardGame->resetGameClock();
}

int Player::getLives() const
{
    return m_lives;
}

int Player::getScore() const
{
    return m_score;
}

void Player::decreaseLives()
{
    if (m_isdead)
        return;
    m_lives = m_lives - 1;
    m_isdead = true;
}

void Player::setScore(int s)
{
    m_score = s;
}

void Player::setLives(int lives)
{
    m_lives = lives;
}

bool Player::getIsDead()
{
    return m_isdead;
}

void Player::setIsDead(bool dead) {
    m_isdead = dead;
}




