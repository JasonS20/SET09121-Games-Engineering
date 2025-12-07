#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "game_parameters.hpp"
#include "scenes.hpp"
#include "game_system.hpp"

using param = Parameters;

int main() {
   
    Scenes::menu = std::make_shared<MenuScene>();
    Scenes::menu->load();
    Scenes::level3 = std::make_shared<Level3Scene>();
    Scenes::level3->load();


    GameSystem::set_active_scene(Scenes::menu);
    GameSystem::start(param::game_width, param::game_height, "Awakening", param::time_step);

    return 0;
}