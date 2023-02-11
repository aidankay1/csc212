/*
2. Counting Blobs

Consider the same grid specification from the problem above, the goal of your program now is to count the total number of blobs.
*/

#include <iostream>

#include "cellgrid.cpp"
#include "cellgrid.h"

int main(int argc, char *argv[]) {
    // declare variables
    int M, N, conn;

    // get .txt file containing the grid
    char *fname = argv[1];

    // convert argument strings to integers
    M = atoi(argv[2]);
    N = atoi(argv[3]);
    conn = atoi(argv[4]);

    // create a Cellgrid object
    Cellgrid myGrid(fname, M, N);

    std::cout << myGrid.countBlobs(conn) << '\n';

    return 0;
}
