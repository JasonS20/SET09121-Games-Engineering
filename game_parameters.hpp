#pragma once

struct Parameters {
    static constexpr int game_width = 1920.f;
    static constexpr int game_height = 1080.f;
    static constexpr float time_step = 0.017f;

    static constexpr int sub_step_count = 4;
    static constexpr float g = 9.8f;
    static constexpr float physics_scale = 30.f;
    static constexpr float physics_scale_inv = 1.0f / physics_scale;
};
