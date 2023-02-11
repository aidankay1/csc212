#include <cstdlib>

#include "headers/Bird.h"
#include "headers/Cat.h"
#include "headers/Dog.h"
#include "headers/Hamster.h"
#include "headers/Snake.h"
// #include "Animal.cpp"

Animal* animal_creator(std::string animal_name, float initial_hunger);

int main(int argc, char* argv[]) {
    int num_animals = strtol(argv[1], NULL, 10);
    Animal** animals = new Animal*[num_animals];

    // Create animals given user input
    for (int i = 0; i < num_animals; i++) {
        std::string animal_name;
        std::cin >> animal_name;
        animals[i] = animal_creator(animal_name, strtof(argv[i + 2], NULL));
    }

    // Make each animal perform some actions
    for (int i = 0; i < num_animals; i++) {
        animals[i]->Speak();
        std::cout << animals[i]->GetHunger() << '\n';
        animals[i]->Move();
        std::cout << '\n';
    }

    // Delete the animals
    for (int i = 0; i < num_animals; i++) {
        delete animals[i];
    }

    delete[] animals;
}

Animal* animal_creator(std::string animal_name, float initial_hunger) {
    if (animal_name == "Bird") return new Bird(initial_hunger);
    if (animal_name == "Cat") return new Cat(initial_hunger);
    if (animal_name == "Dog") return new Dog(initial_hunger);
    if (animal_name == "Hamster") return new Hamster(initial_hunger);
    if (animal_name == "Snake") return new Snake(initial_hunger);
    return nullptr;
}
