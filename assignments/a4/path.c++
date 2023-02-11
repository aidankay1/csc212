/*
3. Finding a Good Path

Given a 2-dimensional grid representing elevations of a map, determine the lowest and highest points and whether there is a path between them that never goes down. This problem is a slightly modified version of one of the problems in the BOSPRE 2018 competition.
*/

/*

- loop through 2D vector, finding highest and lowest elevation
- start at lowest elevation and recursively search for a path in N, E, S, W order
    - if highest elev found, return true
    - if all directions have been exhausted, return false and backtrack

*/

#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using Matrix = std::vector<std::vector<int>>;
struct Point {
    int row, col;
    Point(){};
    Point(int row, int col) : row(row), col(col) {}
};
using Path = std::vector<Point>;

Matrix FillMatrix(char*, int, int);
void FindHighestLowestPoints(Matrix*, Point*, Point*);
Path FindPath(Matrix*, Point, Point);
bool BuildPath(int, int, Matrix*, Path*, Path*, Point);
bool PointAlreadyChecked(Point, Path*);
void PrintPoints(Path*);

int main(int argc, char** argv) {
    char* filename = argv[1];
    int rows = std::stoi(argv[2]);
    int cols = std::stoi(argv[3]);

    Matrix elevation_map = FillMatrix(filename, rows, cols);

    Point highest, lowest;
    FindHighestLowestPoints(&elevation_map, &highest, &lowest);

    std::cout << lowest.row + 1 << ' ' << lowest.col + 1 << ' ' << highest.row + 1 << ' ' << highest.col + 1 << ' ';

    Path path = FindPath(&elevation_map, highest, lowest);

    if (path.empty()) {
        std::cout << "no\n";
    } else {
        std::cout << "yes\n";
    }
}

// Fill matrix from .txt file
Matrix FillMatrix(char* filename, int rows, int cols) {
    Matrix elevation_map(rows, std::vector<int>(cols));

    std::ifstream file(filename);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int n;
            file >> n;
            elevation_map[i][j] = n;
        }
    }

    file.close();
    return elevation_map;
}

// Find coordinates of highest and lowest points in the matrix
void FindHighestLowestPoints(Matrix* elevation_map, Point* hi, Point* lo) {
    int highest = 0, lowest = INT32_MAX;

    for (int row = 0; row < elevation_map->size(); row++) {
        for (int col = 0; col < elevation_map->at(0).size(); col++) {
            int val = elevation_map->at(row).at(col);

            if (val > highest) {
                highest = val;
                hi->row = row;
                hi->col = col;
            }

            if (val < lowest) {
                lowest = val;
                lo->row = row;
                lo->col = col;
            }
        }
    }
}

// Finds a path from the lowest to the highest point, if one exists
Path FindPath(Matrix* m, Point highest, Point lowest) {
    Path path, checked_points;

    // If BuildPath successfully constructs a path, return it
    if (BuildPath(lowest.row, lowest.col, m, &path, &checked_points, highest)) return path;

    // Otherwise, return an empty path
    path.clear();
    return path;
}

// Inspect each of the four (or fewer if the point touches an edge of the matrix) surrounding points.
// If one of these points has a greater elevation, add it to the path and recurse until the highest point is found.
// Otherwise, backtrack.
bool BuildPath(int row, int col, Matrix* elevation_map, Path* path, Path* checked_points, Point highest) {
    // PrintPoints(checked_points);
    // std::cout << checked_points->size() << '\n';
    
    if (row == highest.row && col == highest.col) {
        return true;
    }

    // if (PointAlreadyChecked(Point(row, col), checked_points)) return false;

    const int current_elevation = elevation_map->at(row).at(col);

    // Build map of surrounding points
    const std::map<std::string, Point> directions = {
        {"north", Point(row - 1, col)},
        {"east", Point(row, col + 1)},
        {"south", Point(row + 1, col)},
        {"west", Point(row, col - 1)}};

    // Attempt to build the path out in each cardinal direction
    for (const auto& direction : directions) {
        const auto point = direction.second;
        try {
            if (elevation_map->at(point.row).at(point.col) >= current_elevation && !PointAlreadyChecked(point, checked_points)) {
                path->push_back(point);
                checked_points->push_back(point);
                if (BuildPath(point.row, point.col, elevation_map, path, checked_points, highest)) return true;
                path->pop_back();
            }
        } catch (const std::out_of_range& e) {
            // Skip if no point exists in this direction
            // No handling needed because the error (if one occurs) will throw during the if conditional, before any actual code runs
        }
    }

    // If none of these directions work, return false to backtrack
    return false;
}

// Check if BuildPath() has already been called on a certain point (prevents recursive stack overflows)
bool PointAlreadyChecked(Point point, Path* checked_points) {
    for (const auto& checked_point : *checked_points) {
        if (point.row == checked_point.row && point.col == checked_point.col) {
            return true;
        }
    }
    return false;
}

void PrintPoints(Path *path) {
    for (const auto &point : *path) {
        std::cout << "(" << point.row << ", " << point.col << ")" << " ";
    }
    std::cout << '\n';
}
