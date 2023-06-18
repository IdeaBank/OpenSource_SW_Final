//
// Created by Woojin Lim on 2023/06/03.
//

#include "../util/headers.h"
#include "BoardData.h"

BoardData::BoardData()
{
    this->resetBoard();
}

void BoardData::resetBoard()
{
    this->board = {0, 0, 0, 0, 0, 0, 0, 0, 0};
}

bool BoardData::isCellEmpty(std::vector<int> board, int index)
{
    return board[index] == 0;
}

std::vector<int> &BoardData::getBoard()
{
    return this->board;
}

std::vector<int> BoardData::copyBoard()
{
    std::vector<int> temp_board(this->board);

    return temp_board;
}