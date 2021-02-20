#ifndef SOMETHING_PLAYER_HPP_
#define SOMETHING_PLAYER_HPP_

#include "./something_sdl.hpp"
#include "./something_v2.hpp"

enum class Direction {
    Left,
    Right,
};

struct Player {
    V2<float> pos;
    V2<float> vel;

    void render();
    void update(Seconds dt);

    void move(Direction direction);
    void stop();    
};

#endif // SOMETHING_PLAYER_HPP_
