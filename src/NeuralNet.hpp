#pragma once
#include <vector>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "Mathlib.hpp"

enum NodeType{
    Input, Output, Hidden, Bias
};

struct Node{
    int id;
    int layer;
    float inputs;
    float outputs;
    NodeType type;
};

struct Connection{
    int innovationNbr;
    int in;
    int out;
    float weight;
    bool enable;
};

struct NodeConMap{
    Node* node;
    std::vector<Connection*> connections;
};

class NeuralNet{
private:
    std::vector<std::unique_ptr<Node>> nodes;
    std::vector<std::unique_ptr<Connection>> connections;
    std::vector<std::unique_ptr<NodeConMap>> nodeConMaps;
    std::vector<std::vector<NodeConMap*>> layers;
public:
    //Decode the genome from string to struct Node/Connection stored in vectors
    //Map each node with his previous layer connections
    //sort node maps according to their layer position
    void decodeGenome(std::string genome);

    //Encode the neural net genome into a string
    std::string encodeGenome();

    //Go through list of node maps and process outputs of each nodes
    void processInputs(float inputs[]);

    //Draw the neural net 
    void drawNet(sf::RenderTarget* trgt, Vec2 size, Vec2 center);
};