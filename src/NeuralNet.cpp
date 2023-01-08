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
    float nbr = 15.123f;
    int* ptr1 = (int*)&nbr;
    int val = *ptr1;
    std::bitset<32> floatBit(val);
    std::cout << floatBit.to_string() << std::endl;
    float* ptr = (float*) &floatBit;
    std::cout << *ptr << std::endl;
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
        for(int i = 0; i < 5; i++){
            if(subs[i] != ""){
                std::cout << subs[i] << std::endl;
                // std::string s = subs[i];
                // std::stringstream ss;
                // ss << std::hex << s;
                // unsigned n;
                // ss >> n;
                // std::bitset<8> b(n);
                // std::cout << b.to_string() << std::endl;
            }
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

void NeuralNet::drawNet(sf::RenderTarget* trgt, Vec2 size, Vec2 center){

}