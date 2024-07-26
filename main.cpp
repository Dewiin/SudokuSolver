#include "SudokuSolver.hpp"

int main(){
    SudokuSolver* puzzle1 = new SudokuSolver("puzzle1.csv");

    puzzle1->solve();

    puzzle1 -> display();
}