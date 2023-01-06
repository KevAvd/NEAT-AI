#pragma once
#include "Mathlib.hpp"
#include "Bullet.hpp"
#include "Spaceship.hpp"

struct Asteroid{
    Vec2 position;
    Vec2 velocity;
    bool alive;
    int lives;
    float radius;
    sf::CircleShape drawable;
    Asteroid(Vec2 position, Angle angle, float speed, float radius);
    void Update(std::vector<std::unique_ptr<Bullet>> &bullets,
                std::vector<std::unique_ptr<Spaceship>> &spaceships);
    void Draw(sf::RenderTarget* trgt);
};
