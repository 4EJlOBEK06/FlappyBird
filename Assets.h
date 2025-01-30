#pragma once
#include <SFML/Graphics.hpp>

class Assets {
public:
    sf::Texture tx_background_day;
    sf::Texture tx_background_night;

    sf::Texture tx_bird_down;
    sf::Texture tx_bird_mid;
    sf::Texture tx_bird_up;

    sf::Texture tx_message_flappybird;

    sf::Texture tx_pipe;
    sf::Texture tx_surface;

    sf::Texture tx_button_start;
    sf::Texture tx_button_score;
    sf::Texture tx_button_settings;

    sf::Texture tx_message_get_ready;

    sf::Texture tx_message_game_over;
    sf::Texture tx_banner_empty;
    sf::Texture tx_banner_with_bronze_medal;
    sf::Texture tx_banner_with_silver_medal;
    sf::Texture tx_banner_with_gold_medal;
    sf::Texture tx_banner_with_platinum_medal;

    sf::Texture tx_banner_scores;

    sf::Texture tx_check_box_false;
    sf::Texture tx_check_box_true;
    sf::Texture tx_settings_banner;
    sf::Texture tx_volume_slider;

    sf::Texture tx_button_ok;

    sf::Font font_numbers;

    Assets();
};

Assets::Assets() {
    tx_background_day.loadFromFile("sprites/background-day.png");
    tx_background_night.loadFromFile("sprites/background-night.png");

    tx_bird_down.loadFromFile("sprites/yellowbird-downflap.png");
    tx_bird_mid.loadFromFile("sprites/yellowbird-midflap.png");
    tx_bird_up.loadFromFile("sprites/yellowbird-upflap.png");

    tx_message_flappybird.loadFromFile("sprites/message-flappybird.png");
    
    tx_pipe.loadFromFile("sprites/pipe-green.png");
    tx_surface.loadFromFile("sprites_fhd/base.png");

    tx_button_start.loadFromFile("sprites/button-start-game.png");
    tx_button_score.loadFromFile("sprites/button-score.png");
    tx_button_settings.loadFromFile("sprites/button-settings.png");

    tx_message_get_ready.loadFromFile("sprites/message_get_ready.png");

    tx_message_game_over.loadFromFile("sprites/game-over.png");
    tx_banner_empty.loadFromFile("sprites/banner-empty.png");
    tx_banner_with_bronze_medal.loadFromFile("sprites/banner-with-bronze-medal.png");
    tx_banner_with_silver_medal.loadFromFile("sprites/banner-with-silver-medal.png");
    tx_banner_with_gold_medal.loadFromFile("sprites/banner-with-gold-medal.png");
    tx_banner_with_platinum_medal.loadFromFile("sprites/banner-with-platinum-medal.png");

    tx_banner_scores.loadFromFile("sprites/banner-scores.png");

    tx_check_box_false.loadFromFile("sprites/check-box-false.png");
    tx_check_box_true.loadFromFile("sprites/check-box-true.png");
    tx_settings_banner.loadFromFile("sprites/settings-banner.png");
    tx_volume_slider.loadFromFile("sprites/volume-slider.png");

    tx_button_ok.loadFromFile("sprites/button-ok.png");

    font_numbers.loadFromFile("Font_FlappyBird.otf");
}