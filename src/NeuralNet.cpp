#include "NeuralNet.hpp"
#include <iostream>
#include <sstream>
#include <bitset>

// Node
// - int id
// - float value
// - NodeType type

// Connection
// - int innovation_nbr
// - int in
// - int out
// - float weight
// - bool enable

// Genome
// Node => AA-AA (id, type)
// connection => AAAA-AA-AA-AAAA-A (inNbr, node in id, node out id, weight, enable)

// node    node     node     con              con
// 01-00-0:02-00-00:03-01-01:01-01-03-0000-01:02-02-03-0000-01
// The above genome represent a network of 3 nodes (2 inputs, 1 outputs) with 2 connections 
// Vizualisation:
// []-\
//     []
// []-/

void NeuralNet::DecodeGenome(std::string genome){
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
            ptr->type = (NodeType)values[1];
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

std::string NeuralNet::EncodeGenome(){
    return std::string("Not implemented");
}

void NeuralNet::ProcessInputs(float inputs[], float outputs[]){
    int counter(0);
    for(auto& node : this->inputs){
        node->value = inputs[counter];
        counter++;
    }
    counter = 0;
    for(auto& node : this->outputs){
        ComputeNode(node->ll_ptr);
        outputs[counter] = node->value;
        counter++;
    }
}

void NeuralNet::ComputeNode(NodeLinkedList* current){

    //base case : input and bias nodes values can't be changed
    if(current->node->type == NodeType::Input || current->node->type != NodeType::Bias){
        return;
    }

    //Calculate the weighted sum of all connected nodes neurones
    float sum = 0;
    while (current->next != NULL)
    {
        //Get the next connected node
        current = current->next;

        //Compute its value
        ComputeNode(current->node->ll_ptr);

        //Compute its weighted value
        if(current->connection->enable) { sum += current->node->value * current->connection->weight; }
    }
    
    //Set current node value to ReLU(sum)
    current->node->value = sum < 0.f ? 0.f : sum;
}


void NeuralNet::Draw(sf::RenderTarget* trgt, Vec2 size, Vec2 center, float nodeRadius){
    Vec2 input(
        center.x - size.x/2.f + nodeRadius,
        center.y - size.y/2.f + nodeRadius
    );
    Vec2 in_delta(
        0.f,
        size.y / ((float)inputs.size() + 1.f)
    );
    Vec2 output(
        center.x + size.x/2.f - nodeRadius,
        center.y - size.y/2.f + nodeRadius
    );
    Vec2 out_delta(
        0.f,
        size.y / ((float)outputs.size() + 1.f)
    );
    Vec2 bias(
        center.x - size.x/2.f + nodeRadius*3,
        center.y - size.y/2.f + nodeRadius
    );
    Vec2 bias_delta(
        0.f,
        size.y / ((float)biases.size() + 1.f)
    );
    Vec2 hidden_circle(
        center.x,
        center.y + nodeRadius*2
    );
    float hidden_radius(size.x/2.f - nodeRadius*2);
    Angle current_angle(0);
    current_angle.in_range = true;
    Angle delta_angle(360.f / (float)hiddens.size());

    for(auto& node : inputs){
        node->position = input;
        input += in_delta;
    }

    for(auto& node : outputs){
        node->position = output;
        output += out_delta;
    }

    for(auto& node : biases){
        node->position = bias;
        bias += bias_delta;
    }

    for(auto& node : hiddens){
        node->position = hidden_circle + Vec2(&current_angle, hidden_radius);
        current_angle.SetDegree(current_angle.GetDegree() + delta_angle.GetDegree());
    }

    for(auto& node : nodes){
        sf::CircleShape shape(nodeRadius);
        shape.setPosition(node->position.getVector2f());
        trgt->draw(shape);
    }
}