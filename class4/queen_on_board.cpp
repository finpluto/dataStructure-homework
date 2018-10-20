#include "queen_on_board.hpp"
#include <iostream>
using std::cout;

ChessBoard::ChessBoard(int chessboard_length) {
    cout_of_solution_ = 0;
    chessboard_length_ = chessboard_length;
    column_ = new bool[chessboard_length_]{false};
    queens_column_ = new int[chessboard_length_]{-1};
    main_diagonal_ = new bool[2*chessboard_length_-1]{false};
    sub_diagonal_ = new bool[2*chessboard_length_-1]{false};
}

ChessBoard::~ChessBoard() {
    delete[] column_;
    delete[] queens_column_;
    delete[] main_diagonal_;
    delete[] sub_diagonal_;
}

void ChessBoard::PrintChessBoard() {
    for(int i=0; i<chessboard_length_; i++) {
        if(!column_[i]) {
            for(int j=0; j<chessboard_length_; j++) {
                cout << "[#]";
            }
            cout << '\n';
        }
        else {
            for(int j=0; j<queens_column_[i]; j++) {
                cout << "[#]";
            }
            cout << "[Q]";
            for(int j=queens_column_[i]+1; j<chessboard_length_; j++) {
                cout << "[#]";
            }
            cout << '\n';
        }
    }
}

bool ChessBoard::IsAreaInControl(int row, int column) {
    int index_of_main_diagonal = chessboard_length_ + row - column - 1;
    int index_of_sub_diagonal = row + column;

    return main_diagonal_[index_of_main_diagonal] ||
        sub_diagonal_[index_of_sub_diagonal] ||
        column_[column];
}

void ChessBoard::PlaceAQueen(int row) {
    for(int column=0; column<chessboard_length_; column++) {
        if(!IsAreaInControl(row,column)) {
            queens_column_[row] = column;
            main_diagonal_[chessboard_length_+row-column-1] = true;
            sub_diagonal_[row+column] = true;
            column_[column] = true;
            if(row == chessboard_length_-1) {
                PrintChessBoard();
                cout << '\n';
                cout_of_solution_ += 1;
            }
            else {
                PlaceAQueen(row+1);
            }
            queens_column_[row] = -1;
            main_diagonal_[chessboard_length_+row-column-1] = false;
            sub_diagonal_[row+column] = false;
            column_[column] = false;
        }
    }
}

void ChessBoard::CalculateAndOutput() {
    PlaceAQueen(0);
    cout << "\nThere're " << cout_of_solution_ << " solutions in total.\n";
}
