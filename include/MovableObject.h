#pragma once


#include "WorldObject.h"

class Board;
class MovableObject : public WorldObject {

public:

    enum class Direction
    {
        Stay,
        Up,
        Down,
        Left,
        Right,
        DigLeft,
        DigRight
    };

    enum class State
    {
        onLadder,
        onPole,
        onGround,
        isFalling,
        inHole,

    };

    MovableObject(float x, float y);

    virtual void move(sf::Time deltaTime);

    void setDirection(sf::Keyboard::Key key);
    void setDirection(MovableObject::Direction dir);
    Direction getDirection();

    void setWindowHeight(float);
    void setWindowWidth(float);

    bool limitBounds();
    void mirorDir();

    void setState(State);
    State getState();
    void setBoard(Board* board);
    Board* getBoard() const;

    virtual float getSpeed() const;
    virtual void setSpeed(float);

    bool m_isFalling = false;

protected:
    Direction m_dir = Direction::Stay;
    State m_state;

    float m_window_height = 0;
    float m_window_width = 0;

    sf::Clock m_clock; // for PNG animated
    sf::IntRect m_rectSourceSprite; // image start position for animation in PNG


    Board* m_boardGame;

private:
    float m_speed = ShapeWidth * 3;

};

