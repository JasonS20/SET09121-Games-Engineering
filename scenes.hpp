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
	void load()override;
};


struct Scenes {
	static std::shared_ptr<Scene> menu;
};