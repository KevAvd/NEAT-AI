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
#include "GuiHandler.hpp"
#include "Game.hpp"

int main(void){

    //Initialize
    sf::RenderWindow window(sf::VideoMode(1920,1080), "NEAT-AI", sf::Style::Fullscreen);
    ImGui::SFML::Init(window);
    sf::Clock game_clock;
    float accumulator{0};
    sf::Time frameTime;
    GUI myGUI;
    Game myGame(Vec2(800,800), Vec2(400+100,1080/2), sf::Color(100,100,100), Vec2(GRID_X,GRID_Y));
    myGame.gui_ptr = &myGUI;
    Spaceship* myShip = myGame.AddShip(Vec2(400+100,1080/2));
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

        //Window here
        myGUI.AI_WINDOW();
        myGUI.GAMEOBJ_WINDOW();

        //Fixed time-step update
        while (accumulator >= TIME_STEP)
        {
            //Handle controls
            myShip->forward     = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up      );
            myShip->left        = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left    );
            myShip->right       = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right   );
            myShip->shooting    = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space   );

            myGame.Update();
            accumulator -= TIME_STEP;
        }
        
        //Render
        window.clear(sf::Color(30,30,30));
        if(myGUI.ai_vision) {
            myGame.DrawGrid(&window);
        } else {
            myGame.Draw(&window);
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    //Shut down ImGui
    ImGui::SFML::Shutdown();
}
