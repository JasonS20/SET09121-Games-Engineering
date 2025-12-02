#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

class Scene {
public:
    virtual ~Scene() = default;

    // Default implementations are inline here, so they DO have bodies.
    virtual void update(const float& dt) {}
    virtual void render() {}
    virtual void load() {}
    virtual void unload() {}
};

class GameSystem {
public:
    // Main game loop
    static void start(unsigned int width,
        unsigned int height,
        const std::string& name,
        const float& time_step);

    // Switch which scene is currently active
    static void set_active_scene(const std::shared_ptr<Scene>& act_sc);

    // (Optional) getter if you need it later
    static std::shared_ptr<Scene> get_active_scene() { return _active_scene; }

private:
    static std::shared_ptr<Scene> _active_scene;

    static void _init();
    static void clean();
    static void _update(const float& dt);
    static void _render();
};
