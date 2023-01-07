#include "Spaceship.hpp"
#include "Bullet.hpp"
#include "GameConfig.hpp"

Spaceship::Spaceship(Vec2 position) : 
    velocity(),
    position(position),
    acceleration(),
    rotation(),
    radius(50),
    cooldown(SPACESHIP_COOLDOWN),
    lives(3),
    alive(true),
    forward(false),
    left(false),
    right(false),
    shooting(false),
    drawable(),
    turn_rate(180),
    inv_cooldown(0),
    hitted(false),
    score(0)
{
    drawable.setOrigin(sf::Vector2f(radius,radius));
    drawable.setPointCount(3);
    drawable.setRadius(radius);
}

void Spaceship::Update(std::vector<std::unique_ptr<Bullet>> &bullets){

    if(hitted){
        inv_cooldown += TIME_STEP;

        drawable.setFillColor(sf::Color(255,0,0,70));

        if(inv_cooldown >= INVINCIBLE_COOLDOWN){
            hitted = false;
            inv_cooldown = 0;
            drawable.setFillColor(sf::Color(255,255,255,255));
        }
    }

    //Handle controls
    if(forward){
        acceleration = Vec2(&rotation,SPACESHIP_ACCELERATION);
    }
    if(left){
        rotation.SetDegree(rotation.GetDegree() - turn_rate * TIME_STEP);
    }
    if(right){
        rotation.SetDegree(rotation.GetDegree() + turn_rate * TIME_STEP);
    }
    if(shooting && cooldown <= 0 & !hitted){
        cooldown = SPACESHIP_COOLDOWN;
        bullets.push_back(std::unique_ptr<Bullet>{new Bullet(position,rotation,BULLET_SPEED, this)});
    }

    //Remove delta time from cooldown
    cooldown -= TIME_STEP;

    //Update position
    velocity += acceleration * TIME_STEP;
    position += velocity * TIME_STEP;
    acceleration = {};
}

void Spaceship::Draw(sf::RenderTarget* trgt){
    drawable.setPosition(position.getVector2f());
    drawable.setRotation(rotation.GetDegree() + 90);
    trgt->draw(drawable);
}