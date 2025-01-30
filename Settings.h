#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Assets.h"
#include "Sound_Assets.h"


class Settings {

	sf::RenderWindow& window;

	Assets& assets;
    Sound& sound;

    bool& fullscreen;
    bool& vertical_sync;

	sf::Sprite background;
    sf::Sprite settings_banner;
    sf::Sprite check_box_fullscreen;
    sf::Sprite check_box_vertical_sync;
    sf::Sprite volume_slider;
    sf::Sprite volume_control;
    sf::Sprite button_ok;

    sf::Text text_screen_resolution;
    sf::Text text_volume_level;

    sf::Sound sound_push_button;

	float coefficient_x{};
	float coefficient_y{};
    
    bool isDragging{ false };

    void ñreate_new_window();

public:
	Settings(sf::RenderWindow& window, Assets& assets, Sound& sound, bool& fullscreen, bool& vertical_sync);
	void set_coefficient(sf::RenderWindow& window);
    void update(unsigned int& Level);

    bool delete_object{ false };
};

Settings::Settings(sf::RenderWindow& window, Assets& assets, Sound& sound, bool& fullscreen, bool& vertical_sync)
	:window(window),
	assets(assets),
    sound(sound),
    fullscreen(fullscreen),
    vertical_sync(vertical_sync){

	set_coefficient(window);

	background.setTexture(assets.tx_background_night);
	background.setScale(1 * coefficient_x, 1 * coefficient_y);

    settings_banner.setTexture(assets.tx_settings_banner);
    settings_banner.setScale(1 * coefficient_x, 1 * coefficient_y);
    settings_banner.setPosition(window.getSize().x / 2 - settings_banner.getGlobalBounds().width / 2, window.getSize().y / 2 - settings_banner.getGlobalBounds().height / 2);

    if (fullscreen) {
        check_box_fullscreen.setTexture(assets.tx_check_box_true);
    } 
    else {
        check_box_fullscreen.setTexture(assets.tx_check_box_false);
    }
    check_box_fullscreen.setScale(1 * coefficient_x, 1 * coefficient_y);
    check_box_fullscreen.setPosition(settings_banner.getPosition().x + settings_banner.getGlobalBounds().width - check_box_fullscreen.getGlobalBounds().width - (check_box_fullscreen.getGlobalBounds().width / 2 * 3), settings_banner.getPosition().y + check_box_fullscreen.getGlobalBounds().height * 6.25);

    if (vertical_sync) {
        check_box_vertical_sync.setTexture(assets.tx_check_box_true);
    }
    else {
        check_box_vertical_sync.setTexture(assets.tx_check_box_false);
    }
    check_box_vertical_sync.setScale(1 * coefficient_x, 1 * coefficient_y);
    check_box_vertical_sync.setPosition(check_box_fullscreen.getPosition().x, check_box_fullscreen.getPosition().y + check_box_vertical_sync.getGlobalBounds().height * 3.3);

    volume_slider.setTexture(assets.tx_volume_slider);
    volume_slider.setScale(1 * coefficient_x, 1 * coefficient_y);
    volume_slider.setPosition(settings_banner.getPosition().x + settings_banner.getGlobalBounds().width - volume_slider.getGlobalBounds().width - volume_slider.getGlobalBounds().width / 11, settings_banner.getPosition().y + settings_banner.getGlobalBounds().height - volume_slider.getGlobalBounds().height * 6.7);

    volume_control.setTexture(assets.tx_bird_mid);
    volume_control.setScale(2 * coefficient_x, 2 * coefficient_y);
    volume_control.setOrigin(volume_control.getLocalBounds().width / 2, volume_control.getLocalBounds().height / 2);
    volume_control.setPosition(volume_slider.getPosition().x + volume_slider.getGlobalBounds().width * (sound.volume / 100), volume_slider.getPosition().y + volume_slider.getGlobalBounds().height / 2);

    button_ok.setTexture(assets.tx_button_ok);
    button_ok.setScale(2 * coefficient_x, 2 * coefficient_y);
    button_ok.setPosition(window.getSize().x / 2 - button_ok.getGlobalBounds().width / 2, settings_banner.getGlobalBounds().getPosition().y + settings_banner.getGlobalBounds().height + button_ok.getGlobalBounds().height / 10);

    text_screen_resolution.setFont(assets.font_numbers);
    text_screen_resolution.setString(std::to_string(window.getSize().x) + "x" + std::to_string(window.getSize().y));
    text_screen_resolution.setCharacterSize(text_screen_resolution.getCharacterSize() * coefficient_y);
    text_screen_resolution.setPosition(settings_banner.getPosition().x + text_screen_resolution.getGlobalBounds().width * 1.5, settings_banner.getPosition().y + text_screen_resolution.getGlobalBounds().height * 4.2);

    text_volume_level.setFont(assets.font_numbers);
    text_volume_level.setString(std::to_string(static_cast<int>(sound.volume)));
    text_volume_level.setCharacterSize(text_volume_level.getCharacterSize() * coefficient_y);
    text_volume_level.setPosition(volume_slider.getPosition().x + volume_slider.getGlobalBounds().width / 2 - text_volume_level.getGlobalBounds().width / 2, volume_slider.getPosition().y + volume_slider.getGlobalBounds().height + text_volume_level.getGlobalBounds().height / 2);

    sound_push_button.setBuffer(sound.buffer_push_button);
    sound_push_button.setVolume(sound.volume);
}

void Settings::set_coefficient(sf::RenderWindow& window) {
	coefficient_x = window.getSize().x / 1920.f;
	coefficient_y = window.getSize().y / 1080.f;
}

void Settings::ñreate_new_window() {
    if (fullscreen) {
        window.create(sf::VideoMode::getDesktopMode(), "Flappy bird", sf::Style::Fullscreen);
        window.setVerticalSyncEnabled(vertical_sync);
    }
    else {
        window.create(sf::VideoMode::getDesktopMode(), "Flappy bird", sf::Style::Close);
        window.setVerticalSyncEnabled(vertical_sync);
    }
}

void Settings::update(unsigned int& Level) {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (check_box_fullscreen.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                if (fullscreen) {
                    fullscreen = false;
                    check_box_fullscreen.setTexture(assets.tx_check_box_false);
                }
                else {
                    fullscreen = true;
                    check_box_fullscreen.setTexture(assets.tx_check_box_true);
                }
            }
            else if (check_box_vertical_sync.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                if (vertical_sync) {
                    vertical_sync = false;
                    check_box_vertical_sync.setTexture(assets.tx_check_box_false);
                }
                else {
                    vertical_sync = true;
                    check_box_vertical_sync.setTexture(assets.tx_check_box_true);
                }
            }
            else if (volume_control.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                isDragging = true;
            }
            else if (button_ok.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                sound_push_button.play();
                delete_object = true;
                Level -= 3;
                ñreate_new_window();
            }
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            isDragging = false;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            sound_push_button.play();
            delete_object = true;
            Level -= 3;
            ñreate_new_window();
        }
    }

    if (isDragging && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (mousePos.x > volume_slider.getPosition().x && mousePos.x < volume_slider.getPosition().x + volume_slider.getGlobalBounds().width) {
            volume_control.setPosition(mousePos.x, volume_control.getPosition().y);
            sound.volume = (volume_control.getPosition().x - volume_slider.getPosition().x) / volume_slider.getGlobalBounds().width * 100;
            text_volume_level.setString(std::to_string(static_cast<int>(sound.volume)));
        }
    }

    window.draw(background);
    window.draw(settings_banner);
    window.draw(check_box_fullscreen);
    window.draw(check_box_vertical_sync);
    window.draw(volume_slider);
    window.draw(volume_control);
    window.draw(button_ok);
    window.draw(text_screen_resolution);
    window.draw(text_volume_level);
    
}