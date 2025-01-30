#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include <cstdlib>
#include "Assets.h"

const unsigned int COUNT = 4;

class Pipes {
	sf::Vector2u window_size;

	float coefficient_x{};
	float coefficient_y{};

public:
	Pipes(Assets& assets, sf::Vector2u window_size);

	void update(float time, bool& play);
	void new_coordinates_y(size_t& i);

	sf::Sprite sprites[COUNT];
	sf::FloatRect rect[sizeof(sprites) / sizeof(sprites[0])];

	float coord_x{};
	float coord_y{};
};


Pipes::Pipes(Assets& assets, sf::Vector2u window_size) {

	srand(static_cast<unsigned>(time(0)));
	this->window_size = window_size;
	coefficient_x = static_cast<float>(window_size.x) / 1920.f;
	coefficient_y = static_cast<float>(window_size.y) / 1080.f;

	for (size_t i = 0; i < sizeof(sprites) / sizeof(sprites[0]); ++i) {
		sprites[i].setTexture(assets.tx_pipe);
		if (i % 2 == 0) {
			sprites[i].setScale(3.5 * coefficient_x, -3.5 * coefficient_y);
			new_coordinates_y(i);
			rect[i].left = window_size.x + sprites[i].getGlobalBounds().width + (window_size.x + sprites[i].getGlobalBounds().width) / 4 * i ;
		}
		else {
			sprites[i].setScale(3.5 * coefficient_x, 3.5 * coefficient_y);
			rect[i].left = rect[i - 1].left;
			rect[i].top = rect[i - 1].top + 300.f * coefficient_y;
		}
		sprites[i].setPosition(rect[i].left, rect[i].top);
	}
}


void Pipes::update(float time, bool& play) {

	if (play) {
		for (size_t i = 0; i < sizeof(sprites) / sizeof(sprites[0]); ++i) {
			rect[i].left += coord_x * time / 15;
			if (rect[i].left <= -sprites[i].getGlobalBounds().width) {
				rect[i].left += window_size.x + sprites[i].getGlobalBounds().width;
				new_coordinates_y(i);
			}
			if (i % 2 == 0) {
				sprites[i].setPosition(rect[i].left, rect[i].top);
			}
			else {
				sprites[i].setPosition(rect[i].left, rect[i - 1].top + 300.f * coefficient_y);
			}
		}
	}
}


void Pipes::new_coordinates_y(size_t& i) {
	coord_y = (rand() % 800) * coefficient_y;
	rect[i].top = coord_y;
}