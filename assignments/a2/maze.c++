#include "maze.h"

// Cell implementation
// ---------------------------------------------------------------------------

Cell::Cell(size_t row, size_t col) {
    row_ = row;
    col_ = col;
    visited = false;
    walls_ = {
        {"north", true},
        {"south", true},
        {"east", true},
        {"west", true}};
}

size_t Cell::row() {
    return row_;
}

size_t Cell::col() {
    return col_;
}

std::unordered_map<std::string, bool> Cell::walls() {
    return walls_;
}

void Cell::RemoveWall(std::string direction) {
    walls_[direction] = false;
}

// Maze implementation
// ---------------------------------------------------------------------------

Maze::Maze(size_t rows, size_t cols) {
    rows_ = rows;
    cols_ = cols;

    for (size_t row = 0; row < rows; row++) {
        std::vector<Cell> grid_row;

        for (size_t col = 0; col < cols; col++) {
            grid_row.push_back(Cell(row, col));
        }

        grid_.push_back(grid_row);
    }
}

void Maze::Generate() {
    std::vector<Cell*> maze_path;

    grid_[0][0].RemoveWall("north");
    grid_[rows_ - 1][cols_ - 1].RemoveWall("south");
    
    grid_[0][0].visited = true;
    maze_path.push_back(&grid_[0][0]);

    while (!maze_path.empty()) {
        Cell* current = maze_path.back();
        maze_path.pop_back();

        std::vector<Cell*> nonvisited_neighbors = GetNonvisitedNeighbors(current->row(), current->col());

        if (!nonvisited_neighbors.empty()) {
            maze_path.push_back(current);
            size_t idx = std::rand() / ((RAND_MAX + 1u) / nonvisited_neighbors.size());
            Cell* random_neighbor = nonvisited_neighbors[idx];
            RemoveWalls(current, random_neighbor);
            random_neighbor->visited = true;
            maze_path.push_back(random_neighbor);
        }
    }
}

std::vector<Cell*> Maze::GetNonvisitedNeighbors(long row, long col) {
    std::vector<Cell*> vec;

    if (row - 1 >= 0 && !grid_[row - 1][col].visited) {
        vec.push_back(&grid_[row - 1][col]);
    }

    if (row + 1 < rows_ && !grid_[row + 1][col].visited) {
        vec.push_back(&grid_[row + 1][col]);
    }

    if (col + 1 < cols_ && !grid_[row][col + 1].visited) {
        vec.push_back(&grid_[row][col + 1]);
    }

    if (col - 1 >= 0 && !grid_[row][col - 1].visited) {
        vec.push_back(&grid_[row][col - 1]);
    }

    // if (row - 1 >= 0) {
    //     // Nested if statements necessary to avoid accessing out-of-bounds memory
    //     if (!grid_[row - 1][col].visited) {
    //         vec.push_back(&grid_[row - 1][col]);
    //     }
    // }

    // if (row + 1 < rows_) {
    //     if (!grid_[row + 1][col].visited) {
    //         vec.push_back(&grid_[row + 1][col]);
    //     }
    // }

    // if (col + 1 < cols_) {
    //     if (!grid_[row][col + 1].visited) {
    //         vec.push_back(&grid_[row][col + 1]);
    //     }
    // }

    // if (col - 1 >= 0) {
    //     if (!grid_[row][col - 1].visited) {
    //         vec.push_back(&grid_[row][col - 1]);
    //     }
    // }

    return vec;
}

void Maze::RemoveWalls(Cell* current, Cell* neighbor) {
    if (neighbor->row() == current->row() - 1) {
        current->RemoveWall("north");
        neighbor->RemoveWall("south");
    }

    if (neighbor->row() == current->row() + 1) {
        current->RemoveWall("south");
        neighbor->RemoveWall("north");
    }

    if (neighbor->col() == current->col() + 1) {
        current->RemoveWall("east");
        neighbor->RemoveWall("west");
    }

    if (neighbor->col() == current->col() - 1) {
        current->RemoveWall("west");
        neighbor->RemoveWall("east");
    }
}

void Maze::WriteToFile(std::string file_name) {
    std::ofstream file(file_name);

    for (auto& row : grid_) {
        for (auto& cell : row) {
            unsigned short bitstring = 0;
            auto walls = cell.walls();

            if (walls["north"]) bitstring += 0b1000;
            if (walls["south"]) bitstring += 0b0100;
            if (walls["east"]) bitstring += 0b0010;
            if (walls["west"]) bitstring += 0b0001;

            file << bitstring;
            if (&cell == &row.back()) break;
            file << ' ';
        }
        if (&row == &grid_.back()) break;
        file << '\n';
    }
}

std::vector<Cell>& Maze::operator[](size_t index) {
    return grid_[index];
}
