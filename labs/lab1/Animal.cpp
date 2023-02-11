#include "headers/Animal.h"

Animal::Animal(float initial_hunger) {
    this->hunger = initial_hunger;
}

float Animal::GetHunger() {
    return this->hunger;
}

void Animal::Eat(float sustenance) {
    this->hunger += sustenance;
}

void Animal::Move() {
    if (this->hunger >= 40) {
        std::cout << "Zoom!!" << '\n';
    } else if (this->hunger >= 20) {
        std::cout << "A leisurely stroll." << '\n';
    } else {
        std::cout << "Too hungry to move..." << '\n';
    }
}
