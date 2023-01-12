# NEAT AI (ASTEROID)

This project is an implementation of the **NEAT** algorithm (*NeuroEvolution of Augmenting
Topologies*) for neural networks.

The Implemented neural network will learn to play the ASTEROID game.



## Asteroid

![App Screenshot](https://via.placeholder.com/468x300?text=App+Screenshot+Here)

The game itself is simple. you are a spaceship and you have to shoot the incoming asteroid. Every time an asteroid is destroyed, you scores 100 points.


## NEAT

**NEAT** is a sepcial type of genetic algorithm, that alows the *neural network* to develop new *neurons* and new *connection* between them in it's evolution.
> *The **Neat** Algorithm can be summarize in 3 step :*
- **Speciation**
- **Crossover**
- **Mutation**

### Speciation
The **NEAT** will speciate all the created neural network during the evolution, based on their similarity with other neural net.

### Crossover
The crossover happen after the end of a generation. It will create off-spring of the current generation for each spieces by reassambling 2 parent neural net into one.

### Mutation
The mutation consist of little change in the *genom* of a neural network (*Genoms* represent how the neural net is wired).
## Appendix

This is just a pet-project made in my spare time for learning about Neural Network and how to train them.


## Tech Stack

- Language : C++
- Rendering : SFML
- GUI : Dear ImGUI

