//
// Created by Woojin Lim on 2023/06/03.
//

#include "../util/headers.h"
#include "BoardView.h"

// 싱글톤 패턴 적용
BoardView &BoardView::getInstance()
{
    static BoardView _instance;

    return _instance;
}

// 특정 위치에 출력하는 함수
void BoardView::printOnPosition(int x, int y, std::string str, Align align)
{
    // 문자열을 가지고 x 좌표 계산
    x = getXPosition(x, str, align);

    // 필요한 위치로 이동후 출력
    gotoXY(x, y);
    print(str);
}

// x 좌표를 계산하는 함수
int BoardView::getXPosition(int x, std::string str, Align align)
{
    // string을 wstring으로 변환 (바이트 수 계산용)
    std::wstring wideString = std::wstring(str.begin(), str.end());

    // 한글 개수와 바이트 크기를 계산함
    int hangeulCount = static_cast<int>(std::strlen(str.c_str()) - std::wcslen(wideString.c_str())) / 2;
    int byteSize = static_cast<int>(std::wcslen(wideString.c_str()) + hangeulCount);

    // AlignType이 무엇인지에 따라 서로 다르게 연산
    switch (align)
    {
    case Align::LEFT:
        x = x - byteSize;
        break;
    case Align::CENTER:
        x = x - byteSize / 2;
        break;
    case Align::RIGHT:
        break;
    }

    // 왼쪽을 넘어갈 경우 보정
    if (x < 0)
    {
        x = 0;
    }

    return x;
}

// 화면 출력용 함수
void BoardView::print(std::string str)
{
    std::cout << str;
}

// 보드를 그려주는 함수
void BoardView::drawBoard(std::vector<int> boardData)
{
    std::pair<int, int> window_size = getWindowSize();

    int console_width = window_size.first;
    int console_height = window_size.second;

    // 출력하기 위해 보드 칸의 좌표를 지정해 줌
    int position[9][2] = {
        {console_width / 2 - 6, console_height / 2 - 3},
        {console_width / 2 + 0, console_height / 2 - 3},
        {console_width / 2 + 6, console_height / 2 - 3},
        {console_width / 2 - 6, console_height / 2 + 0},
        {console_width / 2 + 0, console_height / 2 + 0},
        {console_width / 2 + 6, console_height / 2 + 0},
        {console_width / 2 - 6, console_height / 2 + 3},
        {console_width / 2 + 0, console_height / 2 + 3},
        {console_width / 2 + 6, console_height / 2 + 3},
    };

    // 틀 출력
    printOnPosition(console_width / 2, console_height / 2 - 4, "     |     |     ", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 - 3, "     |     |     ", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 - 2, "_____|_____|_____", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 - 1, "     |     |     ", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 + 0, "     |     |     ", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 + 1, "_____|_____|_____", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 + 2, "     |     |     ", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 + 3, "     |     |     ", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 + 4, "     |     |     ", Align::CENTER);

    // 9개의 칸 모두 출력. 해당 칸의 값이 무엇인지에 따라 0, X, O 출력
    for (int i = 0; i < 9; ++i)
    {
        switch (boardData[i])
        {
        case 0:
            printOnPosition(position[i][0], position[i][1], std::to_string(boardData[i]), Align::CENTER);
            break;
        case 1:
            printOnPosition(position[i][0], position[i][1], "X", Align::CENTER);
            break;
        case 2:
            printOnPosition(position[i][0], position[i][1], "O", Align::CENTER);
            break;
        }
    }
}

// 밑줄을 아래 그린 상태로 보드 출력
void BoardView::drawBoardWithInput(std::vector<int> board)
{
    clearConsole();
    std::pair<int, int> window_size = getWindowSize();

    int console_width = window_size.first;
    int console_height = window_size.second;

    drawBoard(board);

    printOnPosition(console_width / 2, console_height / 2 + 14, "_______", Align::CENTER);
}

// 밑줄을 아래 그린 상태로 빈 보드 출력
void BoardView::drawBlankBoardWithInput()
{
    std::vector<int> boardData = {1, 2, 1, 2, 1, 2, 1, 2, 1};

    drawBoardWithInput(boardData);
}

// 메인 메뉴 출력
void BoardView::showMainMenu()
{
    std::pair<int, int> window_size = getWindowSize();
    clearConsole();

    int console_width = window_size.first;
    int console_height = window_size.second;

    drawBlankBoardWithInput();

    printOnPosition(console_width / 2, console_height / 2 + 8, "0: Exit program", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 + 9, "1: Play against computer", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 + 10, "2: Play against player", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 + 11, "3: Show scoreboard", Align::CENTER);
}

// 게임 순서를 입력받는 창 출력
void BoardView::showOrderInput()
{
    std::pair<int, int> window_size = getWindowSize();
    clearConsole();

    int console_width = window_size.first;
    int console_height = window_size.second;

    drawBlankBoardWithInput();

    printOnPosition(console_width / 2, console_height / 2 + 11, "1: First, 2: Second", Align::CENTER);
}

// 결과를 출력해 주는 창 출력
void BoardView::showScore(int result[2][3])
{
    std::pair<int, int> window_size = getWindowSize();

    int console_width = window_size.first;
    int console_height = window_size.second;

    clearConsole();

    printOnPosition(console_width / 2, console_height / 2 - 3, "|  W  |  D  |  L  |", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 - 2, "|-----|-----|-----|", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 - 1, "|     |     |     |", Align::CENTER);
    printOnPosition(console_width / 2 - 10, console_height / 2 - 1, "VS Computer", Align::LEFT);
    printOnPosition(console_width / 2, console_height / 2 + 0, "|-----|-----|-----|", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 + 1, "|     |     |     |", Align::CENTER);
    printOnPosition(console_width / 2 - 10, console_height / 2 + 1, "VS Player", Align::LEFT);
    printOnPosition(console_width / 2, console_height / 2 + 2, "|-----|-----|-----|", Align::CENTER);

    printOnPosition(console_width / 2 - 6, console_height / 2 - 1, std::to_string(result[0][0]), Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 - 1, std::to_string(result[0][1]), Align::CENTER);
    printOnPosition(console_width / 2 + 6, console_height / 2 - 1, std::to_string(result[0][2]), Align::CENTER);

    printOnPosition(console_width / 2 - 6, console_height / 2 + 1, std::to_string(result[1][0]), Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 + 1, std::to_string(result[1][1]), Align::CENTER);
    printOnPosition(console_width / 2 + 6, console_height / 2 + 1, std::to_string(result[1][2]), Align::CENTER);
}

// 게임의 결과를 출력해 주는 함수
void BoardView::printResult(std::vector<int> board, const char *str)
{
    std::pair<int, int> window_size = getWindowSize();

    int console_width = window_size.first;
    int console_height = window_size.second;

    clearConsole();

    drawBoard(board);

    printOnPosition(console_width / 2, console_height / 2 + 13, str, Align::CENTER);
}