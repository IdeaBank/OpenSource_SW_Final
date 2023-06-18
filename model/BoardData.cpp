//
// Created by Woojin Lim on 2023/06/03.
//

#include "../util/headers.h"
#include "BoardData.h"

BoardData::BoardData()
{
    // 생성사 호출시 현재 보드 초기화
    this->resetBoard();
}

void BoardData::resetBoard()
{
    // 현재 보드를 0으로 초기화 함
    this->board = {0, 0, 0, 0, 0, 0, 0, 0, 0};
}

bool BoardData::isCellEmpty(std::vector<int> board, int index)
{
    // 보드의 해당 칸이 비어있는지 여부 반환
    return board[index] == 0;
}

std::vector<int> &BoardData::getBoard()
{
    // 보드의 reference 반환
    return this->board;
}

std::vector<int> BoardData::copyBoard()
{
    // 보드를 복사해서 반환
    std::vector<int> temp_board(this->board);

    return temp_board;
}