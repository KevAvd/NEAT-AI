#include "NeuralNet.hpp"
#include <iostream>
#include <sstream>
#include <bitset>

// Node
// - int id
// - int layer
// - float input
// - float output
// - NodeType type

// Connection
// - int innovation_nbr
// - int in
// - int out
// - float weight
// - bool enable

// Genome
// Node => AA-AA-A (id, layer, type)
// connection => AAAA-AA-AA-AAAA-A (inNbr, node in id, node out id, weight, enable)

// node    node     node     con              con
// 01-00-0:02-00-00:03-01-01:01-01-03-0000-01:02-02-03-0000-01
// The above genome represent a network of 3 nodes (2 inputs, 1 outputs) with 2 connections 
// Vizualisation:
// []-\
//     []
// []-/

void NeuralNet::decodeGenome(std::string genome){
    // std::cout << genome << std::endl << std::endl;
    std::string endSymbol(":&$end$&");
    genome.append(endSymbol);
    size_t begin(0);
    size_t end(genome.find(endSymbol));
    size_t index(genome.find(":"));
    std::string substr;

    while (index < end)
    {
        substr = genome.substr(0,index);
        genome.erase(0,index+1);
        std::string subs[]{"","","","",""};
        int subIndex = 0;
        for(int i = 0; i < substr.length(); i++){
            if(substr.at(i) == '-' && subIndex + 1 < 5){
                subIndex++;
                subs[subIndex] += substr.at(++i);
            } else {
                subs[subIndex] += substr.at(i);
            }
        }
        int count = 0;
        int values[5];
        for(int i = 0; i < 5; i++){
            if(subs[i] != ""){
                std::cout << subs[i] << std::endl;
                std::string s = subs[i];
                std::stringstream ss;
                ss << std::hex << s;
                unsigned n;
                ss >> n;
                count++;
            }
        }
        if(count == 3){
            nodes.push_back(std::unique_ptr<Node>{new Node});
            auto it = nodes.end();
            it--;
            Node* ptr = (*it).get();
            ptr->id = values[0];
            ptr->layer = values[1];
            ptr->type = (NodeType)values[2];
        }
        if(count == 5){
            connections.push_back(std::unique_ptr<Connection>{new Connection});
            auto it = connections.end();
            it--;
            Connection* ptr = (*it).get();
            ptr->innovationNbr = values[0];
            ptr->in = values[1];
            ptr->out = values[2];
            ptr->weight = values[3];
            ptr->enable = values[4];
        }
        std::cout << std::endl;
        index = genome.find(":");
    }

    
}

std::string NeuralNet::encodeGenome(){
    return std::string("Not implemented");
}

void NeuralNet::processInputs(float inputs[]){

}

void NeuralNet::drawNet(sf::RenderTarget* trgt, Vec2 size, Vec2 center, float nodeRadius){
    int layerNbr = layers.size();
    float start_x = center.x - size.x/2.f + nodeRadius;
    float end_x = center.x + size.x/2.f - nodeRadius;
    float delta_x = (end_x - start_x) / (float)layerNbr;
    float crnt_x(start_x);
    float start_y = center.y - size.y/2.f + nodeRadius;
    float end_y = center.y + size.y/2.f - nodeRadius;
    float delta_y;
    float crnt_y(start_y);
    sf::CircleShape nodeShape(nodeRadius);
    nodeShape.setOrigin(nodeRadius, nodeRadius);
    for(int i = 0; i < layerNbr; i++){
        delta_y = (end_y - start_y) / layers[i].size();
        for(int j = 0; j < layers[i].size(); j++){
            nodeShape.setPosition(crnt_x, crnt_y);
            crnt_y += delta_y;
            trgt->draw(nodeShape); 
        }
        crnt_x += delta_x;
    }
}