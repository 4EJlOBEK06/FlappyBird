#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Assets.h"
#include "Sound_Assets.h"
#include "Player.h"
#include "Pipes.h"
#include "Surface.h"

class Menu {

	sf::RenderWindow& window;

    Assets& assets;
    Player player;
    Surface surface;
    Pipes pipes;

    sf::Sprite background;
    sf::Sprite message_flappybird;

	sf::Sprite button_start;
	sf::Sprite button_score;
	sf::Sprite button_settings;

    sf::Sound sound_push_button;

    float coord_y{};
    bool flag = true;

    float coefficient_x{};
    float coefficient_y{};

public:
	Menu(sf::RenderWindow& window, Assets& assets, Sound& sound);
    void set_coefficient(sf::RenderWindow& window);
	void update(float& time, unsigned int& Level);
    void update_message(float& time);

    bool delete_object{ false };
};


Menu::Menu(sf::RenderWindow& window, Assets& assets, Sound& sound)
	:window(window),
    assets(assets),
    player(assets, window.getSize()),
    surface(assets, window.getSize()),
    pipes(assets, window.getSize()) {

    set_coefficient(window);

    message_flappybird.setTexture(assets.tx_message_flappybird);
    message_flappybird.setScale(2 * coefficient_x, 2 * coefficient_y);
    message_flappybird.setPosition(window.getSize().x / 2 - message_flappybird.getGlobalBounds().getSize().x / 2, window.getSize().y / 5);

    background.setTexture(assets.tx_background_day);
    background.setScale(1 * coefficient_x, 1 * coefficient_y);

	button_start.setTexture(assets.tx_button_start);
	button_start.setScale(1.2 * coefficient_x, 1.2 * coefficient_y);
	button_start.setPosition(window.getSize().x / 2 - button_start.getGlobalBounds().getSize().x / 2 - button_start.getGlobalBounds().getSize().x / 1.9, (window.getSize().y / 2 - button_start.getGlobalBounds().getSize().y / 2));

	button_score.setTexture(assets.tx_button_score);
	button_score.setScale(1.2 * coefficient_x, 1.2 * coefficient_y);
	button_score.setPosition(window.getSize().x / 2 - button_score.getGlobalBounds().getSize().x / 2 + button_score.getGlobalBounds().getSize().x / 1.9, (window.getSize().y / 2 - button_score.getGlobalBounds().getSize().y / 2));
	
    button_settings.setTexture(assets.tx_button_settings);
	button_settings.setScale(1.2 * coefficient_x, 1.2 * coefficient_y);
	button_settings.setPosition(window.getSize().x / 2 - button_settings.getGlobalBounds().getSize().x / 2, (window.getSize().y / 2 + button_settings.getGlobalBounds().getSize().y / 2) + button_settings.getGlobalBounds().getSize().y / 10);

    sound_push_button.setBuffer(sound.buffer_push_button);
    sound_push_button.setVolume(sound.volume);
}

void Menu::set_coefficient(sf::RenderWindow& window) {
    
    coefficient_x = window.getSize().x / 1920.f;
    coefficient_y = window.getSize().y / 1080.f;
}

void Menu::update_message(float& time) {
    if (40 * coefficient_y / 2 > 0.03 * time * coefficient_y) {
        if (flag == true) {
            if (message_flappybird.getPosition().y < window.getSize().y / 5 + 40 * coefficient_y) {
                message_flappybird.move(0, 0.03 * time * coefficient_y);
            }
            else {
                flag = false;
            }
        }
        else {
            if (message_flappybird.getPosition().y > window.getSize().y / 5) {
                message_flappybird.move(0, -(0.03 * time * coefficient_y));
            }
            else {
                flag = true;
            }
        }
    }
}

void Menu::update(float& time, unsigned int& Level) {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (button_start.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                sound_push_button.play();
                delete_object = true;
                ++Level;
            }
            else if (button_score.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                sound_push_button.play();
                delete_object = true;
                Level += 2;
            }
            else if (button_settings.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                sound_push_button.play();
                delete_object = true;
                Level += 3;
            }
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            window.close();
        }
    }
    surface.coord_x = -3 * coefficient_x;
    player.update(time, false);
    surface.update(time, true);
    update_message(time);
    window.draw(background);
    for (size_t i = 0; i < sizeof(pipes.sprites) / sizeof(pipes.sprites[0]); ++i) {
        window.draw(pipes.sprites[i]);
    }
    for (size_t i = 0; i < sizeof(surface.sprite) / sizeof(surface.sprite[0]); ++i) {
        window.draw(surface.sprite[i]);
    }
    window.draw(player.sprite);
    window.draw(button_start);
    window.draw(button_score);
    window.draw(button_settings);
    window.draw(message_flappybird);
    
    /*window.display();*/
}