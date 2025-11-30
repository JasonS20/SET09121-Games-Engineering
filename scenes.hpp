#pragma once
#include <memory>
#include "game_system.hpp"



class MenuScene : public Scene {
private:
	sf::Font _font;

	sf::Texture _backgroundTex;
	sf::Sprite _background;


	sf::Text _title;
	sf::Text _startText;
	sf::Text _exitText;

	sf::RectangleShape _startButton;
	sf::RectangleShape _exitButton;

public:
	MenuScene() = default;
	void update(const float& dt) override;
	void render() override;
	void load()override;
};


struct Scenes {
	static std::shared_ptr<Scene> menu;
};