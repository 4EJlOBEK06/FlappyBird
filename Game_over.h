#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Assets.h"
#include "Reading_writing_file.h"

class Game_over {

    sf::Texture tx_message_game_over;
    sf::Texture tx_banner_empty;
    sf::Texture tx_banner_with_bronze_medal;
    sf::Texture tx_banner_with_silver_medal;
    sf::Texture tx_banner_with_gold_medal;
    sf::Texture tx_banner_with_platinum_medal;
    sf::Texture tx_button_ok;

    sf::Vector2u window_size;

    sf::Color color;

    Reading_writing reading_writing{};

    float coefficient_x{};
    float coefficient_y{};
    float accumulation_alpha{};

public:
    Game_over(Assets& assets, sf::Vector2u window_size);
    void draw(sf::RenderWindow& window);
    void update(float& time);
    void set_banner(unsigned int& score);

    sf::Sprite message_game_over;
    sf::Sprite banner_game_over;
    sf::Text score{};
    sf::Text best_score{};
    sf::Sprite button_ok;
};

Game_over::Game_over(Assets& assets, sf::Vector2u window_size) {

    this->window_size = window_size;

    coefficient_x = static_cast<float>(window_size.x) / 1920.f;
    coefficient_y = static_cast<float>(window_size.y) / 1080.f;

    tx_message_game_over = assets.tx_message_game_over;
    tx_banner_empty = assets.tx_banner_empty;
    tx_banner_with_bronze_medal = assets.tx_banner_with_bronze_medal;
    tx_banner_with_silver_medal = assets.tx_banner_with_silver_medal;
    tx_banner_with_gold_medal = assets.tx_banner_with_gold_medal;
    tx_banner_with_platinum_medal = assets.tx_banner_with_platinum_medal;
    tx_button_ok = assets.tx_button_ok;

    message_game_over.setTexture(tx_message_game_over);
    message_game_over.setScale(3 * coefficient_x, 3 * coefficient_y);
    message_game_over.setPosition(window_size.x / 2 - message_game_over.getGlobalBounds().width / 2, window_size.y / 2 - window_size.y / 3);

    banner_game_over.setTexture(tx_banner_empty);
    banner_game_over.setScale(2 * coefficient_x, 2 * coefficient_y);
    banner_game_over.setPosition(window_size.x / 2 - banner_game_over.getGlobalBounds().width / 2, window_size.y);

    button_ok.setTexture(tx_button_ok);
    button_ok.setScale(2 * coefficient_x, 2 * coefficient_y);
    button_ok.setPosition(window_size.x / 2 - button_ok.getGlobalBounds().width / 2, window_size.y);

    score.setFont(assets.font_numbers);
    score.setPosition(banner_game_over.getGlobalBounds().width, banner_game_over.getGlobalBounds().height / 2);
    score.setCharacterSize(64 * coefficient_y);

    best_score.setFont(assets.font_numbers);
    best_score.setPosition(banner_game_over.getGlobalBounds().width / 2, banner_game_over.getGlobalBounds().height / 2);
    best_score.setCharacterSize(64 * coefficient_y);

    color = message_game_over.getColor();
    color.a = 0;
}

void Game_over::update(float& time) {

    if (color.a < 255) {
        accumulation_alpha += time * 0.2;
        if (accumulation_alpha > 255) {
            color.a = 255;
            message_game_over.setColor(color);
        } else {
            color.a = accumulation_alpha;
            message_game_over.setColor(color);
        }
    }

    if (banner_game_over.getPosition().y > window_size.y / 2 - banner_game_over.getGlobalBounds().height / 2) {
        if (banner_game_over.getPosition().y - time * 0.5 < window_size.y / 2 - banner_game_over.getGlobalBounds().height / 2) {
            banner_game_over.setPosition(banner_game_over.getPosition().x, window_size.y / 2 - banner_game_over.getGlobalBounds().height / 2);
        } else {
            banner_game_over.setPosition(banner_game_over.getPosition().x, banner_game_over.getPosition().y - time * 0.5);
        }
    } else {
        button_ok.setPosition(button_ok.getPosition().x, window_size.y / 2 + window_size.y / 5);
    }
    score.setPosition(banner_game_over.getPosition().x + banner_game_over.getGlobalBounds().width / 10 * 9, banner_game_over.getPosition().y + banner_game_over.getGlobalBounds().height / 4);
    best_score.setPosition(banner_game_over.getPosition().x + banner_game_over.getGlobalBounds().width / 10 * 9, banner_game_over.getPosition().y + banner_game_over.getGlobalBounds().height / 1.6);
}

void Game_over::set_banner(unsigned int& new_score) {
    switch (new_score / 30) {
    case 0:
        banner_game_over.setTexture(tx_banner_empty);
        break;
    case 1:
        banner_game_over.setTexture(tx_banner_with_bronze_medal);
        break;
    case 2:
        banner_game_over.setTexture(tx_banner_with_silver_medal);
        break;
    case 3:
        banner_game_over.setTexture(tx_banner_with_gold_medal);
        break;
    case 4:
        banner_game_over.setTexture(tx_banner_with_platinum_medal);
        break;
    default:
        banner_game_over.setTexture(tx_banner_with_platinum_medal);
        break;
    }
    reading_writing.write_highscores(new_score);

    score.setString(std::to_string(new_score));
    score.setOrigin(score.getGlobalBounds().width, 0);

    best_score.setString(std::to_string(reading_writing.read_highscores()[0]));
    best_score.setOrigin(best_score.getGlobalBounds().width, 0);
}

void Game_over::draw(sf::RenderWindow& window) {
    window.draw(banner_game_over);
    window.draw(score);
    window.draw(best_score);
    window.draw(message_game_over);
    window.draw(button_ok);
}