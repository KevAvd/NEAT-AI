#pragma once
#include <SFML/Graphics.hpp>
#include "Spaceship.hpp"
#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Mathlib.hpp"
#include "GuiHandler.hpp"

class Game{
private:
    std::vector<std::unique_ptr<Spaceship>> spaceships;
    std::vector<std::unique_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<Asteroid>> asteroids;
    Vec2 center;
    Vec2 size;
    Vec2 grid;
    Vec2 cellSize;
    sf::RectangleShape background;
    float RIGHT_WALL;
    float LEFT_WALL;
    float UP_WALL;
    float DOWN_WALL;
public:
    GUI* gui_ptr;
    Game(Vec2 gameSize, Vec2 gameCenter, sf::Color gamebkgrnd, Vec2 gridSize);
    void Update();
    void Draw(sf::RenderTarget* trgt);
    void DrawGrid(sf::RenderTarget* trgt);
    int GetValueFromGrid(int cell);
    int GetValueFromGrid(Vec2 cellpos);
    void RemoveDead();
    Vec2 FlipPosition(Vec2 position, float radius);
    void SpawnAsteroid();
    Spaceship* AddShip(Vec2 position);
};