#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "game_parameters.hpp"
#include "scenes.hpp"
#include "game_system.hpp"

using param = Parameters;

int main() {

    //initialises the different Scenes within the game 
   
    Scenes::menu = std::make_shared<MenuScene>();
    Scenes::menu->load();
    Scenes::level1 = std::make_shared<Level1Scene>();
    Scenes::level1->load();
    Scenes::level2 = std::make_shared<Level2Scene>();
    Scenes::level2->load();
    

    //Start the game at the menu screen
    GameSystem::set_active_scene(Scenes::menu);
    GameSystem::start(param::game_width, param::game_height, "The Awakening", param::time_step);

    return 0;
}