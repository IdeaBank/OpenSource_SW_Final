//
// Created by Woojin Lim on 2023/06/03.
//

#ifndef TICTACTOE_CPP_CONSOLEINFO_CPP
#define TICTACTOE_CPP_CONSOLEINFO_CPP

#include <utility>
#include "headers.h"

#ifdef _WIN32
#include <windows.h>

inline std::pair<int, int> getWindowSize()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return std::make_pair(columns, rows);
}

inline void clearConsole()
{
    system("cls");
}

inline void gotoXY(int x, int y)
{
    COORD pos = {(short)x, (short)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

#else
#include <unistd.h>
#include <sys/ioctl.h>

inline std::pair<int, int> getWindowSize()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    return std::make_pair(w.ws_col, w.ws_row);
}

inline void clearConsole()
{
    printf("\x1B[2J\x1B[0;0f");
}

inline void gotoXY(int x, int y)
{
    printf("\x1b[%d;%df", y, x);
}

#endif

#endif // TICTACTOE_CPP_CONSOLEINFO_CPP