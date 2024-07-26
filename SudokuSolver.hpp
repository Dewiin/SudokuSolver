/*************************************************************************
*               _________________________________________                * 
*               | Name: Devin Xie                       |                *
*               | SudokuSolver Project 6 interface      |                *
*               |_______________________________________|                *
*************************************************************************/

#ifndef SUDOKU_SOLVER_HPP_
#define SUDOKU_SOLVER_HPP_
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
using namespace std;

//We define Location within the Sudoku namespace.
//To use Location, you must specify the namespace Sudoku::Location
//Just like you do when using the standard namespace std::
namespace Sudoku
{ 
  struct Location
  {
    int row;
    int col;
  };
}

class SudokuSolver
{
public:
  /*
  the default constructor initializes an emtpy board, that is, a board filled with zeros 
  (an array of 9 arrays, each filled with 9 zeros). This board will be marked unsolvable. 
  */
  SudokuSolver();

  /*
  the parameterized constructor reads the input file to initialize the board. The input files consist of 9 digits 
  on each row separated by commas, and 9 rows separated by new line characters \n, corresponding to a sudoku board. Empty squares 
  contain the digit 0. After reading the puzzle, the constructor tries to solve it and records whether the puzzle has a solution or not. 
  TIP! We strongly suggest that you break down this task with the use of helper functions (reading the file, solving the puzzle etc.) and thoroughly test and debug each functionality separately.
  */
  SudokuSolver(string input_file);

  //solver helper function
  bool solve();
  
  /*
  returns true if the puzzle is solvable, false otherwise. We suggest you keep track of this when solving the 
  problem at construction, rather than solving the puzzle again each time this function is called.
  */
  bool isPuzzleSolvable();

  //records the puzzle as being solvable.
  void setSolvable(); 

  //returns the  2D pointer array representing the puzzle
  int** getPuzzleNumbers(); 

  //sets the 2D pointer array representing the puzzle to the value of the parameter 
  void setPuzzleNumbers(int** puzzle);

  /*
  returns a Location object with the coordinates of the first 0 found in the 2D pointer array, meaning that it is an empty square in the sudoku board. 
  To find the first empty square you must read the 2D array from top-left (0,0) to bottom right (8,8), one row at a time. Set the row and col of the Location
  to the indices at which the first 0 is found in the 2D array. If there are no empty squares the Location object should have row and col values of -1.
  */
  Sudoku::Location returnNextEmpty();

  /*
    checkLegalValue(int value, Sudoku::Location location) returns true if the value parameter (which can take on values 1-9) can legally be placed at the given location in the 2D array without 
    breaking the rules of sudoku. It returns false if placing value at location is not a legal move. Remember, in order to be a valid move, the value must be unique with a row, column, and sub-grid.
    Hint: to define the top-left corner of the sub-grid in which the location falls, integer division of the coordinates (row and col) by 3 will come in handy since all sub-grids are 3x3.
  */
  bool checkLegalValue(int value, Sudoku::Location location);

  //displays the board
  void display();

private:
//Add your private members here
  int** board;    //2D Array board
  int size;       //array size
  bool solvable;  //solvable boolean

};

#endif
