#pragma once
#include <memory>
#include "game_system.hpp"



class MenuScene : public Scene {
private:
	sf::Font _font;

	sf::Texture _menu_backgroundTex;
	sf::Sprite _menu_background;


	sf::Text _menu_title;
	sf::Text _menu_startText;
	sf::Text _menu_exitText;

	sf::RectangleShape _menu_startButton;
	sf::RectangleShape _menu_exitButton;

public:
	MenuScene() = default;
	void update(const float& dt) override;
	void render() override;
	void load() override;
};

class Level3Scene : public Scene {
private:
	enum class HouseState { Explore, Padlock };
	HouseState _state = HouseState::Explore;

	sf::Texture _houseBgTexture;
	sf::Sprite _houseBackground;
	sf::RectangleShape _houseDrawer;
	sf::RectangleShape _houseBookshelf;
	sf::RectangleShape _houseDoor;

	bool _houseDrawerOpened = false;
	bool _houseNoteVisible = false;
	bool _houseClueVisible = false;
	bool _houseDoorClickable = false;
	bool _houseLockedMsgVisible = false;

	sf::RectangleShape _houseLockedMsgBox;
	sf::Text _houseLockedMsgText;


	sf::RectangleShape _houseClueBox;
	sf::Text _houseClueText;


	sf::Font _houseFont;
	sf::Text _houseNoteText;
	sf::RectangleShape _houseNoteBox;

	std::string _houseEnteredCode;
	sf::Text _housePadlockText;
	sf::Text _housePadlockInstr;

	std::vector<sf::RectangleShape> _houseBooks;
	int _houseCorrectBookIndex = 3;

public:
	Level3Scene() = default;
	void update(const float& dt) override;
	void render() override;
	void load() override;

};

struct Scenes {
	static std::shared_ptr<Scene> menu;
	static std::shared_ptr<Scene> level3;
};