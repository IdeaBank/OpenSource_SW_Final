//
// Created by Woojin Lim on 2023/06/04.
//

#include "../util/headers.h"
#include "BoardController.h"

PlayMode BoardController::inputPlayMode()
{
    int input = inputOneDigitBetween(0, 3, ViewType::INPUT_PLAY_MODE);

    switch (input)
    {
    case 0:
        return PlayMode::END;
    case 1:
        return PlayMode::PVC;
    case 2:
        return PlayMode::PVP;
    case 3:
        return PlayMode::SHOW_SCORE;
    }

    return PlayMode::END;
}

void BoardController::waitInput()
{
    std::string temp;
    std::cin >> temp;
}

int BoardController::inputOneDigitBetween(int from, int to, ViewType viewType)
{
    std::pair<int, int> window_size = getWindowSize();

    int console_width = window_size.first;
    int console_height = window_size.second;

    std::string temp_str;

    while (true)
    {
        switch (viewType)
        {
        case ViewType::INPUT_PLAY_MODE:
            BoardView::getInstance().showMainMenu();
            break;
        case ViewType::INPUT_ORDER:
            BoardView::getInstance().showOrderInput();
            break;
        case ViewType::INPUT_BOARD_NUMBER:
            BoardView::getInstance().drawBoardWithInput(this->boardData.getBoard());
            break;
        }

        gotoXY(console_width / 2, console_height / 2 + 13);

        std::cin >> temp_str;

        if (temp_str.length() == 1)
        {
            const char *str = temp_str.c_str();

            if (from + '0' <= str[0] && str[0] <= to + '0')
            {
                return str[0] - '0';
            }
        }
    }

    return 0;
}

void BoardController::start()
{
    bool playAgain = false;

    while (this->playMode != PlayMode::END)
    {
        this->playMode = inputPlayMode();

        if (this->playMode != PlayMode::END)
        {
            startGame();
        }
    }
}

void BoardController::startGame()
{
    int result = -1;

    switch (this->playMode)
    {
    case PlayMode::PVP:
    case PlayMode::PVC:
        playGame(this->playMode);
        break;

    case PlayMode::SHOW_SCORE:
        showScore();
        break;

    case PlayMode::END:
        return;
    }
}

int BoardController::playGame(PlayMode playMode)
{
    this->playOrder = inputOneDigitBetween(1, 2, ViewType::INPUT_ORDER);

    int currentTurn = 0;
    int result = 0;

    while (true)
    {
        BoardView::getInstance().drawBoardWithInput(this->boardData.getBoard());

        result = hasGameEnded(this->boardData.getBoard());

        if (result == 1 || result == 2 || result == 3)
        {
            if (result == 3)
            {
                if (playMode == PlayMode::PVC)
                {
                    this->gameResult[0][1] += 1;
                }

                else if (playMode == PlayMode::PVP)
                {
                    this->gameResult[1][1] += 1;
                }

                BoardView::getInstance().printResult(this->boardData.getBoard(), "Draw");
                waitInput();
            }

            else
            {
                if (playMode == PlayMode::PVC)
                {
                    if (result == playOrder)
                    {
                        this->gameResult[0][0] += 1;

                        BoardView::getInstance().printResult(this->boardData.getBoard(), "Player won!");
                        waitInput();
                    }

                    else
                    {
                        this->gameResult[0][2] += 1;

                        BoardView::getInstance().printResult(this->boardData.getBoard(), "Player lost!");
                        waitInput();
                    }
                }

                else if (playMode == PlayMode::PVP)
                {
                    if (result == playOrder)
                    {
                        this->gameResult[1][0] += 1;

                        BoardView::getInstance().printResult(this->boardData.getBoard(), "Player won!");
                        waitInput();
                    }

                    else
                    {
                        this->gameResult[1][2] += 1;

                        BoardView::getInstance().printResult(this->boardData.getBoard(), "Player lost!");
                        waitInput();
                    }
                }
            }

            this->boardData.resetBoard();
            return result;
        }

        int positionInput = 0;

        if (playMode == PlayMode::PVC && currentTurn % 2 + 1 != playOrder)
        {
            positionInput = calculateBestMove(this->playOrder % 2 + 1) + 1;
        }

        else
        {
            positionInput = inputOneDigitBetween(1, 9, ViewType::INPUT_BOARD_NUMBER);

            while (!this->boardData.isCellEmpty(this->boardData.getBoard(), positionInput - 1))
            {
                positionInput = inputOneDigitBetween(1, 9, ViewType::INPUT_BOARD_NUMBER);
            }
        }

        this->boardData.getBoard()[positionInput - 1] = currentTurn % 2 + 1;

        ++currentTurn;
    }

    return result;
}

void BoardController::showScore()
{
    BoardView::getInstance().showScore(this->gameResult);
    waitInput();
}

int BoardController::hasGameEnded(std::vector<int> board)
{
    // 0: NO
    // 1: FIRST
    // 2: SECOND
    // 3: DRAW

    int combination[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

    for (int i = 1; i <= 2; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (board[combination[j][0]] == board[combination[j][1]] &&
                board[combination[j][1]] == board[combination[j][2]] &&
                board[combination[j][0]] != 0 && board[combination[j][0]] == i)
            {
                return i;
            }
        }
    }

    int count = 0;

    for (int i = 0; i < 9; ++i)
    {
        if (board[i] != 0)
        {
            count += 1;
        }
    }

    if (count == 9)
    {
        return 3;
    }

    return 0;
}

int BoardController::calculateBestMove(int botOrder)
{
    int bestScore = -1000;
    int bestIndex = -1;

    for (int i = 0; i < 9; ++i)
    {
        if (this->boardData.isCellEmpty(this->boardData.getBoard(), i))
        {
            std::vector<int> tempBoard = std::vector<int>(boardData.getBoard());

            tempBoard[i] = botOrder;

            int miniMaxResult = miniMax(tempBoard, false, botOrder, 0);

            if (bestScore < miniMaxResult)
            {
                bestIndex = i;
                bestScore = miniMaxResult;
            }
        }
    }

    return bestIndex;
}

int BoardController::miniMax(std::vector<int> &board, bool isMaximizing, int botOrder, int depth)
{
    int result = hasGameEnded(board);

    if (result == 3)
    {
        return 0;
    }

    else if (result == botOrder)
    {
        return 10 - depth;
    }

    else if (result == botOrder % 2 + 1)
    {
        return depth - 10;
    }

    else if (result == 0)
    {
        if (isMaximizing)
        {
            int bestScore = -1000;

            for (int i = 0; i < 9; ++i)
            {
                if (this->boardData.isCellEmpty(board, i))
                {
                    std::vector<int> tempBoard = std::vector<int>(board);
                    tempBoard[i] = botOrder;

                    int minimaxResult = miniMax(tempBoard, false, botOrder, depth + 1);

                    if (minimaxResult > bestScore)
                    {
                        bestScore = minimaxResult;
                    }
                }
            }

            return bestScore;
        }

        else
        {
            int bestScore = 1000;

            for (int i = 0; i < 9; ++i)
            {
                if (this->boardData.isCellEmpty(board, i))
                {
                    std::vector<int> tempBoard = std::vector<int>(board);
                    tempBoard[i] = botOrder % 2 + 1;

                    int minimaxResult = miniMax(tempBoard, true, botOrder, depth + 1);

                    if (minimaxResult < bestScore)
                        bestScore = minimaxResult;
                }
            }

            return bestScore;
        }
    }

    return 0;
}