/*************************************************************************
*               _________________________________________                * 
*               | Name: Devin Xie                       |                *
*               | SudokuSolver Project 6 implementation |                *
*               |_______________________________________|                *
*************************************************************************/


#include "SudokuSolver.hpp"

/*
  the default constructor initializes an emtpy board, that is, a board filled with zeros 
  (an array of 9 arrays, each filled with 9 zeros). This board will be marked unsolvable. 
*/
SudokuSolver::SudokuSolver()
{
    size = 9;
    board = new int*[size]; //dynamically create an array of pointers with 9 indices
    for(int i = 0; i < size; i++){
        //dynamically allocate memory of size 9 for each row
        board[i] = new int[size];
        for(int j = 0; j < size; j++){
            //assigning value of 0 to each allocated memory
            board[i][j] = 0;
        }
    }
    solvable = false; //marks the board unsolvable
}

/*
  the parameterized constructor reads the input file to initialize the board. The input files consist of 9 digits 
  on each row separated by commas, and 9 rows separated by new line characters \n, corresponding to a sudoku board. Empty squares 
  contain the digit 0. After reading the puzzle, the constructor tries to solve it and records whether the puzzle has a solution or not. 
  TIP! We strongly suggest that you break down this task with the use of helper functions (reading the file, solving the puzzle etc.) and thoroughly test and debug each functionality separately.
*/
SudokuSolver::SudokuSolver(string input_file)
{
    //initialize a board of zeros
    size = 9;
    board = new int*[size];
    for(int i = 0; i < size; i++){
        board[i] = new int[size];
        for(int j = 0; j < size; j++){
            board[i][j] = 0;
        }
    }

    //exception handling
    ifstream fin(input_file);
    if(fin.fail()){
        cerr << "Error. File can not be opened.";
        exit(1);
    }

    //reading csv file
    string line;
    int row = 0;

    while(getline(fin, line)){
        int col = 0;
        stringstream ss(line);
        string temp;

        while(getline(ss, temp, ',')){
            board[row][col] = stoi(temp);
            col++;
        }
        row++;
    }

    solvable = solve();
}

//solver helper function
bool SudokuSolver::solve(){
    Sudoku::Location empty = returnNextEmpty();

    //check for empty cells
    if((empty.row == -1) && (empty.col == -1)){
        return true; //if no more empty cells, return true
    }

    //try every value for empty cells
    for(int i = 1; i <= size; i++){
        //find legal value for empty cell
        if(checkLegalValue(i, empty)){
            board[empty.row][empty.col] = i;
            //recursion
            if(solve()){
                return true;
            }
        }
        board[empty.row][empty.col] = 0; //backtracking and trying new values if values don't work
    }
    return false;
}

/*
  returns true if the puzzle is solvable, false otherwise. We suggest you keep track of this when solving the 
  problem at construction, rather than solving the puzzle again each time this function is called.
*/
bool SudokuSolver::isPuzzleSolvable()
{
    return solvable;
}

//records the puzzle as being solvable.
void SudokuSolver::setSolvable()
{
    solvable = true;
}

//returns the  2D pointer array representing the puzzle
int** SudokuSolver::getPuzzleNumbers()
{
    return board;
}

//sets the 2D pointer array representing the puzzle to the value of the parameter 
void SudokuSolver::setPuzzleNumbers(int** puzzle)
{
    size = 9;
    //copy values from parameter to board
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            board[i][j] = puzzle[i][j];
        }
    }
}

/*
  returns a Location object with the coordinates of the first 0 found in the 2D pointer array, meaning that it is an empty square in the sudoku board. 
  To find the first empty square you must read the 2D array from top-left (0,0) to bottom right (8,8), one row at a time. Set the row and col of the Location
  to the indices at which the first 0 is found in the 2D array. If there are no empty squares the Location object should have row and col values of -1.
*/
Sudoku::Location SudokuSolver::returnNextEmpty()
{
    //default location if no empty cells
    Sudoku::Location location{-1, -1};

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            //if an empty cell is found, return new location
            if(board[i][j] == 0){
                location.row = i;
                location.col = j;
                return location;
            }
        }
    }
    return location;
}

/*
  checkLegalValue(int value, Sudoku::Location location) returns true if the value parameter (which can take on values 1-9) can legally be placed at the given location in the 2D array without 
  breaking the rules of sudoku. It returns false if placing value at location is not a legal move. Remember, in order to be a valid move, the value must be unique with a row, column, and sub-grid.
  Hint: to define the top-left corner of the sub-grid in which the location falls, integer division of the coordinates (row and col) by 3 will come in handy since all sub-grids are 3x3.
*/
bool SudokuSolver::checkLegalValue(int value, Sudoku::Location location)
{
    size = 9;
    int row = location.row;
    int col = location.col;

    //check if number is in same row or same column
    for(int i = 0; i < size; i++){
        if(board[row][i] == value){
            return false;
        }
        if(board[i][col] == value){
            return false;
        }
    }

    //check if number is in the same subgrid
    int rowSubgrid = (row/3) * 3;
    int colSubgrid = (col/3) * 3;

    for(int i = rowSubgrid; i < (rowSubgrid+3); i++){
        for(int j = colSubgrid; j < (colSubgrid+3); j++){
            if(board[i][j] == value){
                return false;
            }
        }
    }

    return true;
}

//displays the board
void SudokuSolver::display()
{   
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            //if the cell is empty
            if(board[i][j] == 0){
                cout << "X ";
            }
            //if the cell contains a number
            else{
                cout << board[i][j] << " ";
            }
            //separating every third column with '|'
            if(j % 3 == 2 && j != size-1){
                cout << " | ";
            }
        }
        cout << endl;
        //separating every third row with 12 dashes
        if(i % 3 == 2 && i != size-1){
            cout << "- - - - - - - - - - - -" << endl;
        }
    }
}

