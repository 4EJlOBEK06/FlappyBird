#pragma once
#include <SFML/Graphics.hpp>
#include "Assets.h"

class Surface {
	sf::Vector2u window_size;

	float coefficient_x{};
	float coefficient_y{};

public:
	Surface(Assets& assets, sf::Vector2u window_size);
	void update(float time, bool play);

	sf::Sprite sprite[2];
	float coord_x{};
};

Surface::Surface(Assets& assets, sf::Vector2u window_size) {
	this->window_size = window_size;
	coefficient_x = static_cast<float>(window_size.x) / 1920.f;
	coefficient_y = static_cast<float>(window_size.y) / 1080.f;
	for (size_t i = 0; i < sizeof(sprite) / sizeof(sprite[0]); ++i) {
		sprite[i].setTexture(assets.tx_surface);
		sprite[i].scale(1 * coefficient_x, 0.5 * coefficient_y);
		sprite[i].setPosition(window_size.x * i, window_size.y - window_size.y / 9);
	}
}


void Surface::update(float time, bool play) {
	if (play) {
		coord_x = coord_x * time / 15;
	}
	for (size_t i = 0; i < sizeof(sprite) / sizeof(sprite[0]); ++i) {
		if (sprite[i].getPosition().x < static_cast<int>(window_size.x) * -1) {
			sprite[i].setPosition(sprite[i].getPosition().x + window_size.x * 2, sprite[i].getPosition().y);
		}
		sprite[i].setPosition(sprite[i].getPosition().x + coord_x, sprite[i].getPosition().y);
	}
}