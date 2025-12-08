#include <algorithm>
#include <SFML/Audio.hpp>
#include <cmath>
#include "scenes.hpp"
#include "game_parameters.hpp"
#include "renderer.hpp"
#include "game_system.hpp"
#include "physics.hpp"
#include "b2d_utils.hpp"
#include <iostream>





//Creates the scenes

using param = Parameters;

std::shared_ptr<Scene> Scenes::menu;
std::shared_ptr<Scene> Scenes::level1;
std::shared_ptr<Scene> Scenes::level2;


//This makes the logic of the menu  
void MenuScene::update(const float& dt) {
    
    //This gets the mouse posiition on the page
    sf::Vector2i mousePos = sf::Mouse::getPosition(Renderer::get_window());

    //changes teh colour of the button if they are hovered over
    _menu_startButton.setOutlineColor(_menu_startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)
        ? sf::Color::White : sf::Color::Black);

    _menu_exitButton.setOutlineColor(_menu_exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)
        ? sf::Color::White : sf::Color::Black);

    _menu_ControlsButton.setOutlineColor(_menu_ControlsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)
        ? sf::Color::White : sf::Color::Black);

    //This makes it so the buttons have functions once pressed 
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (_menu_startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            GameSystem::set_active_scene(Scenes::level1);
        }
        if (_menu_exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            Renderer::get_window().close();
        }
        if (_menu_ControlsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            if (!_controlsActive) {
                _controlsActive = true;
            }
            else {
                _controlsActive = false;
            }
        }
    }


    Scene::update(dt);


}

//This renders all the elements of the menu  
void MenuScene::render() {
    Renderer::queue(&_menu_background);
    Renderer::queue(&_menu_title);
    Renderer::queue(&_menu_startButton);
    Renderer::queue(&_menu_startText);
    Renderer::queue(&_menu_exitButton);
    Renderer::queue(&_menu_exitText);
    Renderer::queue(&_menu_ControlsText);
    Renderer::queue(&_menu_ControlsButton);

    if (_controlsActive) {
        Renderer::queue(&_menu_ControlsTextOutput);
    }

    Scene::render();
}

//This sets all of the elements to the desired position and states in the menu
void MenuScene::load() {

    //this loads the background 
    if (!_menu_backgroundTex.loadFromFile("resources/images/menu_background.png")) {
        std::cerr << "Failed to load menu background image\n";
    }
    _menu_background.setTexture(_menu_backgroundTex);
    _menu_background.setScale(5.f, 5.f);
    _menu_background.setPosition(585.f, 250.f);

    //This loads the font of the menu page
    _font.loadFromFile("resources/fonts/RobotoMono-Regular.ttf");
    
    //this sets the title of the page 
    _menu_title.setFont(_font);
    _menu_title.setString("The awakening");
    _menu_title.setCharacterSize(72);
    _menu_title.setFillColor(sf::Color::White);

    sf::FloatRect tBounds = _menu_title.getLocalBounds();
    _menu_title.setOrigin(tBounds.width / 2, tBounds.height / 2);
    _menu_title.setPosition(param::game_width / 2, 150);

    //this sets the text and position of the start button
    _menu_startText.setFont(_font);
    _menu_startText.setString("Start new game");
    _menu_startText.setCharacterSize(32);
    _menu_startText.setFillColor(sf::Color::Black);

    sf::FloatRect stBounds = _menu_startText.getLocalBounds();
    _menu_startText.setOrigin(stBounds.width / 2, stBounds.height / 2);
    _menu_startText.setPosition(param::game_width / 2, 500);
    
    //This sets the position of the start button
    _menu_startButton.setSize({ stBounds.width + 40, stBounds.height + 30 });
    _menu_startButton.setOrigin(_menu_startButton.getSize() / 2.f);
    _menu_startButton.setPosition(_menu_startText.getPosition());
    _menu_startButton.setFillColor(sf::Color::Transparent);
    _menu_startButton.setOutlineThickness(3);
    _menu_startButton.setOutlineColor(sf::Color::Black);

    //this sets the text and position of the exit button
    _menu_exitText.setFont(_font);
    _menu_exitText.setString("Exit game");
    _menu_exitText.setCharacterSize(32);
    _menu_exitText.setFillColor(sf::Color::Black);

    sf::FloatRect exBounds = _menu_exitText.getLocalBounds();
    _menu_exitText.setOrigin(exBounds.width / 2, exBounds.height / 2);
    _menu_exitText.setPosition(param::game_width / 2, 600);
    _menu_exitText.setOutlineColor(sf::Color::Black);

    //This sets the position of the exit button
    _menu_exitButton.setSize({ exBounds.width + 40, exBounds.height + 30 });
    _menu_exitButton.setOrigin(_menu_exitButton.getSize() / 2.f);
    _menu_exitButton.setPosition(_menu_exitText.getPosition());
    _menu_exitButton.setFillColor(sf::Color::Transparent);
    _menu_exitButton.setOutlineThickness(3);
    _menu_exitButton.setOutlineColor(sf::Color::Black);

    //this sets the text and position of the controls button
    _menu_ControlsText.setFont(_font);
    _menu_ControlsText.setString("Controls");
    _menu_ControlsText.setCharacterSize(32);
    _menu_ControlsText.setFillColor(sf::Color::Black);

    sf::FloatRect ctBounds = _menu_ControlsText.getLocalBounds();
    _menu_ControlsText.setOrigin(ctBounds.width / 2, ctBounds.height / 2);
    _menu_ControlsText.setPosition(param::game_width / 2, 700);
    _menu_ControlsText.setOutlineColor(sf::Color::Black);

    //This sets the position of the controls button
    _menu_ControlsButton.setSize({ ctBounds.width + 40, ctBounds.height + 30 });
    _menu_ControlsButton.setOrigin(_menu_ControlsButton.getSize() / 2.f);
    _menu_ControlsButton.setPosition(_menu_ControlsText.getPosition());
    _menu_ControlsButton.setFillColor(sf::Color::Transparent);
    _menu_ControlsButton.setOutlineThickness(3);
    _menu_ControlsButton.setOutlineColor(sf::Color::Black);

    //this sets the text and position of the controls button output
    _menu_ControlsTextOutput.setFont(_font);
    _menu_ControlsTextOutput.setCharacterSize(16);
    _menu_ControlsTextOutput.setPosition(1300.f, 300.f);
    _menu_ControlsTextOutput.setString("Press A/left arrow key to move left.\nPress D/right arrow key to move right.\nPress left click to interact with the world.\nPress right click to stand on certain objects.\nPress tab to open menu.");
}

void Level1Scene::update(const float& dt) {

    //This gets the position of the mouse on the game
    sf::Vector2i mousePos = sf::Mouse::getPosition(Renderer::get_window());

    //This lets the user press tab to open up the menu page
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
        GameSystem::set_active_scene(Scenes::menu);
    }



    //this sets up the way in wich the player has to be within a certain range to interact with objects
    auto withinRange = [this](const sf::RectangleShape& target) {
        sf::Vector2f center = target.getPosition() + target.getSize() / 2.f;
        float dist = std::hypot(center.x - _playerPos.x, center.y - _playerPos.y);
        return dist <= _interactionRange;
    };

    bool leftMouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    //Checks to see if the player is in explore mode of the level
    if (_state == OutsideState::Exploring) {


        //This make it so the player input is stored and the move direction is stored so that they can move the player sprite and the stool if it is needing to be moved
        sf::Vector2f moveDir(0.f, 0.f);
        float playerInput = 0.f;
        if (!_playerOnBox)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                playerInput -= 1.f;
                moveDir.x -= 1.f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                playerInput += 1.f;
                moveDir.x += 1.f;
            }
            _playerPos += moveDir * _playerSpeed * dt;

            float halfWidth = _player.getSize().x / 2.f;
            _playerPos.x = std::clamp(_playerPos.x, halfWidth, param::game_width - halfWidth);
        }

        //keeps the player within the edges of the game 
        _playerPos.x = std::clamp(_playerPos.x, 0.0f, param::game_width - _outsidePlayer.getSize().x);

        //sets the player sprite and the blayer hit box to that to where they are meant to be visually
        _outsidePlayer.setPosition(_playerPos);
        _playerSprite.setPosition(_playerPos);

        //This makes the movement settings  of the player integrated within the physics system of the game 
        Physics::MovementSettings settings{ 450.f, 8.f, 6.f, _outsideBoxFloorY, (float)param::game_width };
        Physics::integratePlayer(dt, playerInput, settings, _outsidePlayer, _outsidePlayerVelocity);

        //This checks to see if the controls of teh stool are enabled and makes the physics start to work 
        if (_outsideBoxControlEnabled) {
            Physics::dampAndMoveStool(dt, settings.friction, _outsideBox, _outsideBoxVelocity);
            Physics::resolvePlayerStoolCollision(_outsidePlayer, _outsidePlayerVelocity, _outsideBox, _outsideBoxVelocity);
        }
        //this makes the stool stop if the stool is unselected
        else {
            _outsideBoxVelocity = { 0.f, 0.f };
        }
        //Keeps the stool within the scene game page
        Physics::clampStoolWithinScene(settings.sceneWidth, _outsideBoxFloorY, _outsideBox, _outsideBoxVelocity);

        //opens the drawer if it is clicked and within the range of the player and no other text box is open
        if (withinRange(_outsideShop) &&!_outsideLampTextVisible && !_outsideLockedMsgVisible && _outsideBoxMsgText.getString().isEmpty() && _outsideShop.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {


            _outsideShopTextVisible = true;
        }

        //closes the text box
        if (_outsideShopTextVisible && sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
            _outsideShopTextVisible = false;
        }

        //opens the picture text if it is clicked and within the range of the player and no other text box is open
        if (withinRange(_outsideLamp) && !_outsideShopTextVisible && !_outsideLockedMsgVisible && _outsideBoxMsgText.getString().isEmpty() && _outsideLamp.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

            _outsideLampTextVisible = true;
            _outsideDoorClickable = true;
        }
        //closes the text box
        if (_outsideLampTextVisible && sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
            _outsideLampTextVisible = false;
        }



        //opens the Door text if it is clicked and within the range of the player and no other text box is open
        if (withinRange(_outsideDoor) && _outsideDoor.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
            sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            //changes to the padlock if the user ahs seen the book clue
            if (_outsideDoorClickable)
            {
                std::cout << "Door clicked!" << std::endl;
                _state = OutsideState::Name;
            }
            //this shows that the door is locked if the user has not seen the book clue
            else
            {

                _outsideLockedMsgVisible = true;
            }
        }
        
        //closes the text box
        if (_outsideLockedMsgVisible && sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
        {
            _outsideLockedMsgVisible = false;
        }

    }


//Checks to see if the player is in padlock mode of the level
    else if (_state == OutsideState::Name) {
        //this adds the number pressed by the user to the code and displays it on the screen 
        for (int key = sf::Keyboard::A; key <= sf::Keyboard::Z; key++) {
            if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key) && _outsideEnteredName.size() < 4) {
                _outsideEnteredName += char('A' + (key - sf::Keyboard::A));
            }
        }

        //deletes the newest number if backspace was pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !_outsideEnteredName.empty()) {
            _outsideEnteredName.pop_back();
        }

        //Check to see if teh code is correct
        if (_outsideEnteredName == "JOHN") {

            GameSystem::set_active_scene(Scenes::level2);
        }

        _outsideLockText.setString(_outsideEnteredName);

        //chenges the mode back to explore
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
        {
            _state = OutsideState::Exploring;
        }
    }

    _BoxSprite.setPosition(_outsideBox.getPosition());
    _outsideLeftMouseDownPrev = leftMouseDown;

    Scene::update(dt);

}

//This renders all the elements of level3
void Level1Scene::render() {
    Renderer::queue(&_outsideBackground);

    Renderer::queue(&_ShopSprite);
    Renderer::queue(&_outsideShop);


    Renderer::queue(&_outsideLamp);
    Renderer::queue(&_LampSprite);




    Renderer::queue(&_outsideDoor);
    Renderer::queue(&_DoorSprite);



    Renderer::queue(&_outsidePlayer);
    Renderer::queue(&_playerSprite);



    //Checks to see if different elements of the game should be loaded in
    if (_state == OutsideState::Name) {
        Renderer::queue(&_outsideLockText);
        Renderer::queue(&_outsideLockInstr);
    }



    if (_outsideShopTextVisible) {
        Renderer::queue(&_outsideShopBox);
        Renderer::queue(&_outsideShopText);
    }

    if (_outsideLampTextVisible) {
        Renderer::queue(&_outsideLampText);
    }


    if (_outsideLockedMsgVisible)
    {
        Renderer::queue(&_outsideLockedMsgBox);
        Renderer::queue(&_outsideLockedMsgText);
    }

    if (!_outsideBoxMsgText.getString().isEmpty())
    {
        Renderer::queue(&_outsideBoxMsgText);
    }
    Scene::render();
}


void Level1Scene::load() {

    //originally sets the state to explore
    _state = OutsideState::Exploring;
    _outsideEnteredName = "";




    //Loads in all teh resources required for the level

    _outsideBgTexture.loadFromFile("resources/images/outside_background.png");
    _outsideBackground.setTexture(_outsideBgTexture);
    _outsideBackground.setScale(1920.f / _outsideBgTexture.getSize().x, 1080.f / _outsideBgTexture.getSize().y);






    if (!_playerTexture.loadFromFile("resources/images/player.png")) {
        std::cerr << "Failed to load player texture!\n";
    }

    _outsideFont.loadFromFile("resources/fonts/RobotoMono-Regular.ttf");


    //This sets all of the variables up for the drawer




    //This sets all of the variables up for the bookshelf

    _lampTexture.loadFromFile("resources/images/lamp.png");
    _LampSprite.setTexture(_lampTexture);

    _LampSprite.setScale(6.f, 6.f);
    _LampSprite.setPosition(1272.f, 608.f);

    _outsideLamp.setSize({ 120, 340 });
    _outsideLamp.setPosition(1272.f, 608.f);
    _outsideLamp.setFillColor(sf::Color(0, 0, 0, 0));


    //This sets all of the variables up for the picture

    _shopTexture.loadFromFile("resources/images/shop.png");
    _ShopSprite.setTexture(_shopTexture);

    _ShopSprite.setScale(3.f, 3.f);
    _ShopSprite.setPosition(444.f, 656.f);

    _outsideShop.setSize({ 350, 300});
    _outsideShop.setPosition(444.f, 656.f);
    _outsideShop.setFillColor(sf::Color(0, 0, 0, 0));


    //This sets all of the variables up for the door

    _DoorTexture.loadFromFile("resources/images/door_closed.png");
    _DoorSprite.setTexture(_DoorTexture);

    _DoorSprite.setScale(12.5f, 12.5f);
    _DoorSprite.setPosition(50, 550);

    _outsideDoor.setSize({ 200, 400 });
    _outsideDoor.setFillColor(sf::Color(0, 0, 0, 0));
    _outsideDoor.setPosition(50, 550);


    //This sets all of the variables up for the player
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

    _outsidePlayer.setSize({ 60, 120 });
    _outsidePlayer.setFillColor(sf::Color(0, 0, 0, 0));
    _outsidePlayer.setPosition(200, _outsideBoxFloorY - _outsidePlayer.getSize().y);
    _outsidePlayerVelocity = { 0.f, 0.f };

    _outsideBoxMsgText.setFont(_outsideFont);
    _outsideBoxMsgText.setCharacterSize(28);
    _outsideBoxMsgText.setFillColor(sf::Color::Black);
    _outsideBoxMsgText.setPosition(575, 350);


    _outsideShopBox.setSize({ 600, 200 });
    _outsideShopBox.setFillColor(sf::Color(0, 0, 0, 0));
    _outsideShopBox.setPosition(660, 300);


    _outsideShopText.setFont(_outsideFont);
    _outsideShopText.setCharacterSize(28);
    _outsideShopText.setFillColor(sf::Color::Black);
    _outsideShopText.setString("Riddle 1\nI知 the first in January and the start of a joke.\nYou値l see me at the front of a jungle,\n but I知 nowhere in a forest.\nWhat am I?\nRiddle 2\nI知 the start of open and the end of hello. \nI appear twice in door, but only once in window. \nWhat am I?");
    _outsideShopText.setPosition(700, 350);


    _outsideLampBox.setSize({ 600, 200 });
    _outsideLampBox.setFillColor(sf::Color(0, 0, 0, 0));
    _outsideLampBox.setPosition(660, 300);

    _outsideLampText.setFont(_outsideFont);
    _outsideLampText.setCharacterSize(28);
    _outsideLampText.setFillColor(sf::Color::Black);
    _outsideLampText.setString("You notice some graffiti on the lamp post \n 'H'");
    _outsideLampText.setPosition(700, 350);

    //This sets all of the variables up for the padlock
    _outsideLockText.setFont(_outsideFont);
    _outsideLockText.setCharacterSize(70);
    _outsideLockText.setFillColor(sf::Color::White);
    _outsideLockText.setPosition(800, 450);
    _outsideLockText.setString("____");

    _outsideLockInstr.setFont(_outsideFont);
    _outsideLockInstr.setCharacterSize(28);
    _outsideLockInstr.setFillColor(sf::Color::Yellow);
    _outsideLockInstr.setPosition(650, 550);
    _outsideLockInstr.setString("Enter your Name (All capital) and with a N");

    //This sets all of the variables up for the door locked message
    _outsideLockedMsgBox.setSize({ 600, 200 });
    _outsideLockedMsgBox.setFillColor(sf::Color(200, 50, 50));
    _outsideLockedMsgBox.setPosition(660, 300);

    _outsideLockedMsgText.setFont(_outsideFont);
    _outsideLockedMsgText.setCharacterSize(28);
    _outsideLockedMsgText.setFillColor(sf::Color::White);
    _outsideLockedMsgText.setString("The door is locked!");
    _outsideLockedMsgText.setPosition(700, 350);


    //clears all the sprites and bodies
    _sprites.clear();
    _bodies.clear();

    b2WorldDef world_def = b2DefaultWorldDef();
    world_def.gravity = { 0.0f, param::g };
    _world_id = b2CreateWorld(&world_def);



}

//This makes the logic of the Level3  
void Level2Scene::update(const float& dt) {

    //This gets the position of the mouse on te game
    sf::Vector2i mousePos = sf::Mouse::getPosition(Renderer::get_window());

    //this lets the user press tab to open up the menu page
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
        GameSystem::set_active_scene(Scenes::menu);
    }



    //this sets up the way in wich the player has to be within a certain range to interact with objects
    auto withinRange = [this](const sf::RectangleShape& target) {
        sf::Vector2f center = target.getPosition() + target.getSize() / 2.f;
        float dist = std::hypot(center.x - _playerPos.x, center.y - _playerPos.y);
        return dist <= _interactionRange;
    };

    bool leftMouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    //Checks to see if the player is in explore mode of the level
    if (_state == HouseState::Explore) {

        //Check to see if the stool is being interacted with
        if (withinRange(_houseStool) && leftMouseDown && !_houseLeftMouseDownPrev && !_houseNoteVisible && !_housePictureVisible && !_houseClueVisible && _houseStool.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y)) {
            _houseStoolControlEnabled = !_houseStoolControlEnabled;
            if (_houseStoolControlEnabled) {
                _houseStoolMsgText.setString("Stool selected:\nWalk into it to push toward the shelf.\nClick again to release.\nRight click to stand and get of the stool.");
            }
            else {
                _houseStoolVelocity = { 0.f, 0.f };
                _houseStoolMsgText.setString("");
            }
        }

        //this check to see if the right mouse button was pressed 
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(Renderer::get_window());

            //checks to see if the button press was on the stool
            if (_houseStool.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                //checks if the player is not on the stool thensaves the current position of the player and puts the player on top of the stool
                if (!_playerOnStool)
                {

                    _savedPlayerPos = _playerPos;

                    sf::Vector2f stoolPos = _houseStool.getPosition();
                    sf::Vector2f stoolSize = _houseStool.getSize();

                    _playerPos.x = stoolPos.x + (stoolSize.x / 40.f);
                    _playerPos.y = stoolPos.y - (_playerSprite.getGlobalBounds().height);

                    _playerSprite.setPosition(_playerPos);
                    _playerOnStool = true;
                }

                //if the stool is right clicked and the player is already on the stool the player goes back to their original position 
                else
                {
                    _playerPos = _savedPlayerPos;
                    _playerSprite.setPosition(_playerPos);
                    _playerOnStool = false;
                }
            }
        }

        //This make it so the player input is stored and the move direction is stored so that they can move the player sprite and the stool if it is needing to be moved
        sf::Vector2f moveDir(0.f, 0.f);
        float playerInput = 0.f;
        if (!_playerOnStool)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                playerInput -= 1.f;
                moveDir.x -= 1.f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                playerInput += 1.f;
                moveDir.x += 1.f;
            }
            _playerPos += moveDir * _playerSpeed * dt;

            float halfWidth = _player.getSize().x / 2.f;
            _playerPos.x = std::clamp(_playerPos.x, halfWidth, param::game_width - halfWidth);
        }

        //keeps the player within the edges of the game 
        _playerPos.x = std::clamp(_playerPos.x, 0.0f, param::game_width - _housePlayer.getSize().x);

        //sets the player sprite and the blayer hit box to that to where they are meant to be visually
        _housePlayer.setPosition(_playerPos);
        _playerSprite.setPosition(_playerPos);

        //This makes the movement settings  of the player integrated within the physics system of the game 
        Physics::MovementSettings settings{ 450.f, 8.f, 6.f, _houseStoolFloorY, (float)param::game_width };
        Physics::integratePlayer(dt, playerInput, settings, _housePlayer, _housePlayerVelocity);

        //This checks to see if the controls of teh stool are enabled and makes the physics start to work 
        if (_houseStoolControlEnabled) {
            Physics::dampAndMoveStool(dt, settings.friction, _houseStool, _houseStoolVelocity);
            Physics::resolvePlayerStoolCollision(_housePlayer, _housePlayerVelocity, _houseStool, _houseStoolVelocity);
        }
        //this makes the stool stop if the stool is unselected
        else {
            _houseStoolVelocity = { 0.f, 0.f };
        }
        //Keeps the stool within the scene game page
        Physics::clampStoolWithinScene(settings.sceneWidth, _houseStoolFloorY, _houseStool, _houseStoolVelocity);

        //opens the drawer if it is clicked and within the range of the player and no other text box is open
        if (withinRange(_houseDrawer) && !_housePictureVisible && !_houseClueVisible && _houseStoolMsgText.getString().isEmpty() && _houseDrawer.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            _houseDrawerOpenSound.play();
            _houseDrawerOpened = true;
            _houseNoteVisible = true;
        }
        
        //closes the text box
        if (_houseNoteVisible && sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
            _houseNoteVisible = false;
        }

        //opens the picture text if it is clicked and within the range of the player and no other text box is open
        if (withinRange(_housePicture) && !_houseNoteVisible && !_houseClueVisible && _houseStoolMsgText.getString().isEmpty() && _housePicture.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

            _housePictureVisible = true;
        }
        //closes the text box
        if (_housePictureVisible && sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
            _housePictureVisible = false;
        }

        //opens the book text if it is clicked and within the range of the player and no other text box is open
        if (withinRange(_houseBookshelf) && _houseDrawerOpened && !_houseNoteVisible && !_housePictureVisible && _houseStoolMsgText.getString().isEmpty() && _houseBookshelf.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            _houseBookOpenSound.play();
            _houseClueVisible = true;
        }
        //closes the text box
        if (_houseClueVisible && sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
            _houseClueVisible = false;
            _houseDoorClickable = true;
        }   


        //opens the Door text if it is clicked and within the range of the player and no other text box is open
        if (withinRange(_houseDoor) && !_houseNoteVisible && !_housePictureVisible && !_houseClueVisible && _houseStoolMsgText.getString().isEmpty() && _houseDoor.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
            sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            //changes to the padlock if the user ahs seen the book clue
            if (_houseDoorClickable)
            {
                std::cout << "Door clicked - keypad active!" << std::endl;
                _state = HouseState::Padlock;
            }
            //this shows that the door is locked if the user has not seen the book clue
            else
            {
                _houseDoorLockedSound.play();
                _houseLockedMsgVisible = true;
            }
        }
        //closes the text box
        if (_houseLockedMsgVisible && sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
        {
            _houseLockedMsgVisible = false;
        }
    }


    //Checks to see if the player is in padlock mode of the level
    else if (_state == HouseState::Padlock) {
        //this adds the number pressed by the user to the code and displays it on the screen 
        for (int key = sf::Keyboard::Num0; key <= sf::Keyboard::Num9; key++) {
            if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key) && _houseEnteredCode.size() < 4) {
                _houseEnteredCode += char('0' + (key - sf::Keyboard::Num0));
            }
        }

        //deletes the newest number if backspace was pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !_houseEnteredCode.empty()) {
            _houseEnteredCode.pop_back();
        }

        //Check to see if the code is correct
        if (_houseEnteredCode == "2334") {
            _houseDoorOpenSound.play();
            GameSystem::set_active_scene(Scenes::menu);
        }

        _housePadlockText.setString(_houseEnteredCode);

        //chenges the mode back to explore
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
        {
            _state = HouseState::Explore;
        }
    }

    _StoolSprite.setPosition(_houseStool.getPosition());
    _houseLeftMouseDownPrev = leftMouseDown;

    Scene::update(dt);

}

//This renders all the elements of level3
void Level2Scene::render() {
    Renderer::queue(&_houseBackground);
    Renderer::queue(&_DrawerLegsLeft);
    Renderer::queue(&_DrawerLegsRight);
    Renderer::queue(&_DrawerSprite);
    Renderer::queue(&_BookshelfSprite);
    Renderer::queue(&_houseBookshelf);
    Renderer::queue(&_PictureSprite);
    Renderer::queue(&_housePicture);
    Renderer::queue(&_houseDoor);
    Renderer::queue(&_housePlayer);
    Renderer::queue(&_houseStool);
    Renderer::queue(&_StoolSprite);
    Renderer::queue(&_WindowSprite);
    Renderer::queue(&_playerSprite);
    


    //Checks to see if different elements of the game should be loaded in
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
    Scene::render();
}

//This sets all of the elements to the desired position and states in level3
void Level2Scene::load() {

    //originally sets the state to explore
    _state = HouseState::Explore;
    _houseEnteredCode = "";

    


    //Loads in all teh resources required for the level

    _houseBgTexture.loadFromFile("resources/images/house_background.png");
    _houseBackground.setTexture(_houseBgTexture);
    _houseBackground.setScale(1920.f / _houseBgTexture.getSize().x, 1080.f / _houseBgTexture.getSize().y);

    if (!_furnitureTexture.loadFromFile("resources/images/FurnitureSpriteSheet.png")) {
        std::cerr << "Failed to load furniture sprite sheet!\n";
    }

    if (!_houseDoorLockedBuffer.loadFromFile("resources/audio/lockeddoor.mp3")) {
        std::cerr << "Failed to load door locked sound!\n";
    }
    _houseDoorLockedSound.setBuffer(_houseDoorLockedBuffer);

    if (!_houseDoorOpenBuffer.loadFromFile("resources/audio/opendoor.mp3")) {
        std::cerr << "Failed to load door locked sound!\n";
    }
    _houseDoorOpenSound.setBuffer(_houseDoorOpenBuffer);

    if (!_houseDrawerOpenBuffer.loadFromFile("resources/audio/draweropen.mp3")) {
        std::cerr << "Failed to load door locked sound!\n";
    }
    _houseDrawerOpenSound.setBuffer(_houseDrawerOpenBuffer);

    if (!_houseBookOpenBuffer.loadFromFile("resources/audio/bookopen.mp3")) {
        std::cerr << "Failed to load door locked sound!\n";

    }

    _houseBookOpenSound.setBuffer(_houseBookOpenBuffer);

    if (!_playerTexture.loadFromFile("resources/images/player.png")) {
        std::cerr << "Failed to load player texture!\n";
    }

    _houseFont.loadFromFile("resources/fonts/RobotoMono-Regular.ttf");


    //This sets all of the variables up for the drawer
    sf::IntRect DrawerRect(0, 0, 32, 16);

    _DrawerSprite.setTexture(_furnitureTexture);
    _DrawerSprite.setTextureRect(DrawerRect);
    _DrawerSprite.setScale(5.1f, 5.9f);
    _DrawerSprite.setPosition(444.f, 787.f);

    _DrawerLegsLeft.setSize({ 10, 90 });
    _DrawerLegsLeft.setFillColor(sf::Color(161, 101, 87));
    _DrawerLegsLeft.setPosition(460, 860);

    _DrawerLegsRight.setSize({ 10, 90 });
    _DrawerLegsRight.setFillColor(sf::Color(161, 101, 87));
    _DrawerLegsRight.setPosition(580, 860);

    _houseDrawer.setSize({ 150, 80 });
    _houseDrawer.setFillColor(sf::Color(0, 0, 0, 0));
    _houseDrawer.setPosition(450, 800);


    //This sets all of the variables up for the bookshelf
    sf::IntRect BookshelfRect(0, 18, 32, 30);

    _BookshelfSprite.setTexture(_furnitureTexture);
    _BookshelfSprite.setTextureRect(BookshelfRect);
    _BookshelfSprite.setScale(14.f, 13.5f);
    _BookshelfSprite.setPosition(1272.f, 573.f);

    _houseBookshelf.setSize({ 42, 95 });
    _houseBookshelf.setPosition( 1552, 667);
    _houseBookshelf.setFillColor(sf::Color(0, 0, 0, 0));


    //This sets all of the variables up for the picture
    _housePicture.setSize({ 100, 135 });
    _housePicture.setPosition(472, 586);
    _housePicture.setFillColor(sf::Color(0, 0, 0, 0));

    _PictureSprite.setTexture(_furnitureTexture);
    _PictureSprite.setTextureRect(sf::IntRect(38, 20, 21, 28));
    _PictureSprite.setScale(5.1f, 5.9f);
    _PictureSprite.setPosition(472, 586);


    //This sets all of the variables up for the door
    _houseDoor.setSize({ 200, 400 });
    _houseDoor.setFillColor(sf::Color(0, 0, 0, 0));
    _houseDoor.setPosition(50, 550);

    //This sets all of the variables up for the window
    _WindowSprite.setTexture(_furnitureTexture);
    _WindowSprite.setTextureRect(sf::IntRect(48, 48, 32, 16));
    _WindowSprite.setScale(13.f, 13.f);
    _WindowSprite.setPosition(1290, 300);

    //This sets all of the variables up for the player
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

    _housePlayer.setSize({ 60, 120 });
    _housePlayer.setFillColor(sf::Color(0, 0, 0, 0));
    _housePlayer.setPosition(200, _houseStoolFloorY - _housePlayer.getSize().y);
    _housePlayerVelocity = { 0.f, 0.f };

    //This sets all of the variables up for the stool
    _houseStoolPlaced = false;
    _houseStool.setSize({ 80, 80 });
    _houseStool.setFillColor(sf::Color(0, 0, 0, 0));
    _houseStool.setOutlineThickness(1);
    _houseStool.setOutlineColor(sf::Color(0, 0, 0, 0));
    _houseStool.setPosition(850, 880);
    _houseStoolFloorY = _houseStool.getPosition().y;
    _houseStoolVelocity = { 0.f, 0.f };


    _StoolSprite.setTexture(_furnitureTexture);
    _StoolSprite.setTextureRect(sf::IntRect(48, 68, 16, 12));
    _StoolSprite.setScale(5.1f, 5.9f);
    _StoolSprite.setPosition(_houseStool.getPosition());

    _houseStoolMsgText.setFont(_houseFont);
    _houseStoolMsgText.setCharacterSize(28);
    _houseStoolMsgText.setFillColor(sf::Color::Black);
    _houseStoolMsgText.setPosition(575, 350);

    //This sets all of the variables up for the note
    _houseNoteBox.setSize({ 600, 200 });
    _houseNoteBox.setFillColor(sf::Color(0, 0, 0, 0));
    _houseNoteBox.setPosition(660, 300);

    _houseNoteText.setFont(_houseFont);
    _houseNoteText.setCharacterSize(28);
    _houseNoteText.setFillColor(sf::Color::Black);
    _houseNoteText.setString("Always remember\nBlue was always my favourite.");
    _houseNoteText.setPosition(700, 350);

    //This sets all of the variables up for the book clue
;

    _houseClueText.setFont(_houseFont);
    _houseClueText.setCharacterSize(28);
    _houseClueText.setFillColor(sf::Color::Black);
    _houseClueText.setString("The book opened to page 34");
    _houseClueText.setPosition(700, 350);

    //This sets all of the variables up for the picture clue
    _housePictureBox.setSize({ 600, 200 });
    _housePictureBox.setFillColor(sf::Color(0, 0, 0, 0));
    _housePictureBox.setPosition(660, 300);

    _housePictureText.setFont(_houseFont);
    _housePictureText.setCharacterSize(28);
    _housePictureText.setFillColor(sf::Color::Black);
    _housePictureText.setString("The picture frame is empty\nthe frame has is labeled: \nFamily picture 23.");
    _housePictureText.setPosition(700, 350);

    //This sets all of the variables up for the padlock
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

    //This sets all of the variables up for the door locked message
    _houseLockedMsgBox.setSize({ 600, 200 });
    _houseLockedMsgBox.setFillColor(sf::Color(200, 50, 50));
    _houseLockedMsgBox.setPosition(660, 300);

    _houseLockedMsgText.setFont(_houseFont);
    _houseLockedMsgText.setCharacterSize(28);
    _houseLockedMsgText.setFillColor(sf::Color::White);
    _houseLockedMsgText.setString("The door is locked!");
    _houseLockedMsgText.setPosition(700, 350);


    //clears all the sprites and bodies
    _sprites.clear();
    _bodies.clear();

    b2WorldDef world_def = b2DefaultWorldDef();
    world_def.gravity = { 0.0f, param::g };
    _world_id = b2CreateWorld(&world_def);
 
}