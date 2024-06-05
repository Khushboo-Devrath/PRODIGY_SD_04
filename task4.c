#include <stdio.h>
#include <stdbool.h>

// Define the size of the Sudoku grid
#define N 9

// Function prototypes
bool solveSudoku(int grid[N][N]);
bool isSafe(int grid[N][N], int row, int col, int num);
bool findUnassignedLocation(int grid[N][N], int *row, int *col);
void printGrid(int grid[N][N]);

int main() {
    int grid[N][N];

    // Prompt the user to enter the Sudoku puzzle
    printf("Enter the Sudoku puzzle (use 0 for empty cells):\n");
    int i;
    for ( i = 0; i < N; i++) {
    	int j;
        for (j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    if (solveSudoku(grid)) {
        printf("Solved Sudoku grid:\n");
        printGrid(grid);
    } else {
        printf("No solution exists\n");
    }

    return 0;
}

// Function to find an unassigned location in the grid
bool findUnassignedLocation(int grid[N][N], int *row, int *col) {
    for (*row = 0; *row < N; (*row)++) {
        for (*col = 0; *col < N; (*col)++) {
            if (grid[*row][*col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Function to check if num can be placed in grid[row][col]
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if num is not in the current row and column
    int x;
    for ( x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    // Check if num is not in the current 3x3 box
    int startRow = row - row % 3, startCol = col - col % 3;
    int i;
    for (i = 0; i < 3; i++) {
    	int j;
        for (j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // If there is no unassigned location, we are done
    if (!findUnassignedLocation(grid, &row, &col)) {
        return true;
    }

    // Consider digits 1 to 9
    int num;
    for (num = 1; num <= 9; num++) {
        // If it is safe to place num in grid[row][col]
        if (isSafe(grid, row, col, num)) {
            // Make the assignment
            grid[row][col] = num;

            // Return if the assignment leads to a solution
            if (solveSudoku(grid)) {
                return true;
            }

            // Failure, unmake the assignment
            grid[row][col] = 0;
        }
    }

    return false;  // This triggers backtracking
}

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
	int row;
    for ( row = 0; row < N; row++) {
    	int col;
        for (col = 0; col < N; col++) {
            printf("%2d ", grid[row][col]);
        }
        printf("\n");
    }
}

