#ifndef _CELLGRID_H_
#define _CELLGRID_H_
#include <set>
#include <utility>
#include <vector>

class Cellgrid {
   private:
    // dimensions of the grid, think rowCount, columnCount
    int rows, cols;
    // grid will store the actual grid in 1D space
    bool *grid;
    // return value of cell at specified row, col
    int isCellFilled(int row, int col);
    // check if cell is outside grid dimensions
    bool isCellOutOfBounds(int row, int col);
    // enter filled cells horizontally and vertically into a set
    void countCellsHV(int row, int col, std::set<std::pair<int, int>> *cellSet);
    // enter filled cells horizontally, vertically, and diagonally into a set
    void countCellsHVD(int row, int col, std::set<std::pair<int, int>> *cellSet);
    // check if cell is in any blob already seen while traversing grid
    bool isCellInBlob(int row, int col, std::vector<std::set<std::pair<int, int>>> *blobList);

   public:
    /* Class constructors and destructors */
    // class constructor using a file
    Cellgrid(const char *fname, int m, int n);
    // class destructor
    ~Cellgrid();
    /* Member functions */
    // count the number of cells in grid
    int countCells(int row, int col, int conn);
    // counts the number of blobs in grid
    int countBlobs(int conn);
    // prints the Cellgrid in 2D format
    void print();
};
#endif
