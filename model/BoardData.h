//
// Created by Woojin Lim on 2023/06/03.
//

#ifndef TICTACTOE_CPP_BOARDDATA_H
#define TICTACTOE_CPP_BOARDDATA_H

#include <vector>

class BoardData
{
public:
    BoardData();
    void resetBoard();
    bool isCellEmpty(std::vector<int>, int);
    std::vector<int> &getBoard();
    std::vector<int> copyBoard();

private:
    std::vector<int> board;
};

#endif // TICTACTOE_CPP_BOARDDATA_H
