#include <iostream>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

int main(void){

    //Create window
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML & ImGui works !");

    //Init ImGui for SFML
    ImGui::SFML::Init(window);

    //Create a shape
    float radius = 100.f;
    float colors[3];
    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(sf::Vector2f(400,400));

    //Create a clock
    sf::Clock deltaClock;

    //Gameloop
    while (window.isOpen())
    {
        //Handles event
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Update ImGui
        ImGui::SFML::Update(window, deltaClock.restart());

        //Set a ImGui window
        ImGui::Begin("My Window 1");
        ImGui::SliderFloat("Radius", &radius,0.f,1000.f);
        ImGui::ColorPicker3("Shape Color", colors);
        ImGui::End();

        //Update Shape
        shape.setRadius(radius);
        shape.setFillColor(sf::Color(colors[0]*255,colors[1]*255,colors[2]*255,255));
        shape.setOrigin(sf::Vector2f(radius,radius));

        //Render
        window.clear();
        window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    //Shut down ImGui
    ImGui::SFML::Shutdown();
    return 0;
}