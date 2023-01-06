#include "Asteroid.hpp"
#include "GameConfig.hpp"
#include "Bullet.hpp"
#include "Spaceship.hpp"
#include "Coillision.hpp"

Asteroid::Asteroid(Vec2 position, Angle angle, float speed, float radius) : 
    position(position), 
    velocity(&angle, speed),
    alive(true),
    radius(radius),
    lives(3)
{
    drawable.setRadius(radius);
    drawable.setOrigin(radius, radius);
    drawable.setPointCount(6);
    drawable.setFillColor(sf::Color(0,0,0,0));
    drawable.setOutlineThickness(5);
    drawable.setOutlineColor(sf::Color::Green);
}

void Asteroid::Update(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<Spaceship>> &spaceships){
    position += velocity * TIME_STEP;

    //Handles bullet collision
    for(auto& bullet : bullets){
        if(!alive){break;}
        if(circle_circle_collision(position,bullet->position,radius,bullet->radius)){
            bullet->alive = false;
            lives--;
            //Change color according to lives
            switch (lives)
            {
                case 3: drawable.setOutlineColor(sf::Color::Green); break;
                case 2: drawable.setOutlineColor(sf::Color::Blue); break;
                case 1: drawable.setOutlineColor(sf::Color::Red); break;
            }
            if(lives <= 0) {
                alive = false;
                bullet->ship->score += 100;
            }
        }
    }

    //Handle ship collision
    for(auto& ship : spaceships){
        if(!ship->alive || ship->hitted){continue;}
        if(circle_circle_collision(position,ship->position,radius,ship->radius)){
            ship->lives--;
            ship->hitted = true;
            if(ship->lives <= 0) {ship->alive = false;}
        }
    }
}
void Asteroid::Draw(sf::RenderTarget* trgt){
    drawable.setPosition(position.getVector2f());
    trgt->draw(drawable);
}