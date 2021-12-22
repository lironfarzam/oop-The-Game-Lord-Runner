#pragma once
#include "constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


// a singleton of all textures/sound/fonts

class Resources {
public:
	~Resources();
	static Resources& instance();

	static int randomNumber(int max);

	sf::Texture& getImage(int index) ;
	sf::Font& getFont() ;

	void playSound(int type);

private:
	Resources();
	Resources(const Resources&) = default;
	Resources& operator=(const Resources&) = default;

	std::vector<sf::Texture> all_textures;
	std::vector<sf::SoundBuffer> m_soundsBuffer;
	std::vector<sf::Sound> m_sounds;

	sf::Font m_gameFont;

};
