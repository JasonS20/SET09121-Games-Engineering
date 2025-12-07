#pragma once
#include <memory>
#include "game_system.hpp"
#include <vector>
#include <box2d/box2d.h>
#include <SFML/Audio.hpp>



//Creates a scene MenuScene
class MenuScene : public Scene {
//Defines all the variables in the menu scene
private:
	sf::Font _font;

	sf::Texture _menu_backgroundTex;
	sf::Sprite _menu_background;


	sf::Text _menu_title;
	sf::Text _menu_startText;
	sf::Text _menu_exitText;
	sf::Text _menu_ControlsText;
	sf::Text _menu_ControlsTextOutput;

	sf::RectangleShape _menu_startButton;
	sf::RectangleShape _menu_exitButton;
	sf::RectangleShape _menu_ControlsButton;

	bool _controlsActive = false;

public:
	MenuScene() = default;
	void update(const float& dt) override;
	void render() override;
	void load() override;
};

//Creates a scene MenuScene
class Level3Scene : public Scene {
//Defines all the variables in the menu scene
private:
	enum class HouseState { Explore, Padlock };
	HouseState _state = HouseState::Explore;

	sf::Texture _houseBgTexture;
	sf::Sprite _houseBackground;
	sf::RectangleShape _houseDrawer;
	sf::RectangleShape _houseBookshelf;
	sf::RectangleShape _housePicture;
	sf::RectangleShape _houseDoor;
	sf::RectangleShape _player;
	sf::RectangleShape _houseStool;
	sf::RectangleShape _housePlayer;
	sf::Texture _playerTexture;
	sf::Sprite _playerSprite;
	sf::Vector2f _playerPos;
	sf::Vector2f _savedPlayerPos;
	sf::Texture _furnitureTexture;
	sf::Sprite _DrawerSprite;
	sf::Sprite _BookshelfSprite;
	sf::Sprite _StoolSprite;
	sf::Sprite _PictureSprite;
	sf::Sprite _WindowSprite;
	sf::RectangleShape _DrawerLegsLeft;
	sf::RectangleShape _DrawerLegsRight;



	bool _houseStoolControlEnabled = false;
	bool _houseLeftMouseDownPrev = false;
	bool _playerOnStool = false;

	float _playerSpeed = 350.f;
	float _interactionRange = 110.f;

	bool _houseDrawerOpened = false;
	bool _houseNoteVisible = false;
	bool _houseClueVisible = false;
	bool _housePictureVisible = false;
	bool _houseDoorClickable = false;
	bool _houseLockedMsgVisible = false;
	bool _houseMovingStool = false;
	bool _houseStoolPlaced = false;
	bool _houseStoolText = false;
	float _houseStoolFloorY = 0.f;
	sf::Vector2f _houseStoolVelocity{ 0.f, 0.f };
	sf::Vector2f _housePlayerVelocity{ 0.f, 0.f };

	sf::RectangleShape _houseLockedMsgBox;
	sf::Text _houseLockedMsgText;

	sf::Text _houseStoolMsgText;
	sf::Vector2f _houseStoolDragOffset;

	sf::RectangleShape _houseClueBox;
	sf::Text _houseClueText;

	sf::SoundBuffer _houseDoorLockedBuffer;
	sf::Sound _houseDoorLockedSound;

	sf::SoundBuffer _houseDoorOpenBuffer;
	sf::Sound _houseDoorOpenSound;

	sf::SoundBuffer _houseDrawerOpenBuffer;
	sf::Sound _houseDrawerOpenSound;

	sf::SoundBuffer _houseBookOpenBuffer;
	sf::Sound _houseBookOpenSound;

	sf::Font _houseFont;
	sf::Text _houseNoteText;
	sf::RectangleShape _houseNoteBox;

	sf::Text _housePictureText;
	sf::RectangleShape _housePictureBox;

	std::string _houseEnteredCode;
	sf::Text _housePadlockText;
	sf::Text _housePadlockInstr;

	std::vector<sf::RectangleShape> _houseBooks;
	int _houseCorrectBookIndex = 3;


	b2WorldId _world_id{};
	bool _world_created = false;
	std::vector<b2BodyId> _bodies;
	std::vector<std::shared_ptr<sf::RectangleShape>> _sprites;

public:
	Level3Scene() = default;
	void update(const float& dt) override;
	void render() override;
	void load() override;




};

//Creates the Struct Scene which Holds the levels
struct Scenes {
	static std::shared_ptr<Scene> menu;
	static std::shared_ptr<Scene> level3;
};