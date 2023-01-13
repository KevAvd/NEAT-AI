#pragma once
#include <vector>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "Mathlib.hpp"

enum NodeType{
    Input, Output, Hidden, Bias
};

struct Connection{
    int innovationNbr;
    int in;
    int out;
    float weight;
    bool enable;
};

struct NodeLinkedList;

struct Node{
    int id;
    float value;
    Vec2 position;
    NodeType type;
    NodeLinkedList* ll_ptr; 
};

struct NodeLinkedList{
    Node* node;
    Connection* connection;
    NodeLinkedList* next{NULL};
};

class NeuralNet{
private:
    //Nodes and Connections
    std::vector<std::unique_ptr<Node>> nodes;
    std::vector<std::unique_ptr<Connection>> connections;

    //Store nodes in linkedlist for calculating the neural network's output
    std::vector<std::unique_ptr<NodeLinkedList>> ll_nodes;

    //Keep tracks of nodes 
    std::vector<Node*> inputs;
    std::vector<Node*> biases;
    std::vector<Node*> outputs;
    std::vector<Node*> hiddens;
public:
    void DecodeGenome(std::string genome);
    std::string EncodeGenome();
    void NeuralNet::ProcessInputs(float inputs[], float outputs[]);
    void NeuralNet::ComputeNode(NodeLinkedList* current);
    void Draw(sf::RenderTarget* trgt, Vec2 size, Vec2 center, float nodeRadius);
};