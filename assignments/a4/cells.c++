/*
1. Counting Cells

Consider a grid of cells in two dimensions, where each cell is considered empty or filled. Any number of cells that are connected constitutes a blob. Every cell can either be connected to 4 adjacent cells (vertically, horizontally) or to 8 adjacent cells (vertically, horizontally, diagonally). The goal of your program is to recursively count the number of cells in a blob, given a starting cell.
*/
#include <iostream>

#include "cellgrid.cpp"
#include "cellgrid.h"

int main(int argc, char *argv[]) {
    // declare variables
    int M, N, row, col, conn;

    // get .txt file containing the grid
    char *fname = argv[1];

    // convert argument strings to integers
    M = atoi(argv[2]);
    N = atoi(argv[3]);
    row = atoi(argv[4]);
    col = atoi(argv[5]);
    conn = atoi(argv[6]);

    // create a Cellgrid object
    Cellgrid myGrid(fname, M, N);

    std::cout << myGrid.countCells(row, col, conn) << '\n';

    return 0;
}
