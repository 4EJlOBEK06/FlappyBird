#pragma once
#include <SFML/Graphics.hpp>
#include "Assets.h"


class Message_get_ready {
	float time{};
	float coefficient_x{};
	float coefficient_y{};

public:
	Message_get_ready(Assets& assets, sf::Vector2u window_size);
	void update(float time);

	sf::Sprite sprite;
	bool visible{ true };
};


Message_get_ready::Message_get_ready(Assets& assets, sf::Vector2u window_size) {
	coefficient_x = static_cast<float>(window_size.x) / 1920.f;
	coefficient_y = static_cast<float>(window_size.y) / 1080.f;
	sprite.setTexture(assets.tx_message_get_ready);
	sprite.setScale(2.5 * coefficient_x, 2.5 * coefficient_y);
	sprite.setPosition(window_size.x / 2.6, window_size.y / 3.5);
}


void Message_get_ready::update(float time) {
	this->time += 0.0015 * time;
	if (this->time < 2) { visible = true; }
	else if (this->time > 4) { this->time = 0; }
	else { visible = false; }
}