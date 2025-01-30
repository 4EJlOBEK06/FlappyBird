#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Assets.h"
#include "Sound_Assets.h"
#include "Menu.h"
#include "Level_game.h"
#include "Scores.h"
#include "Settings.h"


int main()
{
    int Speed{ 400 }; // 400
    unsigned int Level{};
    unsigned int fps{};

    bool fullscreen{ true };
    bool vertical_sync{ true };

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Flappy bird", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);

    Assets assets;
    Sound sound;

    Menu* menu{ nullptr };
    Level_game* level_game{ nullptr };
    Scores* scores{ nullptr };
    Settings* settings{ nullptr };

    sf::Clock clock;
    sf::Time Time;

    sf::Text text_fps;
    text_fps.setFont(assets.font_numbers);
    text_fps.setCharacterSize(text_fps.getCharacterSize() * (1080 / window.getSize().y));
    text_fps.setFillColor(sf::Color::Black);

    while (window.isOpen()){

        Time += clock.getElapsedTime();
        float time = clock.restart().asMicroseconds();
        time /= Speed;

        window.clear();
        

        switch (Level) {
        case 0:
            if (!menu) {
                menu = new Menu(window, assets, sound);
            }
            if (menu->delete_object == true) {
                delete menu;
                menu = nullptr;
            } else {
                menu->update(time, Level);
            }
            break;
        case 1:
            if (!level_game) {
                level_game = new Level_game(window, assets, sound);
            }
            if (level_game->delete_object == true) {
                delete level_game;
                level_game = nullptr;
            } else {
                level_game->update(time, Level, Speed);
            }
            break;
        case 2:
            if (!scores) {
                scores = new Scores(window, assets, sound);
            }
            if (scores->delete_object == true) {
                delete scores;
                scores = nullptr;
            } else {
                scores->update(Level);
            }
            break;
        case 3:
            if (!settings) {
                settings = new Settings(window, assets, sound, fullscreen, vertical_sync);
            }
            if (settings->delete_object == true) {
                delete settings;
                settings = nullptr;
            }
            else {
                settings->update(Level);
            }
            break;
        }

        sf::FloatRect visibleArea(0, 0, window.getSize().x, window.getSize().y);
        window.setView(sf::View(visibleArea));

        ++fps;
        if (Time.asSeconds() >= 1) {
            Time = sf::microseconds(0);
            text_fps.setString(std::to_string(fps));
            fps = 0;
        }
        window.draw(text_fps);
        window.display();
    }

    return 0;
}