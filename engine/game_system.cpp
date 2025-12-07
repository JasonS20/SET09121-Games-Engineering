#include "game_system.hpp"
#include "renderer.hpp"

std::shared_ptr<Scene> GameSystem::_active_scene = nullptr;

void GameSystem::start(unsigned int width,unsigned int height,const std::string& name,const float& time_step) {
    sf::RenderWindow window(sf::VideoMode({ width, height }), name);
    _init();
    Renderer::initialise(window);

    sf::Event event;

    while (window.isOpen()) {
        static sf::Clock clock;
        float dt = clock.restart().asSeconds();

        // Handle window events
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                clean();
                return;
            }
        }

        // Escape closes as well
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        window.clear();

        _update(dt);
        _render();

        sf::sleep(sf::seconds(time_step));  // crude frame cap
        window.display();
    }

    window.close();
    clean();
}

void GameSystem::set_active_scene(const std::shared_ptr<Scene>& act_sc) {
    _active_scene = act_sc;
}

void GameSystem::_init() {

}

void GameSystem::clean() {
    if (_active_scene) {
        _active_scene->unload();
    }
}

void GameSystem::_update(const float& dt) {
    if (_active_scene) {
        _active_scene->update(dt);
    }
    Renderer::update(dt);
}

void GameSystem::_render() {
    if (_active_scene) {
        _active_scene->render();
    }
    Renderer::render();
}
