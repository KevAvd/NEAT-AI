#include "Game.hpp"
#include "GameConfig.hpp"
#include "GuiHandler.hpp"

Game::Game(Vec2 gameSize, Vec2 gameCenter, sf::Color gamebkgrnd, Vec2 gridSize) : 
    size(gameSize),
    center(gameCenter),
    RIGHT_WALL(gameCenter.x + gameSize.x/2),
    LEFT_WALL(gameCenter.x - gameSize.x/2),
    UP_WALL(gameCenter.y - gameSize.y/2),
    DOWN_WALL(gameCenter.y + gameSize.y/2),
    background(gameSize.getVector2f()),
    grid(gridSize),
    cellSize(gameSize.x/gridSize.x,gameSize.y/gridSize.y)
{
    background.setFillColor(gamebkgrnd);
    background.setOrigin(size.x/2, size.y/2);
    background.setPosition(center.getVector2f());
}

void Game::Update(){
    RemoveDead();
    if(asteroids.size() <= 0) {SpawnAsteroid();}
    for(auto& ship : spaceships){
        ship->Update(bullets);
        ship->position = FlipPosition(ship->position, ship->radius);
    }
    for(auto& bullet : bullets){
        bullet->Update();
    }
    for(auto& asteroid : asteroids){
        asteroid->Update(bullets, spaceships);
        asteroid->position = FlipPosition(asteroid->position, asteroid->radius);
    }
}

void Game::Draw(sf::RenderTarget* trgt){
    trgt->draw(background);
    for(auto& bullet : bullets)     { bullet->Draw(trgt);   }
    for(auto& ship : spaceships)    { ship->Draw(trgt);     }
    for(auto& asteroid : asteroids) { asteroid->Draw(trgt); }
}

int Game::GetValueFromGrid(int cell){
    return GetValueFromGrid(Vec2((cell % (int)grid.x)*cellSize.x, (cell / (int)grid.x)*cellSize.y));
}

int Game::GetValueFromGrid(Vec2 cellpos){
    int value = 0b00;

    for(auto& ship : spaceships){
        Vec2 pos = ship->position;
        if(pos.x > cellpos.x && pos.x < cellpos.x + cellSize.x
        && pos.y > cellpos.y && pos.y < cellpos.y + cellSize.y)
        { value = value | 0b01; break;}
    }
    for(auto& asteroid : asteroids){
        Vec2 pos = asteroid->position;
        if(pos.x > cellpos.x && pos.x < cellpos.x + cellSize.x
        && pos.y > cellpos.y && pos.y < cellpos.y + cellSize.y)
        { value = value | 0b10; break;}
    }

    return value;
}

void Game::DrawGrid(sf::RenderTarget* trgt){
    sf::Vector2f pos(LEFT_WALL,UP_WALL);
    sf::RectangleShape cell(cellSize.getVector2f());
    cell.setOutlineThickness(1);
    cell.setOutlineColor(sf::Color::Magenta);
    for(int i = 0; i < grid.y; i++){
        for(int j = 0; j < grid.x; j++){
            cell.setPosition(pos.x+j*cellSize.x,pos.y+i*cellSize.y);
            switch (GetValueFromGrid(Vec2(cell.getPosition().x,cell.getPosition().y))){
                case 0: cell.setFillColor(sf::Color::Black); break;
                case 1: cell.setFillColor(sf::Color::Red); break;
                case 2: cell.setFillColor(sf::Color::Green); break;
                case 3: cell.setFillColor(sf::Color::Blue); break;
            }
            trgt->draw(cell);
        }
    }
}

void Game::RemoveDead(){
    for(int i = 0; i < bullets.size(); i++){
        if(!bullets[i]->alive || bullets.size() > 3){
            bullets.erase(i + bullets.begin());
        }
    }
    if(!gui_ptr->ship_invincible){
        for(int i = 0; i < spaceships.size(); i++){
            if(!spaceships[i]->alive){
                spaceships.erase(i + spaceships.begin());
            }
        }       
    }
    if(!gui_ptr->asteroid_invincible){
        for(int i = 0; i < asteroids.size(); i++){
            if(!asteroids[i]->alive){
               asteroids.erase(i + asteroids.begin());
            }
        }
    }
}

Vec2 Game::FlipPosition(Vec2 position, float radius){
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

void Game::SpawnAsteroid(){
    if(asteroids.size() == 0){
        Vec2 vectors[4] = {
            Vec2(LEFT_WALL,UP_WALL),
            Vec2(RIGHT_WALL,UP_WALL),
            Vec2(RIGHT_WALL,DOWN_WALL),
            Vec2(LEFT_WALL,DOWN_WALL)
        };
        Angle angles[4] = {
            Angle(std::rand()%90),
            Angle(std::rand()%90+90),
            Angle(std::rand()%90+180),
            Angle(std::rand()%90+270)
        };
        for(int i = 0; i < ASTEROIDS_SPAWNING_NBR; i++){
            int radius = std::rand() % 50 + 50;
            asteroids.push_back(std::unique_ptr<Asteroid>{new Asteroid(vectors[i],angles[i],METEOR_SPEED,radius)});
        }
    }
}

Spaceship* Game::AddShip(Vec2 position){
    spaceships.push_back(std::unique_ptr<Spaceship>{new Spaceship(position)});
    return spaceships[spaceships.size() - 1].get();
}