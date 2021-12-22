#include "Resources.h"
#include <iostream>

const int NUM_IMAGES = 11;
const char* game_images[NUM_IMAGES] = { "wall.png", "player.png", "enemy.png", "ladder.png", 
                                        "pole.png", "coin.png" , "gift.png", "runner.png", 
                                        "guard.png", "cover.png", "cover_help.png" };

const int NUM_SOUNDS = 14;
const char* sounds[] = {"beep.ogg", "born.ogg", "dead.ogg", "dig.ogg", "down.ogg", "ending.ogg", "fall.ogg",
                        "getGold.ogg", "goldFinish.ogg", "pass.ogg", "scoreBell.ogg", "scoreCount.ogg", 
                        "scoreEnding.ogg", "trap.ogg" };


/*
*  A SINGLETON class to load game images, sound and font
*/


Resources::~Resources()
{
    all_textures.clear();
    m_soundsBuffer.clear();
    m_sounds.clear();
}

Resources& Resources::instance()
{
    static Resources inst;
    return inst;
}


sf::Texture& Resources::getImage(int i)
{
    return all_textures[i];
}


void Resources::playSound(int type)
{
    m_sounds[type].setVolume(100.f);
    m_sounds[type].setLoop(false);
    m_sounds[type].play();
}

sf::Font& Resources::getFont()
{
    return m_gameFont;
}

Resources::Resources()
{
    srand((unsigned int)time(NULL));

    all_textures.resize(NUM_IMAGES);

    for (int i = 0; i < NUM_IMAGES; i++) {
        if (!all_textures[i].loadFromFile(game_images[i])) //, sf::IntRect(0, 0, ShapeWidth, ShapeHeight)))
            std::cout << "failed to load image file:" << game_images[i] << std::endl;
    }

    // load font
    if (!m_gameFont.loadFromFile("SHOWG.TTF"))
    {
        std::cout << "Cannot load font!! " << std::endl;
    }


    // load sound.
    m_soundsBuffer.resize(NUM_SOUNDS);
    m_sounds.resize(NUM_SOUNDS);
    for (int i = 0; i < NUM_SOUNDS; i++) {
        if (!m_soundsBuffer[i].loadFromFile(sounds[i])) {
            std::cout << "failed to load sound file:" << sounds[i] << std::endl;
        }
        else
            m_sounds[i].setBuffer(m_soundsBuffer[i]);
    }

}

int Resources::randomNumber(int max)
{
    return rand() % max;
}

