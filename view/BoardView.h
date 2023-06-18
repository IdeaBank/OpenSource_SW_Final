//
// Created by Woojin Lim on 2023/06/03.
//

#ifndef TICTACTOE_CPP_BOARDVIEW_H
#define TICTACTOE_CPP_BOARDVIEW_H

#include "../AlignType.h"
#include "../util/headers.h"

class BoardView
{
private:
    BoardView() = default;
    BoardView(const BoardView &) = default;
    BoardView &operator=(const BoardView &) = default;
    ~BoardView() = default;

public:
    static BoardView &getInstance();
    void printOnPosition(int, int, std::string, Align);
    int getYPosition(int, std::string, Align);
    void print(std::string);
    void drawBoard(std::vector<int>);
    void drawBoardWithInput(std::vector<int>);
    void drawBlankBoardWithInput();
    void showMainMenu();
    void showOrderInput();
    void showScore(int[2][3]);
    void printResult(std::vector<int>, const char *);
};

#endif // TICTACTOE_CPP_BOARDVIEW_H