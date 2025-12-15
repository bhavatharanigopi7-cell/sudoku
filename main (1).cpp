#include <iostream>
using namespace std;

#define N 9   // Size of Sudoku grid

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    cout << "\nSolved Sudoku:\n\n";
    for (int row = 0; row < N; row++) {
        if (row % 3 == 0 && row != 0)
            cout << "---------------------\n";

        for (int col = 0; col < N; col++) {
            if (col % 3 == 0 && col != 0)
                cout << "| ";

            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Check if number already exists in the row
bool usedInRow(int grid[N][N], int row, int num) {
    for (int col = 0; col < N; col++) {
        if (grid[row][col] == num)
            return true;
    }
    return false;
}

// Check if number already exists in the column
bool usedInCol(int grid[N][N], int col, int num) {
    for (int row = 0; row < N; row++) {
        if (grid[row][col] == num)
            return true;
    }
    return false;
}

// Check if number already exists in the 3x3 box
bool usedInBox(int grid[N][N], int startRow, int startCol, int num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (grid[row + startRow][col + startCol] == num)
                return true;
        }
    }
    return false;
}

// Check if it's safe to place num at grid[row][col]
bool isSafe(int grid[N][N], int row, int col, int num) {
    return !usedInRow(grid, row, num) &&
           !usedInCol(grid, col, num) &&
           !usedInBox(grid, row - row % 3, col - col % 3, num);
}

// Find an empty cell in the grid
bool findEmptyLocation(int grid[N][N], int &row, int &col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0)
                return true;
        }
    }
    return false;
}

// Main Sudoku solving function using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // If no empty cell left, puzzle is solved
    if (!findEmptyLocation(grid, row, col))
        return true;

    // Try digits 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            // Recur to solve rest
            if (solveSudoku(grid))
                return true;

            // If failed, undo & try again
            grid[row][col] = 0;
        }
    }
    return false; // triggers backtracking
}

int main() {
    int grid[N][N];

    cout << "Enter the Sudoku grid (use 0 for empty cells):\n\n";

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }

    if (solveSudoku(grid)) {
        printGrid(grid);
    } else {
        cout << "\nNo solution exists for this Sudoku.\n";
    }

    return 0;
}
