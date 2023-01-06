#include "Bullet.hpp"
#include "GameConfig.hpp"

Bullet::Bullet(Vec2 position, Angle angle, float speed, Spaceship* parent) : 
    position(position), 
    velocity(&angle, speed),
    alive(true),
    radius(6),
    ship(parent)
{
    drawable.setRadius(radius);
    drawable.setOrigin(radius, radius);
    drawable.setFillColor(sf::Color::Green);
}
void Bullet::Update(){
    position += velocity * TIME_STEP;
}
void Bullet::Draw(sf::RenderTarget* trgt){
    drawable.setPosition(position.getVector2f());
    trgt->draw(drawable);
}