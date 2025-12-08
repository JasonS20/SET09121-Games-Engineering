#include "renderer.hpp"
#include <queue>

static std::queue<const sf::Drawable*> draw_queue;
static sf::RenderWindow* rw;

void Renderer::initialise(sf::RenderWindow& r) { rw = &r; }

sf::RenderWindow& Renderer::get_window() { return *rw; }

void Renderer::shutdown() {
    while (!draw_queue.empty())
        draw_queue.pop();
}

void Renderer::update(const float&) {}

void Renderer::render() {
    if (rw == nullptr) {
        throw("No render window set! ");
    }
    while (!draw_queue.empty()) {
        rw->draw(*draw_queue.front());
        draw_queue.pop();
    }
}

void Renderer::queue(const sf::Drawable* s) { draw_queue.push(s); }