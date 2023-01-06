#pragma once
#include "Mathlib.hpp"

struct Spaceship;

struct Bullet{
    Vec2 position;
    Vec2 velocity;
    bool alive;
    float radius;
    sf::CircleShape drawable;
    Spaceship* ship;
    Bullet(Vec2 position, Angle angle, float speed, Spaceship* parent);
    void Update();
    void Draw(sf::RenderTarget* trgt);
};