#pragma once
#include <SFML/Graphics.hpp>
#include "Mathlib.hpp"

struct Bullet;

struct Spaceship{
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;
    Angle rotation;
    float radius;
    float cooldown;
    float inv_cooldown;
    int lives;
    int score;
    bool alive;
    bool forward;
    bool left;
    bool right;
    bool shooting;
    bool hitted;
    sf::CircleShape drawable;
    float turn_rate;
    Spaceship(Vec2 position);
    void Update(std::vector<std::unique_ptr<Bullet>> &bullets);
    void Draw(sf::RenderTarget* trgt);  
};