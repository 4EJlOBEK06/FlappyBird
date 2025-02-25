#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameElements/Assets.h"
#include "GameElements/Sound_Assets.h"
#include "GameElements/Player.h"
#include "GameElements/Message_get_ready.h"
#include "GameElements/Pipes.h"
#include "GameElements/Surface.h"
#include "GameElements/Game_over.h"

class Level_game {

    sf::RenderWindow& window;

    Assets& assets;
    Player player;
    Surface surface;
    Pipes pipes;
    Message_get_ready message_get_ready;
    Game_over game_over;

    sf::Sprite background;
    sf::Text score_game;

    sf::Sound sound_jump;
    sf::Sound sound_hit;
    sf::Sound sound_point;
    sf::Sound sound_push_button;

    bool b_play{ false };
    bool b_game_over{ false };

    float coefficient_x{};
    float coefficient_y{};
    unsigned int count_score{0};
    int num_passed_pipe{1};

public:
	Level_game(sf::RenderWindow& window, Assets& assets, Sound& sound);
    void set_coefficient(sf::RenderWindow& window);
    void update(float& time, unsigned int& Level, int& speed);

    bool delete_object{ false };
};

Level_game::Level_game(sf::RenderWindow& window, Assets& assets, Sound& sound)
    :window(window),
    assets(assets),
    player(assets, window.getSize()),
    surface(assets, window.getSize()),
    pipes(assets, window.getSize()),
    message_get_ready(assets, window.getSize()),
    game_over(assets, window.getSize()){

    set_coefficient(window);

    background.setTexture(assets.tx_background_day);
    background.setScale(1 * coefficient_x, 1 * coefficient_y);

    score_game.setFont(assets.font_numbers);
    score_game.setPosition(window.getSize().x / 2 - score_game.getGlobalBounds().width / 2, window.getSize().y / 10);
    score_game.setCharacterSize(96 * coefficient_y);

    sound_jump.setBuffer(sound.buffer_jump);
    sound_jump.setVolume(sound.volume);

    sound_hit.setBuffer(sound.buffer_hit);
    sound_hit.setVolume(sound.volume);

    sound_point.setBuffer(sound.buffer_point);
    sound_point.setVolume(sound.volume);

    sound_push_button.setBuffer(sound.buffer_push_button);
    sound_push_button.setVolume(sound.volume);
}

void Level_game::set_coefficient(sf::RenderWindow& window) {
    coefficient_x = window.getSize().x / 1920.f;
    coefficient_y = window.getSize().y / 1080.f;
}

void Level_game::update(float& time, unsigned int& Level, int& speed) {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left || event.mouseButton.button == sf::Mouse::Right) {
                if (b_play) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sound_jump.play();
                        player.coord_y = -5.f * coefficient_y;
                    }else {
                        sound_jump.play();
                        player.coord_y = -6.f * coefficient_y;
                    }
                }else if (!b_game_over){
                    sound_push_button.play();
                    b_play = true;
                }
                if(game_over.button_ok.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    sound_push_button.play();
                    delete_object = true;
                    --Level;
                }
            }
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && !b_game_over) {
            b_play = false;
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && b_game_over) {
            sound_push_button.play();
            delete_object = true;
            --Level;
        }
    }

    if (b_play) {

        pipes.coord_x = -5.f * coefficient_x;
        surface.coord_x = -5.f * coefficient_x;

        // Checking for being on the surface
        for (size_t i = 0; i < sizeof(surface.sprite) / sizeof(surface.sprite[0]); ++i) {
            if (player.sprite.getGlobalBounds().intersects(surface.sprite[i].getGlobalBounds())) {
                player.on_surface = true;
                break;
            }
            else {
                player.on_surface = false;
            }
        }

        // Game Score
        for (size_t i = 0; i < sizeof(pipes.sprites) / sizeof(pipes.sprites[0]); i += 2) {
            if (player.sprite.getPosition().x >= pipes.sprites[i].getPosition().x && num_passed_pipe != i) {
                sound_point.play();
                ++count_score;
                num_passed_pipe = i;
                score_game.setString(std::to_string(count_score));
                score_game.setOrigin(score_game.getGlobalBounds().width / 2, 0);
                speed = speed - i / 2;
            }
        }

        // Set Background
        if (count_score % 30 == 0) {
            if (count_score / 30 % 2) {
                background.setTexture(assets.tx_background_night);
            } else {
                background.setTexture(assets.tx_background_day);
            }
        }

        player.update(time, b_play);
        pipes.update(time, b_play);
        surface.update(time, b_play);

        window.draw(background);
        for (size_t i = 0; i < sizeof(pipes.sprites) / sizeof(pipes.sprites[0]); ++i) {
            if (player.sprite.getGlobalBounds().intersects(pipes.sprites[i].getGlobalBounds())) {

                sf::FloatRect birdBounds = player.sprite.getGlobalBounds();
                birdBounds.top += birdBounds.height / 4;
                birdBounds.height -= birdBounds.height / 2;
                birdBounds.left += birdBounds.width / 4;
                birdBounds.width -= birdBounds.width / 2;

                if (birdBounds.intersects(pipes.sprites[i].getGlobalBounds())) {
                    sound_hit.play();
                    game_over.set_banner(count_score);
                    b_game_over = true;
                    b_play = false;
                    speed = 400;
                    break;
                }
            }
            window.draw(pipes.sprites[i]);
        }

        for (size_t i = 0; i < sizeof(surface.sprite) / sizeof(surface.sprite[0]); ++i) {
            window.draw(surface.sprite[i]);
        }
        window.draw(score_game);
        window.draw(player.sprite);
    }
    else if (b_game_over) {

        game_over.update(time);

        window.draw(background);
        for (size_t i = 0; i < sizeof(pipes.sprites) / sizeof(pipes.sprites[0]); ++i) {
            window.draw(pipes.sprites[i]);
        }
        for (size_t i = 0; i < sizeof(surface.sprite) / sizeof(surface.sprite[0]); ++i) {
            window.draw(surface.sprite[i]);
        }
        window.draw(player.sprite);
        game_over.draw(window);
    }
    else {
        player.update(time, b_play, true);
        message_get_ready.update(time);
        window.draw(background);
        for (size_t i = 0; i < sizeof(pipes.sprites) / sizeof(pipes.sprites[0]); ++i) {
            window.draw(pipes.sprites[i]);
        }
        for (size_t i = 0; i < sizeof(surface.sprite) / sizeof(surface.sprite[0]); ++i) {
            window.draw(surface.sprite[i]);
        }
        if (message_get_ready.visible) {
            window.draw(message_get_ready.sprite);
        }
        window.draw(score_game);
        window.draw(player.sprite);
    }

}