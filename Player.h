#pragma once
#include <SFML/Graphics.hpp>
#include "Assets.h"

class Player {
	sf::Texture tx_bird_down;
	sf::Texture tx_bird_mid;
	sf::Texture tx_bird_up;

	sf::FloatRect rect;
	float current_frame{};
	float rotate{};
	float coefficient_x{};
	float coefficient_y{};

public:
	Player(Assets& assets, sf::Vector2u window_size);
	void update(float time, bool play, bool pause = false);

	sf::Sprite sprite;

	float coord_y{};
	bool on_surface{ false };
};



Player::Player(Assets& assets, sf::Vector2u window_size){

	coefficient_x = static_cast<float>(window_size.x) / 1920.f;
	coefficient_y = static_cast<float>(window_size.y) / 1080.f;

	tx_bird_down = assets.tx_bird_down;
	tx_bird_mid = assets.tx_bird_mid;
	tx_bird_up = assets.tx_bird_up;

	sprite.setTexture(tx_bird_down);
	sprite.setScale(2.5 * coefficient_x, 2.5 * coefficient_y);
	sprite.setOrigin(tx_bird_mid.getSize().x / 2, tx_bird_mid.getSize().y / 2);

	rect.left = window_size.x/6;
	rect.top = window_size.y/2;
}

void Player::update(float time, bool play, bool pause) {
	if (!pause) {
		if (play) {
			coord_y += 0.005 * time * coefficient_y;
		}
		if (on_surface && coord_y > 0) {
			coord_y = 0;
		}
		if (rect.top <= 0 + sprite.getGlobalBounds().height / 3 && coord_y < 0) {
			coord_y = 0;
		}
		rect.top += coord_y * time / 20;

		sprite.setRotation(coord_y * 5 / coefficient_y);
	}

	current_frame += 0.006 * time;
	if (current_frame > 8) { current_frame = 0; }
	if (current_frame < 3) { sprite.setTexture(tx_bird_down); }
		else if (current_frame >= 3 && current_frame <= 5) { sprite.setTexture(tx_bird_mid); }
			else if (current_frame > 5) { sprite.setTexture(tx_bird_up); }
	if (!play && !pause) {
		sprite.setPosition(rect.left, rect.top + current_frame * coefficient_y);
	}
	else {
		sprite.setPosition(rect.left, rect.top);
	}
}


