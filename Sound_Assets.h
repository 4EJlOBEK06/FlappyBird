#pragma once
#include <SFML/Audio.hpp>

class Sound {
public:

	float volume{ 100 };

	sf::SoundBuffer buffer_jump;
	sf::SoundBuffer buffer_hit;
	sf::SoundBuffer buffer_point;
	sf::SoundBuffer buffer_push_button;
	Sound();
};

Sound::Sound() {
	buffer_jump.loadFromFile("audio/wing.wav");
	buffer_hit.loadFromFile("audio/hit.wav");
	buffer_point.loadFromFile("audio/point.wav");
	buffer_push_button.loadFromFile("audio/swoosh.wav");
}