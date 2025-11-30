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

    _startButton.setOutlineColor(_startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)
        ? sf::Color::Yellow : sf::Color::White);

    _exitButton.setOutlineColor(_exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)
        ? sf::Color::Yellow : sf::Color::White);

    // Mouse click detection
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (_startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            std::cout << "Start button clicked!\n";
            // TODO: Change scene when game scene exists!
            // GameSystem::set_active_scene(Scenes::game);
        }
        if (_exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            std::cout << "Exit button clicked!\n";
            Renderer::get_window().close();
        }
    }

    Scene::update(dt);


}

void MenuScene::render() {
    Renderer::queue(&_background);
    Renderer::queue(&_title);
    Renderer::queue(&_startButton);
    Renderer::queue(&_startText);
    Renderer::queue(&_exitButton);
    Renderer::queue(&_exitText);
    Scene::render();
}

void MenuScene::load() {

    if (!_backgroundTex.loadFromFile("resources/images/menu_background.png")) {
        std::cerr << "Failed to load menu background image\n";
    }
    _background.setTexture(_backgroundTex);


    _font.loadFromFile("resources/fonts/RobotoMono-Regular.ttf");
    
    _title.setFont(_font);
    _title.setString("The awakening");
    _title.setCharacterSize(72);
    _title.setFillColor(sf::Color::White);

    // Center title horizontally
    sf::FloatRect tBounds = _title.getLocalBounds();
    _title.setOrigin(tBounds.width / 2, tBounds.height / 2);
    _title.setPosition(param::game_width / 2, 150);

    // Start button setup
    _startText.setFont(_font);
    _startText.setString("Start new game");
    _startText.setCharacterSize(32);
    _startText.setFillColor(sf::Color::White);

    sf::FloatRect stBounds = _startText.getLocalBounds();
    _startText.setOrigin(stBounds.width / 2, stBounds.height / 2);
    _startText.setPosition(param::game_width / 2, 300);

    _startButton.setSize({ stBounds.width + 40, stBounds.height + 30 });
    _startButton.setOrigin(_startButton.getSize() / 2.f);
    _startButton.setPosition(_startText.getPosition());
    _startButton.setFillColor(sf::Color::Transparent);
    _startButton.setOutlineThickness(3);
    _startButton.setOutlineColor(sf::Color::White);

    // Exit button setup
    _exitText.setFont(_font);
    _exitText.setString("Exit game");
    _exitText.setCharacterSize(32);
    _exitText.setFillColor(sf::Color::White);

    sf::FloatRect exBounds = _exitText.getLocalBounds();
    _exitText.setOrigin(exBounds.width / 2, exBounds.height / 2);
    _exitText.setPosition(param::game_width / 2, 400);

    _exitButton.setSize({ exBounds.width + 40, exBounds.height + 30 });
    _exitButton.setOrigin(_exitButton.getSize() / 2.f);
    _exitButton.setPosition(_exitText.getPosition());
    _exitButton.setFillColor(sf::Color::Transparent);
    _exitButton.setOutlineThickness(3);
    _exitButton.setOutlineColor(sf::Color::White);
}


