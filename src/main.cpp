#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <memory>
#include "GameConfig.hpp"
#include "Mathlib.hpp"
#include "Spaceship.hpp"
#include "Bullet.hpp"
#include "Asteroid.hpp"

float RIGHT_WALL;
float LEFT_WALL;
float UP_WALL;
float DOWN_WALL;

Vec2 FlipPosition(Vec2 position) {
    if(position.x > RIGHT_WALL){
        position.x = LEFT_WALL;
    }
    if(position.x < LEFT_WALL){
        position.x = RIGHT_WALL;
    }
    if(position.y > DOWN_WALL){
        position.y = UP_WALL;
    }
    if(position.y < UP_WALL){
        position.y = DOWN_WALL;
    }

    return position;
}

int main(void){

    //Initialize
    sf::RenderWindow window(sf::VideoMode(800,800), "NEAT-AI");
    ImGui::SFML::Init(window);
    sf::Clock game_clock;
    float accumulator{0};
    sf::Time frameTime;

    //Game objects
    std::vector<std::unique_ptr<Spaceship>> spaceships;
    std::vector<std::unique_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<Asteroid>> asteroids;

    spaceships.push_back(std::unique_ptr<Spaceship>{new Spaceship(Vec2(400,400))});

    //Gamen center position & size (width, height)
    Vec2 gameCenter(400,400);
    Vec2 gameSize(800,800);

    //Define all wall position
    RIGHT_WALL = (gameCenter.x + gameSize.x/2);
    LEFT_WALL = (gameCenter.x - gameSize.x/2);
    UP_WALL = (gameCenter.y - gameSize.y/2);
    DOWN_WALL = (gameCenter.y + gameSize.y/2);

    window.setFramerateLimit(144);
    while (window.isOpen())
    {
        //Handle time
        frameTime = game_clock.restart();
        accumulator += frameTime.asSeconds();

        //Handles event
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Updates ImGui
        ImGui::SFML::Update(window, frameTime);

        //ImGui window
        ImGui::Begin("My window");
        for(auto& ship : spaceships){
            ImGui::Text("score: %d", ship->score);
            ImGui::Text("lives: %d", ship->lives);
        }
        ImGui::End();

        //Fixed time-step update
        while (accumulator >= TIME_STEP)
        {
            for(int i = 0; i < bullets.size(); i++){
                if(!bullets[i]->alive || bullets.size() > 3){
                    bullets.erase(i + bullets.begin());
                }
            }
            for(int i = 0; i < spaceships.size(); i++){
                if(!spaceships[i]->alive){
                    spaceships.erase(i + spaceships.begin());
                }
            }
            for(int i = 0; i < asteroids.size(); i++){
                if(!asteroids[i]->alive){
                    asteroids.erase(i + asteroids.begin());
                }
            }
            

            //Update
            if(asteroids.size() == 0){
                for(int i = 0; i < 3; i++){
                    Angle randAngle(std::rand()%360);
                    Vec2 randPosition(400,400);
                    asteroids.push_back(std::unique_ptr<Asteroid>{new Asteroid(randPosition,randAngle,METEOR_SPEED,50)});
                }
            }
            for(auto& ship : spaceships){
                ship->forward = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
                ship->left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
                ship->right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
                ship->shooting = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
                ship->Update(bullets);
                ship->position = FlipPosition(ship->position);
            }
            for(auto& bullet : bullets){
                bullet->Update();
            }
            for(auto& asteroid : asteroids){
                asteroid->Update(bullets, spaceships);
                asteroid->position = FlipPosition(asteroid->position);
            }
            accumulator -= TIME_STEP;
        }
        
        //Render
        window.clear(sf::Color(100,100,100));
        for(auto& bullet : bullets){
            bullet->Draw(&window);
        }
        for(auto& ship : spaceships){
            ship->Draw(&window);
        }
        for(auto& asteroid : asteroids){
            asteroid->Draw(&window);
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    //Shut down ImGui
    ImGui::SFML::Shutdown();
}
