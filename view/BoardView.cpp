//
// Created by Woojin Lim on 2023/06/03.
//

#include "../util/headers.h"
#include "BoardView.h"

BoardView &BoardView::getInstance()
{
    static BoardView _instance;

    return _instance;
}

void BoardView::printOnPosition(int x, int y, std::string str, Align align)
{
    x = getYPosition(x, str, align);
    gotoXY(x, y);
    print(str);
}

int BoardView::getYPosition(int x, std::string str, Align align)
{
    std::wstring wideString = std::wstring(str.begin(), str.end());

    int hangeulCount = static_cast<int>(std::strlen(str.c_str()) - std::wcslen(wideString.c_str())) / 2;
    int byteSize = static_cast<int>(std::wcslen(wideString.c_str()) + hangeulCount);

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

    if (x < 0)
    {
        x = 0;
    }

    return x;
}

void BoardView::print(std::string str)
{
    std::cout << str;
}

void BoardView::drawBoard(std::vector<int> boardData)
{

    std::pair<int, int> window_size = getWindowSize();

    int console_width = window_size.first;
    int console_height = window_size.second;

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

    printOnPosition(console_width / 2, console_height / 2 - 4, "     |     |     ", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 - 3, "     |     |     ", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 - 2, "_____|_____|_____", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 - 1, "     |     |     ", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 + 0, "     |     |     ", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 + 1, "_____|_____|_____", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 + 2, "     |     |     ", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 + 3, "     |     |     ", Align::CENTER);
    printOnPosition(console_width / 2, console_height / 2 + 4, "     |     |     ", Align::CENTER);

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

void BoardView::drawBoardWithInput(std::vector<int> board)
{
    clearConsole();
    std::pair<int, int> window_size = getWindowSize();

    int console_width = window_size.first;
    int console_height = window_size.second;

    drawBoard(board);

    printOnPosition(console_width / 2, console_height / 2 + 14, "_______", Align::CENTER);
}

void BoardView::drawBlankBoardWithInput()
{
    std::vector<int> boardData = {1, 2, 1, 2, 1, 2, 1, 2, 1};

    drawBoardWithInput(boardData);
}

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

void BoardView::showOrderInput()
{
    std::pair<int, int> window_size = getWindowSize();
    clearConsole();

    int console_width = window_size.first;
    int console_height = window_size.second;

    drawBlankBoardWithInput();

    printOnPosition(console_width / 2, console_height / 2 + 11, "1: First, 2: Second", Align::CENTER);
}

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

void BoardView::printResult(std::vector<int> board, const char *str)
{
    std::pair<int, int> window_size = getWindowSize();

    int console_width = window_size.first;
    int console_height = window_size.second;

    clearConsole();

    drawBoard(board);

    printOnPosition(console_width / 2, console_height / 2 + 13, str, Align::CENTER);
}