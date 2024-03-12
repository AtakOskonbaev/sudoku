#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;

const int N = 9; // grid size

void greeting()
{
    cout << "\t\t\t<================================================================================>" << endl;
    cout << "\t\t\t|                        WELCOME TO SUDOKU Game!                                 |" << endl;
    cout << "\t\t\t|       Fill in the missing numbers to solve the puzzle.                         |" << endl;
    cout << "\t\t\t<================================================================================>" << endl;
}

int difficultyLevel()
{
    int difficulty;
    cout << "Choose difficulty level:" << endl;
    cout << "1. Easy" << endl;   // hide 20 elements
    cout << "2. Medium" << endl; // hide 30 elements
    cout << "3. Hard" << endl;   // hide 45 elements

    while (true)
    {
        cout << "Enter your choice: ";
        cin >> difficulty;

        if (difficulty >= 0 && difficulty <= 3)
            break; // Valid input, exit the loop
        else
        {
            cout << "Invalid input. Please enter a number between 1 and 3." << endl;
            cin.clear();
        }
    }

    return difficulty;
}

void printGrid(vector<vector<int>> &grid)
{
    cout << "     ";
    for (int k = 0; k < N; k++)
    {
        cout << k + 1 << "  ";
        if ((k + 1) % 3 == 0 && k != 8)
        {
            cout << "|  ";
        }
    }
    cout << endl
         << "   ------------------------------------" << endl;
    for (int i = 0; i < N; ++i)
    {
        cout << i + 1 << "  | ";
        for (int j = 0; j < N; ++j)
        {

            cout << grid[i][j] << "  ";
            if ((j + 1) % 3 == 0)
            {
                cout << "|  ";
            }
            if ((i + 1) % 3 == 0 && j == 8)
            {
                cout << endl
                     << "   ------------------------------------";
            }
        }
        cout << endl;
    }
}

bool isSafe(int row, int col, int num, vector<vector<int>> &grid)
{
    for (int i = 0; i < N; i++)
    {
        if (grid[row][i] == num || grid[i][col] == num)
        {
            return false;
        }
    }
    int startRow = row - row % 3; // check if there is a number in square
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (grid[i + startRow][j + startCol] == num)
            {
                return false;
            }
        }
    }
    return true;
}

bool solveSudoku(std::vector<std::vector<int>> &grid) // solve the sudoku with only diagonal squares
{
    for (int row = 0; row < N; ++row)
    {
        for (int col = 0; col < N; ++col)
        {
            if (grid[row][col] == 0)
            {
                for (int num = 1; num <= 9; ++num)
                {
                    if (isSafe(row, col, num, grid))
                    {
                        grid[row][col] = num;
                        if (solveSudoku(grid))
                        {
                            return true;
                        }
                        grid[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void generateSudoku(std::vector<std::vector<int>> &grid)
{
    srand(time(NULL)); // fill the diagonal squares
    for (int i = 0; i < N; i += 3)
    {
        for (int num = 1; num <= N; ++num)
        {
            int row = i + rand() % 3;
            int col = i + rand() % 3;
            while (!isSafe(row, col, num, grid))
            {
                row = i + rand() % 3;
                col = i + rand() % 3;
            }
            grid[row][col] = num;
        }
    }

    solveSudoku(grid);
}

void hideElements(int difficulty, vector<vector<int>> &grid)
{
    switch (difficulty)
    {
    case 0: // fast completion
        for (int k = 0; k < 1; ++k)
        {
            int row = rand() % 8;
            int col = rand() % 8;
            while (grid[row][col] == 0)
            {
                row = rand() % 8;
                col = rand() % 8;
            }
            grid[row][col] = 0;
        }
        break;
    case 1:
        for (int k = 0; k < 20; ++k)
        {
            int row = rand() % 8;
            int col = rand() % 8;
            while (grid[row][col] == 0)
            {
                row = rand() % 8;
                col = rand() % 8;
            }
            grid[row][col] = 0;
        }
        break;
    case 2:
        for (int k = 0; k < 30; ++k)
        {
            int row = rand() % 8;
            int col = rand() % 8;
            while (grid[row][col] == 0)
            {
                row = rand() % 8;
                col = rand() % 8;
            }
            grid[row][col] = 0;
        }
        break;
    case 3:
        for (int k = 0; k < 45; ++k)
        {
            int row = rand() % 8;
            int col = rand() % 8;
            while (grid[row][col] == 0)
            {
                row = rand() % 8;
                col = rand() % 8;
            }
            grid[row][col] = 0;
        }
        break;
    }
}

bool gameEnd(vector<vector<int>> &grid)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (grid[i][j] == 0)
                return false;
        }
    }
    return true;
}

int main()
{
    srand(time(NULL));
    vector<vector<int>> grid(N, vector<int>(N, 0));
    greeting();
    cout << "Generating Sudoku puzzle..." << endl;
    generateSudoku(grid);
    int difficulty = difficultyLevel();
    hideElements(difficulty, grid);
    system("cls");

    // start of game
    int row;
    int col;
    int number;
    printGrid(grid);

    cout << "'q' to exit" << endl;
    cout << "Choose a row(vertical): ";
    cin >> row;
    cout << "Choose a col(horizontal): ";
    cin >> col;
    cout << "Choose a number(1 - 9): ";
    cin >> number;

    // start timer
    auto start = high_resolution_clock::now();
    int mistakes = 0;
    while (true)
    {
        if (row == 'q')
            break;

        if (gameEnd(grid))
            break;

        system("cls");

        if (grid[row - 1][col - 1] == 0 && (number <= 9 && number >= 1))
        {
            if (isSafe(row - 1, col - 1, number, grid))
            {
                grid[row - 1][col - 1] = number;
                printGrid(grid);
                cout << "Correct" << endl;
            }
            else
            {
                printGrid(grid);
                cout << "Wrong" << endl;
                mistakes++;
            }
        }
        else
            cout << "There is already a number or invalid input." << endl;

        cout << "Choose a row (or 'q'): ";
        cin >> row;
        cout << "Choose a col: ";
        cin >> col;
        cout << "Choose a number: ";
        cin >> number;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    int seconds = duration.count();
    int minutes = 0;
    int hours = 0;

    while (seconds >= 60)
    {
        if (seconds >= 60)
        {
            minutes++;

            if (minutes >= 60)
            {
                hours++;
                minutes -= 60;
            }

            seconds -= 60;
        }
    }

    cout << "Congratulations! You have done the game with " << mistakes << " mistakes" << endl;
    cout << "Time elapsed: " << hours << ":" << minutes << ":" << seconds << endl;
    char a;
    cout << "Do you want to play again? (y/n) ";
    cin >> a;
    if (a == 'y')
    {
        system("cls");
        main();
    }
    cout << "Thank you for playing Sudoku Puzzle Game!";
}