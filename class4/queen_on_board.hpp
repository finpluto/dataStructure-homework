#ifndef QUEEN_ON_BOARD_HPP_
#define QUEEN_ON_BOARD_HPP_

class ChessBoard {
  private:
    bool *column_;
    bool *main_diagonal_;
    bool *sub_diagonal_;
    int *queens_column_;
    int chessboard_length_;
    int cout_of_solution_;
    void PrintChessBoard();
    bool IsAreaInControl(int row, int column);
    void PlaceAQueen(int row);
  public:
    ChessBoard() {};
    ChessBoard(int chessboard_length);
    ~ChessBoard();
    void CalculateAndOutput();
};

#endif
