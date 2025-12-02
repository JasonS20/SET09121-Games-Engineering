#include <cmath>
#include "scenes.hpp"
#include "game_paramaters.hpp"
#include "renderer.hpp"
#include "game_system.hpp"
#include <iostream>

using param = Parameters;

std::shared_ptr<Scene> Scenes::menu;

void MenuScene::update(const float& dt) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(Renderer::get_window());

    // Hover effects (optional)

    _menu_startButton.setOutlineColor(_menu_startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)
        ? sf::Color::Yellow : sf::Color::White);

    _menu_exitButton.setOutlineColor(_menu_exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)
        ? sf::Color::Yellow : sf::Color::White);

    // Mouse click detection
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (_menu_startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            std::cout << "Start button clicked!\n";
            // TODO: Change scene when game scene exists!
            // GameSystem::set_active_scene(Scenes::game);
        }
        if (_menu_exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            std::cout << "Exit button clicked!\n";
            Renderer::get_window().close();
        }
    }

    Scene::update(dt);


}

void MenuScene::render() {
    Renderer::queue(&_menu_background);
    Renderer::queue(&_menu_title);
    Renderer::queue(&_menu_startButton);
    Renderer::queue(&_menu_startText);
    Renderer::queue(&_menu_exitButton);
    Renderer::queue(&_menu_exitText);
    Scene::render();
}

void MenuScene::load() {

    if (!_menu_backgroundTex.loadFromFile("resources/images/menu_background.png")) {
        std::cerr << "Failed to load menu background image\n";
    }
    _menu_background.setTexture(_menu_backgroundTex);


    _font.loadFromFile("resources/fonts/RobotoMono-Regular.ttf");
    
    _menu_title.setFont(_font);
    _menu_title.setString("The awakening");
    _menu_title.setCharacterSize(72);
    _menu_title.setFillColor(sf::Color::White);

    // Center title horizontally
    sf::FloatRect tBounds = _menu_title.getLocalBounds();
    _menu_title.setOrigin(tBounds.width / 2, tBounds.height / 2);
    _menu_title.setPosition(param::game_width / 2, 150);

    // Start button setup
    _menu_startText.setFont(_font);
    _menu_startText.setString("Start new game");
    _menu_startText.setCharacterSize(32);
    _menu_startText.setFillColor(sf::Color::White);

    sf::FloatRect stBounds = _menu_startText.getLocalBounds();
    _menu_startText.setOrigin(stBounds.width / 2, stBounds.height / 2);
    _menu_startText.setPosition(param::game_width / 2, 300);

    _menu_startButton.setSize({ stBounds.width + 40, stBounds.height + 30 });
    _menu_startButton.setOrigin(_menu_startButton.getSize() / 2.f);
    _menu_startButton.setPosition(_menu_startText.getPosition());
    _menu_startButton.setFillColor(sf::Color::Transparent);
    _menu_startButton.setOutlineThickness(3);
    _menu_startButton.setOutlineColor(sf::Color::White);

    // Exit button setup
    _menu_exitText.setFont(_font);
    _menu_exitText.setString("Exit game");
    _menu_exitText.setCharacterSize(32);
    _menu_exitText.setFillColor(sf::Color::White);

    sf::FloatRect exBounds = _menu_exitText.getLocalBounds();
    _menu_exitText.setOrigin(exBounds.width / 2, exBounds.height / 2);
    _menu_exitText.setPosition(param::game_width / 2, 400);

    _menu_exitButton.setSize({ exBounds.width + 40, exBounds.height + 30 });
    _menu_exitButton.setOrigin(_menu_exitButton.getSize() / 2.f);
    _menu_exitButton.setPosition(_menu_exitText.getPosition());
    _menu_exitButton.setFillColor(sf::Color::Transparent);
    _menu_exitButton.setOutlineThickness(3);
    _menu_exitButton.setOutlineColor(sf::Color::White);
}


