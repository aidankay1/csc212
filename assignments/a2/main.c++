/*
Maze generation
*/

#include <iostream>
#include <string>

#include "maze.h"
// #include "maze.cpp"

int main(int argc, char **argv) {
    const size_t rng_seed = std::stoi(argv[1]);
    const size_t rows = std::stoi(argv[2]);
    const size_t cols = std::stoi(argv[3]);
    const std::string output_file_name = argv[4];

    std::srand(rng_seed);

    Maze maze = Maze(rows, cols);
    maze.Generate();
    maze.WriteToFile(output_file_name);

    return 0;
}
