//
// Created by Woojin Lim on 2023/06/04.
//

#ifndef TICTACTOE_CPP_BOARDCONTROLLER_H
#define TICTACTOE_CPP_BOARDCONTROLLER_H

class BoardController
{
private:
    PlayMode playMode;
    BoardData boardData;
    int playOrder;
    int gameResult[2][3] = {{0, 0, 0}, {0, 0, 0}};

public:
    BoardController() = default;
    PlayMode inputPlayMode();
    void waitInput();
    int inputOneDigitBetween(int, int, ViewType);
    void start();
    void startGame();
    int playGame(PlayMode);
    void showScore();
    int hasGameEnded(std::vector<int>);
    int calculateBestMove(int);
    int miniMax(std::vector<int> &, bool, int, int);
};

#endif // TICTACTOE_CPP_BOARDCONTROLLER_H
