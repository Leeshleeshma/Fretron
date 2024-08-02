#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Function to initialize the grid
void initializeGrid(vector<vector<char>>& grid, int width, int height) {
    grid.assign(height, vector<char>(width, '.'));
}

// Function to draw a path on the grid
void drawPath(vector<vector<char>>& grid, const vector<pair<int, int>>& path, char symbol) {
    for (const auto& point : path) {
        int x = point.first;
        int y = point.second;
        if (x >= 0 && x < grid[0].size() && y >= 0 && y < grid.size()) {
            grid[y][x] = symbol;
        }
    }
}

// Function to print the grid
void printGrid(const vector<vector<char>>& grid) {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            cout << cell << ' ';
        }
        cout << endl;
    }
}

int main() {
    int width = 10; // Width of the grid
    int height = 10; // Height of the grid

    vector<vector<char>> grid;
    initializeGrid(grid, width, height);

    // Define flight paths
    vector<vector<pair<int, int>>> flights = {
        {{1, 1}, {2, 2}, {3, 3}}, // Flight 1
        {{1, 1}, {2, 4}, {3, 2}}, // Flight 2
        {{1, 1}, {4, 2}, {3, 4}}  // Flight 3
    };

    // Draw each flight path
    char flightSymbols[] = {'1', '2', '3'};
    for (size_t i = 0; i < flights.size(); ++i) {
        drawPath(grid, flights[i], flightSymbols[i]);
    }

    // Print the grid
    printGrid(grid);

    return 0;
}
