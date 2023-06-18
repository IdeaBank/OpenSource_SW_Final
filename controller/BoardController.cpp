//
// Created by Woojin Lim on 2023/06/04.
//

#include "../util/headers.h"
#include "BoardController.h"

// 플레이 할 모드를 입력받는 함수
PlayMode BoardController::inputPlayMode()
{
    // 0에서 3까지 수를 입력 받음
    int input = inputOneDigitBetween(0, 3, ViewType::INPUT_PLAY_MODE);

    // 입력 받은 수에 따라 다른 게임 진행
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

// 입력될 때까지 대기하는 함수
void BoardController::waitInput()
{
    std::string temp;
    std::cin >> temp;
}

// 한 개의 숫자를 입력 받음 (0 ~ 9)
int BoardController::inputOneDigitBetween(int from, int to, ViewType viewType)
{
    std::pair<int, int> window_size = getWindowSize();

    int console_width = window_size.first;
    int console_height = window_size.second;

    // 임시로 문자열을 저장하는 변수
    std::string temp_str;

    // 무한 반복
    while (true)
    {
        // 화면 출력
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

        // 입력 받는 칸 위치로 감
        gotoXY(console_width / 2, console_height / 2 + 13);

        
        std::cin >> temp_str;

        // 입력 받은 문자열의 길이가 1이고 원하는 범위 안 이면 해당 숫자 반환, 아니면 계속 다시 입력 받음
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

// 시작점
void BoardController::start()
{
    // 0을 입력할 때까지 계속 반복 실행

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
    // playMode가 무엇인 지에 따라 다른 함수 실행
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
    // 순서를 입력 받음
    this->playOrder = inputOneDigitBetween(1, 2, ViewType::INPUT_ORDER);

    // 현재 턴과 게임의 결과를 저장하기 위한 변수 선언
    int currentTurn = 0;
    int result = 0;

    while (true)
    {
        // 보드를 그림
        BoardView::getInstance().drawBoardWithInput(this->boardData.getBoard());

        // 게임이 끝났으면
        result = hasGameEnded(this->boardData.getBoard());

        // 누군가가 이겼거나 비겼으면 게임 결과 저장 후 결과 출력
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

            // 게임이 끝났으므로 보드 초기화 후 결과 반환
            this->boardData.resetBoard();
            return result;
        }

        // 입력한 칸 위치를 저장하기 위한 변수
        int positionInput = 0;

        // 컴퓨터 턴이면 가장 좋은 수를 얻어 옴
        if (playMode == PlayMode::PVC && currentTurn % 2 + 1 != playOrder)
        {
            positionInput = calculateBestMove(this->playOrder % 2 + 1) + 1;
        }

        // PVC에서 내 턴이거나 PVP일 경우 수를 둘 칸을 입력 받음
        else
        {
            positionInput = inputOneDigitBetween(1, 9, ViewType::INPUT_BOARD_NUMBER);

            // 이미 칸이 차 있으면 다시 입력 받음
            while (!this->boardData.isCellEmpty(this->boardData.getBoard(), positionInput - 1))
            {
                positionInput = inputOneDigitBetween(1, 9, ViewType::INPUT_BOARD_NUMBER);
            }
        }

        // 입력한 칸에 수를 두고 턴을 1 증가시킴
        this->boardData.getBoard()[positionInput - 1] = currentTurn % 2 + 1;

        ++currentTurn;
    }

    return result;
}

// 결과를 보여주는 함수
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

    // 게임 종료 조건
    int combination[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

    // 플레이어 1 혹은 2가 이겼는 지 보기 위해 for문을 돌림
    for (int i = 1; i <= 2; ++i)
    {
        // 게임 종료 조건 탐색
        for (int j = 0; j < 8; ++j)
        {
            // 게임이 종료 되었으면 이긴 사람 반환
            if (board[combination[j][0]] == board[combination[j][1]] &&
                board[combination[j][1]] == board[combination[j][2]] &&
                board[combination[j][0]] != 0 && board[combination[j][0]] == i)
            {
                return i;
            }
        }
    }

    // 9칸이 다 찼을 경우 무승부 반환
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

    // 아니면 아직 안 끝났다는 것을 반환
    return 0;
}

// 최적의 수를 계산하는 함수
int BoardController::calculateBestMove(int botOrder)
{
    // 최고 점수를 -1000으로 설정
    int bestScore = -1000;
    int bestIndex = -1;

    // 9개의 칸을 모두 돎
    for (int i = 0; i < 9; ++i)
    {
        // 칸이 비어있으면
        if (this->boardData.isCellEmpty(this->boardData.getBoard(), i))
        {
            // 현재 보드를 복사해서 임시 보드를 만들고 보드의 해당 칸에 컴퓨터의 값을 넣음
            std::vector<int> tempBoard = std::vector<int>(boardData.getBoard());

            tempBoard[i] = botOrder;

            // miniMax 함수를 호출해 해당 칸의 점수를 얻음
            int miniMaxResult = miniMax(tempBoard, false, botOrder, 0);

            // 가장 최적의 수면 저장
            if (bestScore < miniMaxResult)
            {
                bestIndex = i;
                bestScore = miniMaxResult;
            }
        }
    }

    // 최적의 수 반환
    return bestIndex;
}

// 해당 칸의 점수를 얻기 위한 함수
int BoardController::miniMax(std::vector<int> &board, bool isMaximizing, int botOrder, int depth)
{
    // 게임이 끝났으면
    int result = hasGameEnded(board);

    // 비겼으면 0 반환
    if (result == 3)
    {
        return 0;
    }

    // 이겼으면 10 - depth 반환
    else if (result == botOrder)
    {
        return 10 - depth;
    }

    // 졌으면 depth - 10 반환
    else if (result == botOrder % 2 + 1)
    {
        return depth - 10;
    }

    // 아직 안 끝났으면
    else if (result == 0)
    {  
        // 컴퓨터 턴이면
        if (isMaximizing)
        {
            // 최고 점수를 -1000으로 설정
            int bestScore = -1000;

            // 9개의 칸을 모두 순회
            for (int i = 0; i < 9; ++i)
            {
                // 해당 칸이 비어 있으면
                if (this->boardData.isCellEmpty(board, i))
                {
                    // 현재 보드를 복사해 임시 보드를 만들고 해당 칸에 컴퓨터의 수를 둠
                    std::vector<int> tempBoard = std::vector<int>(board);
                    tempBoard[i] = botOrder;

                    // 임시 보드를 바탕으로 점수를 구함
                    int minimaxResult = miniMax(tempBoard, false, botOrder, depth + 1);

                    // 최고점보다 높으면 최고점에 저장
                    if (minimaxResult > bestScore)
                    {
                        bestScore = minimaxResult;
                    }
                }
            }

            // 최고점 반환
            return bestScore;
        }

        // 사용자 턴이면
        else
        {
            // 최저 점수를 1000으로 설정
            int worstScore = 1000;

            for (int i = 0; i < 9; ++i)
            {
                if (this->boardData.isCellEmpty(board, i))
                {
                    std::vector<int> tempBoard = std::vector<int>(board);
                    tempBoard[i] = botOrder % 2 + 1;

                    int minimaxResult = miniMax(tempBoard, true, botOrder, depth + 1);

                    if (minimaxResult < worstScore)
                        worstScore = minimaxResult;
                }
            }

            return worstScore;
        }
    }

    return 0;
}