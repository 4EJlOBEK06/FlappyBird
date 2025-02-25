#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include "GameElements/Assets.h"
#include "GameElements/Sound_Assets.h"
#include "FunctionClasses/Reading_writing_file.h"

class Scores {

	sf::RenderWindow& window;

    Assets& assets;
    
    Surface surface;
    Pipes pipes;

    Reading_writing reading_writing{};

    sf::Sprite background;
    sf::Sprite bunner_scores;
    sf::Sprite button_ok;

    sf::Text text_scores;

    sf::Sound sound_push_button;

    float coefficient_x{};
    float coefficient_y{};

    std::vector<int> vec_scores;

    void set_coefficient(sf::RenderWindow& window);
    void draw_scores(sf::RenderWindow& window);

public:
    Scores(sf::RenderWindow& window, Assets& assets, Sound& sound);
    void update(unsigned int& Level);

    bool delete_object{ false };
};

Scores::Scores(sf::RenderWindow& window, Assets& assets, Sound& sound)
    :window(window),
    assets(assets),
    surface(assets, window.getSize()),
    pipes(assets, window.getSize()) {
    
    set_coefficient(window);

    text_scores.setFont(assets.font_numbers);
    text_scores.setCharacterSize(64 * coefficient_y);
    text_scores.setFillColor(sf::Color::Black);

    background.setTexture(assets.tx_background_night);
    background.setScale(1 * coefficient_x, 1 * coefficient_y);

    bunner_scores.setTexture(assets.tx_banner_scores);
    bunner_scores.setScale(1 * coefficient_x, 1 * coefficient_y);
    bunner_scores.setPosition(window.getSize().x / 2 - bunner_scores.getGlobalBounds().width / 2, window.getSize().y / 2 - bunner_scores.getGlobalBounds().height / 2);

    button_ok.setTexture(assets.tx_button_ok);
    button_ok.setScale(2 * coefficient_x, 2 * coefficient_y);
    button_ok.setPosition(window.getSize().x / 2 - button_ok.getGlobalBounds().width / 2, bunner_scores.getGlobalBounds().getPosition().y + bunner_scores.getGlobalBounds().height + button_ok.getGlobalBounds().height / 10);

    sound_push_button.setBuffer(sound.buffer_push_button);
    sound_push_button.setVolume(sound.volume);

    vec_scores = reading_writing.read_highscores();
}

void Scores::set_coefficient(sf::RenderWindow& window) {

    coefficient_x = window.getSize().x / 1920.f;
    coefficient_y = window.getSize().y / 1080.f;
}

void Scores::draw_scores(sf::RenderWindow& window) {
    for (size_t i = 0; i < vec_scores.size(); ++i) {
        text_scores.setString(std::to_string(vec_scores[i]));
        text_scores.setPosition(bunner_scores.getGlobalBounds().getPosition().x + bunner_scores.getGlobalBounds().width / 2 - text_scores.getGlobalBounds().width / 2, bunner_scores.getPosition().y + bunner_scores.getGlobalBounds().height / 9 + (55 * coefficient_y + text_scores.getGlobalBounds().height) * i );
        window.draw(text_scores);
    }
}

void Scores::update(unsigned int& Level) {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (button_ok.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                sound_push_button.play();
                delete_object = true;
                Level -= 2;
                break;
            }

        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            sound_push_button.play();
            delete_object = true;
            Level -= 2;
        }
    }

    window.draw(background);
    window.draw(bunner_scores);
    window.draw(button_ok);
    draw_scores(window);

}