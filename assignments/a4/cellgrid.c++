#include "cellgrid.h"

#include <fstream>
#include <iostream>
using namespace std;

// reads a file containing 1's and 0's and the dimesnsions to expect and
// creates a Cellgrid object
Cellgrid::Cellgrid(const char *fname, int m, int n) {
    // assign row and col counters
    rows = m;
    cols = n;

    // create the grid on the heap, this will have to be deallocated later in
    // the destructor
    grid = new bool[rows * cols];

    // create a file reader stream to read data from a file
    ifstream infile;

    // open a stream to the given file
    infile.open(fname);

    // we are using row-major order in order to store this grid in 1D
    // instead of accessing grid like grid[a][b], we instead do:
    // grid[(a * number of columns) + b]
    for (int i = 0; i < rows; i++) {
        // calculate "(a * number of columns)" from above
        // in order to save some unnecessary computation
        int base = i * cols;
        for (int offset = 0; offset < cols; offset++) {
            // read data from filestream and store it in grid
            infile >> grid[base + offset];
        }
    }

    // close the filestream once we are done with it
    infile.close();
}

// destruct object where not implicit to the program
Cellgrid::~Cellgrid() {
    // since we allocated memory on the heap, we must deallocate that memory
    delete[] grid;
}

// this is the function call which will be made by the autograder to test
// your implementation for problem 1. (row, col) is the "start point" for
// counting the cells, conn is the type of connection to consider (4 or 8).
int Cellgrid::countCells(int row, int col, int conn) {
    if (!isCellFilled(row, col)) return 0;

    set<pair<int, int>> cellsInBlob;
    if (conn == 4) {
        countCellsHV(row, col, &cellsInBlob);
    } else {
        countCellsHVD(row, col, &cellsInBlob);
    }

    return cellsInBlob.size();
}

// this is the funciton call which will be made by the autograder to test
// your implementation for problem 2. conn is the type of connection
// to consider (4 or 8).
int Cellgrid::countBlobs(int conn) {
    vector<set<pair<int, int>>> blobs;

    for (int row = 1; row <= rows; row++) {
        for (int col = 1; col <= cols; col++) {
            if (!isCellFilled(row, col)) continue;
            if (isCellInBlob(row, col, &blobs)) continue;

            set<pair<int, int>> cellsInBlob;
            if (conn == 4) {
                countCellsHV(row, col, &cellsInBlob);
            } else {
                countCellsHVD(row, col, &cellsInBlob);
            }

            blobs.push_back(cellsInBlob);
        }
    }

    return blobs.size();
}

// this function prints your cellgrid in 2D format without trailing
// whitespace. Use this function to aid in debugging if you wish
void Cellgrid::print() {
    for (int i = 0; i < rows; i++) {
        int base = i * cols;
        std::cout << grid[base];
        for (int offset = 1; offset < cols; offset++) {
            std::cout << ' ' << grid[base + offset];
        }
        std::cout << '\n';
    }
}

int Cellgrid::isCellFilled(int row, int col) {
    return grid[(rows * (row - 1)) + (col - 1)];
}

bool Cellgrid::isCellOutOfBounds(int row, int col) {
    if (row < 1 || row > rows) {
        return true;
    }

    if (col < 1 || col > cols) {
        return true;
    }

    return false;
}

// count cells in blob horizontally and vertically
// two cells whose corners touch *are not* part of the same blob
void Cellgrid::countCellsHV(int row, int col, set<pair<int, int>> *cellSet) {
    // I do not know how to check surrounding cells in a 'plus' formation using a single for loop

    for (int i = row - 1; i <= row + 1; i += 2) {
        if (isCellOutOfBounds(i, col) || !isCellFilled(i, col)) continue;
        // continue if adjacent cell is already in the set
        if (cellSet->find(make_pair(i, col)) != cellSet->end()) continue;
        cellSet->insert(make_pair(i, col));
        countCellsHV(i, col, cellSet);
    }

    for (int j = col - 1; j <= col + 1; j += 2) {
        if (isCellOutOfBounds(row, j) || !isCellFilled(row, j)) continue;
        if (cellSet->find(make_pair(row, j)) != cellSet->end()) continue;
        cellSet->insert(make_pair(row, j));
        countCellsHV(row, j, cellSet);
    }
}

// count cells in blob horizontally, vertically, and diagonally
// two cells whose corners touch *are* part of the same blob
void Cellgrid::countCellsHVD(int row, int col, set<pair<int, int>> *cellSet) {
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            // continue if trying to check starting cell
            if (i == row && j == col) continue;
            if (isCellOutOfBounds(i, j) || !isCellFilled(i, j)) continue;
            // continue if adjacent cell is already in the set
            if (cellSet->find(make_pair(i, j)) != cellSet->end()) continue;
            cellSet->insert(make_pair(i, j));
            countCellsHVD(i, j, cellSet);
        }
    }
}

// check if cell is in any blob already seen while traversing grid
bool Cellgrid::isCellInBlob(int row, int col, vector<set<pair<int, int>>> *blobList) {
    for (const auto blob : *blobList) {
        for (const auto cell : blob) {
            if (cell.first == row && cell.second == col) return true;
        }
    }
    return false;
}
