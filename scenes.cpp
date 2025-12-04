#include <algorithm>
#include <cmath>
#include "scenes.hpp"
#include "game_parameters.hpp"
#include "renderer.hpp"
#include "game_system.hpp"
#include "physics.hpp"
#include "b2d_utils.hpp"
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




    auto withinRange = [this](const sf::RectangleShape& target) {
        sf::Vector2f center = target.getPosition() + target.getSize() / 2.f;
        float dist = std::hypot(center.x - _playerPos.x, center.y - _playerPos.y);
        return dist <= _interactionRange;
    };

    bool leftMouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (_state == HouseState::Explore) {

        if (leftMouseDown && !_houseLeftMouseDownPrev &&
            _houseStool.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y)) {
            _houseStoolControlEnabled = !_houseStoolControlEnabled;
            if (_houseStoolControlEnabled) {
                _houseStoolMsgText.setString("Stool selected: walk into it to push toward the shelf. Click again to release.");
            }
            else {
                _houseStoolVelocity = { 0.f, 0.f };
                _houseStoolMsgText.setString("Click the stool to select it before pushing toward the shelf.");
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(Renderer::get_window());

            // Only interact if mouse hovers over the stool
            if (_houseStool.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                if (!_playerOnStool)
                {
                    // Save old position
                    _savedPlayerPos = _playerPos;

                    // Move to top of the stool
                    sf::Vector2f stoolPos = _houseStool.getPosition();
                    sf::Vector2f stoolSize = _houseStool.getSize();

                    _playerPos.x = stoolPos.x + (stoolSize.x / 40.f);
                    _playerPos.y = stoolPos.y - (_playerSprite.getGlobalBounds().height);

                    _playerSprite.setPosition(_playerPos);
                    _playerOnStool = true;
                }
                else
                {
                    // Move back to previous floor position
                    _playerPos = _savedPlayerPos;
                    _playerSprite.setPosition(_playerPos);
                    _playerOnStool = false;
                }
            }
        }

        float playerInput = 0.f;
        if (!_playerOnStool)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                playerInput -= 1.f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                playerInput += 1.f;
            }
        }

        Physics::MovementSettings settings{ 450.f, 8.f, 6.f, _houseStoolFloorY, (float)param::game_width };
        Physics::integratePlayer(dt, playerInput, settings, _housePlayer, _housePlayerVelocity);

        if (_houseStoolControlEnabled) {
            Physics::dampAndMoveStool(dt, settings.friction, _houseStool, _houseStoolVelocity);
            Physics::resolvePlayerStoolCollision(_housePlayer, _housePlayerVelocity, _houseStool, _houseStoolVelocity);
        }
        else {
            _houseStoolVelocity = { 0.f, 0.f };
        }
        Physics::clampStoolWithinScene(settings.sceneWidth, _houseStoolFloorY, _houseStool, _houseStoolVelocity);

        float stoolCenterX = _houseStool.getPosition().x + _houseStool.getSize().x / 2.f;
        float stoolBottom = _houseStool.getPosition().y + _houseStool.getSize().y;
        float shelfBottom = _houseBookshelf.getPosition().y + _houseBookshelf.getSize().y;

        bool alignedWithShelf = std::abs(stoolCenterX - (_houseBookshelf.getPosition().x +
            _houseBookshelf.getSize().x / 2.f)) <= _houseBookshelf.getSize().x / 2.f;
        bool closeInHeight = std::abs(stoolBottom - shelfBottom) <= 400.f;
        _houseStoolPlaced = alignedWithShelf && closeInHeight;




        if (withinRange(_houseDrawer) && !_housePictureVisible && !_houseClueVisible && _houseDrawer.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y) &&
            sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

            _houseDrawerOpened = true;
            _houseNoteVisible = true;
        }

        if (_houseNoteVisible && sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
            _houseNoteVisible = false;
        }


        if (withinRange(_housePicture) && !_houseNoteVisible && !_houseClueVisible && _housePicture.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y) &&
            sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

            _housePictureVisible = true;
        }

        if (_housePictureVisible && sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
            _housePictureVisible = false;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _houseDrawerOpened) {
            for (size_t i = 0; i < _houseBooks.size(); i++) {
                if (withinRange(_houseBooks[i]) && !_houseNoteVisible && !_housePictureVisible && _houseBooks[i].getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y)) {

                    if (i == _houseCorrectBookIndex) {
                        _houseClueVisible = true;
                    }
                    else {
                        _houseStoolMsgText.setString("Need to be taller to reach it.");
                    }

                    return;
                }
            }
        }

        if (_houseClueVisible && sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
            _houseClueVisible = false;
            _houseDoorClickable = true;
        }

        if (withinRange(_houseDoor) && !_houseNoteVisible && !_housePictureVisible && !_houseClueVisible && _houseDoor.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
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


        sf::Vector2f moveDir(0.f, 0.f);


        if (!_playerOnStool)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                moveDir.x -= 1.f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                moveDir.x += 1.f;
            }

            _playerPos += moveDir * _playerSpeed * dt;

            float halfWidth = _player.getSize().x / 2.f;
            _playerPos.x = std::clamp(_playerPos.x, halfWidth, param::game_width - halfWidth);
        }




        _playerPos.x = std::clamp(_playerPos.x, 0.0f, param::game_width - _housePlayer.getSize().x);


        _housePlayer.setPosition(_playerPos);
        _playerSprite.setPosition(_playerPos);

        b2World_Step(_world_id, param::time_step, param::sub_step_count);

        for (size_t i = 0; i < _bodies.size(); ++i) {
            sf::Vector2f pos = box2d_helpers::invert_height(box2d_helpers::bv2_to_sv2(b2Body_GetPosition(_bodies[i])));
            _sprites[i]->setPosition(pos);
            const float pi = 3.14159;
            _sprites[i]->setRotation((180.f / pi));
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
        {
            _state = HouseState::Explore;
        }
    }

    _houseLeftMouseDownPrev = leftMouseDown;

    Scene::update(dt);

}

void Level3Scene::render() {
    Renderer::queue(&_houseBackground);
    Renderer::queue(&_houseDrawer);
    Renderer::queue(&_houseBookshelf);
    Renderer::queue(&_housePicture);
    Renderer::queue(&_houseDoor);
    Renderer::queue(&_housePlayer);
    Renderer::queue(&_houseStool);
    Renderer::queue(&_playerSprite);


    
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

    if (_housePictureVisible) {
        Renderer::queue(&_housePictureBox);
        Renderer::queue(&_housePictureText);
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

    if (!_houseStoolMsgText.getString().isEmpty())
    {
        Renderer::queue(&_houseStoolMsgText);
    }

}

void Level3Scene::load() {

    _state = HouseState::Explore;
    _houseEnteredCode = "";

    



    std::cout << "Max texture size: " << sf::Texture::getMaximumSize() << "\n";

    _houseBgTexture.loadFromFile("resources/images/house_background.png");
    _houseBackground.setTexture(_houseBgTexture);
    _houseBackground.setScale(1920.f / _houseBgTexture.getSize().x, 1080.f / _houseBgTexture.getSize().y);

    _houseDrawer.setSize({ 150, 80 });
    _houseDrawer.setFillColor(sf::Color(0, 0, 0, 0));
    _houseDrawer.setPosition(450, 800);

    _houseBookshelf.setSize({ 400, 200 });
    _houseBookshelf.setPosition( 1300, 600);
    _houseBookshelf.setFillColor(sf::Color(0, 0, 0, 0));

    _housePicture.setSize({ 201, 122 });
    _housePicture.setPosition(425, 629);
    _housePicture.setFillColor(sf::Color(0, 0, 0, 0));


    _houseBookshelf.setOutlineThickness(6);
    _houseBookshelf.setOutlineColor(sf::Color(0, 0, 0, 0));



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

        book.setFillColor(sf::Color(0, 0, 0, 0));

        _houseBooks.push_back(book);
    }

    _houseDoor.setSize({ 200, 400 });
    if (_houseDoorClickable)
        _houseDoor.setFillColor(sf::Color(0, 0, 0, 0));
    else
        _houseDoor.setFillColor(sf::Color(0, 0, 0, 0));
    _houseDoor.setPosition(50, 550);

    

    if (!_playerTexture.loadFromFile("resources/images/player.png")) {
        std::cerr << "Failed to load player texture!\n";
    }

    _player.setSize({ 60.f, 120.f });
    _player.setOrigin(_player.getSize() / 2.f);
    _playerSprite.setTexture(_playerTexture);
    _playerSprite.setScale(
        _player.getSize().x / _playerTexture.getSize().x,
        _player.getSize().y / _playerTexture.getSize().y);
    _playerPos.x = param::game_width / 2.f;
    _playerPos.y = 830;
    _player.setPosition(_playerPos);
    _playerSprite.setPosition(_playerPos);

    _houseStoolPlaced = false;
    _houseStool.setSize({ 80, 80 });
    _houseStool.setFillColor(sf::Color(180, 130, 80));
    _houseStool.setOutlineThickness(4);
    _houseStool.setOutlineColor(sf::Color(120, 80, 40));
    _houseStool.setPosition(850, 870);
    _houseStoolFloorY = _houseStool.getPosition().y;
    _houseStoolVelocity = { 0.f, 0.f };

    _housePlayer.setSize({ 60, 120 });
    _housePlayer.setFillColor(sf::Color(0, 0, 0, 0));
    _housePlayer.setPosition(200, _houseStoolFloorY - _housePlayer.getSize().y);
    _housePlayerVelocity = { 0.f, 0.f };;


    _houseFont.loadFromFile("resources/fonts/RobotoMono-Regular.ttf");

    _houseNoteBox.setSize({ 600, 200 });
    _houseNoteBox.setFillColor(sf::Color(0, 0, 0, 0));
    _houseNoteBox.setPosition(660, 300);

    _houseNoteText.setFont(_houseFont);
    _houseNoteText.setCharacterSize(28);
    _houseNoteText.setFillColor(sf::Color::Black);
    _houseNoteText.setString("Always remember \ngreen was always my favourite.");
    _houseNoteText.setPosition(700, 350);

    _houseClueBox.setSize({ 600, 200 });
    _houseClueBox.setFillColor(sf::Color(0, 0, 0, 0));
    _houseClueBox.setPosition(660, 300);

    _houseClueText.setFont(_houseFont);
    _houseClueText.setCharacterSize(28);
    _houseClueText.setFillColor(sf::Color::Black);
    _houseClueText.setString("The book open to page 34");
    _houseClueText.setPosition(700, 350);

    _housePictureBox.setSize({ 600, 200 });
    _housePictureBox.setFillColor(sf::Color(0, 0, 0, 0));
    _housePictureBox.setPosition(660, 300);

    _housePictureText.setFont(_houseFont);
    _housePictureText.setCharacterSize(28);
    _housePictureText.setFillColor(sf::Color::Black);
    _housePictureText.setString("The picture frame is empty\nthe frame has is labeled: \nFamily picture 23.");
    _housePictureText.setPosition(700, 350);

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


    _houseStoolMsgText.setFont(_houseFont);
    _houseStoolMsgText.setCharacterSize(24);
    _houseStoolMsgText.setFillColor(sf::Color::Yellow);
    _houseStoolMsgText.setString("");
    _houseStoolMsgText.setPosition(700, 800);

    _houseStoolMsgText.setFont(_houseFont);
    _houseStoolMsgText.setCharacterSize(24);
    _houseStoolMsgText.setFillColor(sf::Color::Yellow);
    _houseStoolMsgText.setString("Walk into the stool to push it toward the shelf.");
    _houseStoolMsgText.setPosition(700, 800);


    _sprites.clear();
    _bodies.clear();

    b2WorldDef world_def = b2DefaultWorldDef();
    world_def.gravity = { 0.0f, param::g };
    _world_id = b2CreateWorld(&world_def);

    for (int i = 1; i < 11; ++i) {
        std::shared_ptr<sf::RectangleShape> s = std::make_shared<sf::RectangleShape>();
        s->setPosition(sf::Vector2f(i * (param::game_width / 12.f), param::game_height * .7f));
        s->setSize(sf::Vector2f(50.0f, 50.0f));
        s->setOrigin(sf::Vector2f(25.0f, 25.0f));
        s->setFillColor(sf::Color::White);
        _sprites.push_back(s);

        b2BodyId b = box2d_helpers::create_physics_box(_world_id, true, s);
        b2Body_ApplyAngularImpulse(b, 5.0f, 1);
        _bodies.push_back(b);
    }

    sf::Vector2f walls[] = {
        sf::Vector2f(param::game_width * .5f, 5.f), sf::Vector2f(param::game_width, 10.f),
        sf::Vector2f(param::game_width * .5f, param::game_height - 5.f), sf::Vector2f(param::game_width, 10.f),
        sf::Vector2f(5.f, param::game_height * .5f), sf::Vector2f(10.f, param::game_height),
        sf::Vector2f(param::game_width - 5.f, param::game_height * .5f), sf::Vector2f(10.f, param::game_height)
    };

    for (int i = 0; i < 8; i += 2) {
        std::shared_ptr<sf::RectangleShape> wall = std::make_shared<sf::RectangleShape>();
        wall->setPosition(walls[i]);
        wall->setSize(walls[i + 1]);
        wall->setOrigin(wall->getSize() / 2.f);
        wall->setFillColor(sf::Color(80, 80, 80));
        _sprites.push_back(wall);

        b2BodyId b = box2d_helpers::create_physics_box(_world_id, false, wall);
        _bodies.push_back(b);
    }
}

void Level3Scene::unload() {
    _sprites.clear();
    _bodies.clear();
    if (_world_created) {
        b2DestroyWorld(_world_id);
        _world_id = {};
        _world_created = false;
    }

}

