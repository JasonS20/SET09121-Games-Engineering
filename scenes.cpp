#include <cmath>
#include "scenes.hpp"
#include "game_paramaters.hpp"
#include "renderer.hpp"
#include "game_system.hpp"
#include <iostream>

using param = Parameters;

std::shared_ptr<Scene> Scenes::menu;
std::shared_ptr<Scene> Scenes::level3;


void MenuScene::update(const float& dt) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(Renderer::get_window());

    _menu_startButton.setOutlineColor(_menu_startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)
        ? sf::Color::Yellow : sf::Color::White);

    _menu_exitButton.setOutlineColor(_menu_exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)
        ? sf::Color::Yellow : sf::Color::White);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (_menu_startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            GameSystem::set_active_scene(Scenes::level3);
        }
        if (_menu_exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
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

    sf::FloatRect tBounds = _menu_title.getLocalBounds();
    _menu_title.setOrigin(tBounds.width / 2, tBounds.height / 2);
    _menu_title.setPosition(param::game_width / 2, 150);


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

void Level3Scene::update(const float& dt) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(Renderer::get_window());


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
        GameSystem::set_active_scene(Scenes::menu);
    }

    if (_state == HouseState::Explore) {
        if (!_houseDrawerOpened &&
            _houseDrawer.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y) &&
            sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

            _houseDrawerOpened = true;
            _houseNoteVisible = true;
        }

        if (_houseNoteVisible && sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
            _houseNoteVisible = false;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _houseDrawerOpened) {
            for (size_t i = 0; i < _houseBooks.size(); i++) {
                if (_houseBooks[i].getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y)) {

                    if (i == _houseCorrectBookIndex) {
                        _houseClueVisible = true;
                    }
                    return;
                }
            }
        }

        if (_houseClueVisible && sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
            _houseClueVisible = false; 
            _houseDoorClickable = true;
        }

        if (_houseDoor.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
            sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (_houseDoorClickable)
            {
                std::cout << "Door clicked - keypad active!" << std::endl;
                _state = HouseState::Padlock;
            }
            else
            {
                _houseLockedMsgVisible = true;
            }
        }

        if (_houseLockedMsgVisible && sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
        {
            _houseLockedMsgVisible = false;
        }


    }



    else if (_state == HouseState::Padlock) {
        for (int key = sf::Keyboard::Num0; key <= sf::Keyboard::Num9; key++) {
            if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key) && _houseEnteredCode.size() < 4) {
                _houseEnteredCode += char('0' + (key - sf::Keyboard::Num0));
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !_houseEnteredCode.empty()) {
            _houseEnteredCode.pop_back();
        }

        if (_houseEnteredCode == "2334") {
            GameSystem::set_active_scene(Scenes::menu);
        }

        _housePadlockText.setString(_houseEnteredCode);
    }

    Scene::update(dt);

}

void Level3Scene::render() {
    Renderer::queue(&_houseDrawer);
    Renderer::queue(&_houseBookshelf);
    Renderer::queue(&_houseDoor);
    Renderer::queue(&_houseBackground);
    if (_state == HouseState::Padlock) {
        Renderer::queue(&_housePadlockText);
        Renderer::queue(&_housePadlockInstr);
    }

    for (auto& b : _houseBooks) {
        Renderer::queue(&b);
    }

    if (_houseNoteVisible) {
        Renderer::queue(&_houseNoteBox);
        Renderer::queue(&_houseNoteText);
    }

    if (_houseClueVisible) {
        Renderer::queue(&_houseClueBox);
        Renderer::queue(&_houseClueText);
    }

    if (_houseLockedMsgVisible)
    {
        Renderer::queue(&_houseLockedMsgBox);
        Renderer::queue(&_houseLockedMsgText);
    }

;
}

void Level3Scene::load() {

    _state = HouseState::Explore;
    _houseEnteredCode = "";

    _houseBgTexture.loadFromFile("resources/images/house_bg.png");
    _houseBackground.setTexture(_houseBgTexture);
    _houseBackground.setScale(1920.f / _houseBgTexture.getSize().x, 1080.f / _houseBgTexture.getSize().y);

    _houseDrawer.setSize({ 150, 80 });
    _houseDrawer.setFillColor(sf::Color(160, 82, 45));
    _houseDrawer.setPosition(450, 600);

    _houseBookshelf.setSize({ 400, 200 });
    _houseBookshelf.setPosition( 1300, 350);
    _houseBookshelf.setFillColor(sf::Color(100, 70, 40));


    _houseBookshelf.setOutlineThickness(6);
    _houseBookshelf.setOutlineColor(sf::Color(60, 40, 20));



    _houseBooks.clear();

    float padding = 20.f;
    float shelfX = _houseBookshelf.getPosition().x + padding;
    float shelfY = _houseBookshelf.getPosition().y + padding;
    float shelfWidth = _houseBookshelf.getSize().x - (padding * 2);
    float shelfHeight = _houseBookshelf.getSize().y - (padding * 2);


    float bookWidth = shelfWidth / 6.f - 5.f;
    float bookHeight = shelfHeight;


    for (int i = 0; i < 6; i++) {
        sf::RectangleShape book({ bookWidth, bookHeight });
        book.setPosition(shelfX + i * (bookWidth + 5.f), shelfY);

        book.setFillColor(sf::Color::Blue);

        _houseBooks.push_back(book);
    }

    _houseDoor.setSize({ 200, 400 });
    if (_houseDoorClickable)
        _houseDoor.setFillColor(sf::Color(255, 255, 255, 255));
    else
        _houseDoor.setFillColor(sf::Color(160, 160, 160, 200));
    _houseDoor.setPosition(50, 350);


    _houseFont.loadFromFile("resources/fonts/RobotoMono-Regular.ttf");

    _houseNoteBox.setSize({ 600, 200 });
    _houseNoteBox.setFillColor(sf::Color(255, 255, 200));
    _houseNoteBox.setPosition(660, 300);

    _houseNoteText.setFont(_houseFont);
    _houseNoteText.setCharacterSize(28);
    _houseNoteText.setFillColor(sf::Color::Black);
    _houseNoteText.setString("My favourite book\nis always read fourth.");
    _houseNoteText.setPosition(700, 350);

    _houseClueBox.setSize({ 600, 200 });
    _houseClueBox.setFillColor(sf::Color(255, 255, 200));
    _houseClueBox.setPosition(660, 300);

    _houseClueText.setFont(_houseFont);
    _houseClueText.setCharacterSize(28);
    _houseClueText.setFillColor(sf::Color::Black);
    _houseClueText.setString("Picture 23 - Page 34");
    _houseClueText.setPosition(700, 350);

    _housePadlockText.setFont(_houseFont);
    _housePadlockText.setCharacterSize(72);
    _housePadlockText.setFillColor(sf::Color::White);
    _housePadlockText.setPosition(800, 450);
    _housePadlockText.setString("____");

    _housePadlockInstr.setFont(_houseFont);
    _housePadlockInstr.setCharacterSize(28);
    _housePadlockInstr.setFillColor(sf::Color::Yellow);
    _housePadlockInstr.setPosition(650, 550);
    _housePadlockInstr.setString("Enter Code (Press Numbers)");

    _houseLockedMsgBox.setSize({ 600, 200 });
    _houseLockedMsgBox.setFillColor(sf::Color(200, 50, 50));
    _houseLockedMsgBox.setPosition(660, 300);

    _houseLockedMsgText.setFont(_houseFont);
    _houseLockedMsgText.setCharacterSize(28);
    _houseLockedMsgText.setFillColor(sf::Color::White);
    _houseLockedMsgText.setString("The door is locked!");
    _houseLockedMsgText.setPosition(700, 350);

}