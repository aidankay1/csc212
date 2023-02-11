#include <string>
#include <unordered_map>

class Cell {
   private:
    size_t row_;
    size_t col_;
    std::unordered_map<std::string, bool> walls_;

   public:
    size_t row();
    size_t col();
    std::unordered_map<std::string, bool> walls();

    bool visited;
    Cell(size_t row, size_t col);
    void RemoveWall(std::string direction);
};

#include <fstream>
#include <vector>

class Maze {
   private:
    size_t rows_;
    size_t cols_;
    std::vector<std::vector<Cell>> grid_;

   public:
    Maze(size_t rows, size_t cols);
    void Generate();
    std::vector<Cell*> GetNonvisitedNeighbors(long row, long col);
    void RemoveWalls(Cell* current, Cell* neighbor);
    void WriteToFile(std::string file_name);
    std::vector<Cell>& operator[](size_t index);
};
