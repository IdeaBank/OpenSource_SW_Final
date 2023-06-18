# TicTacToe

Tic Tac Toe 게임입니다.

## Installation

### MACOS

1. 해당 Repository를 클론합니다.

```bash
git clone https://github.com/IdeaBank/OpenSource_SW_Final.git
```

2. CMake를 설치합니다.

```bash
brew install cmake
```

3. Repository 내에서 build를 진행합니다.

```bash
cd OpenSource_SW_Final
cmake CMakeLists.txt
make
```

4. 프로그램을 실행시킵니다.

```bash
./TicTacToe_CPP
```

![캡쳐0](/images/capture0.png)

### Windows
1. Visual Studio Installer에서 Windows용 C++ CMake 도구를 설치합니다.

![캡쳐1](/images/capture1.png)

2. Visual Studio에서 클론한 폴더를 엽니다.

![캡쳐2](/images/capture2.png)

3. 시작 항목 선택 -> TicTacToe_CPP.exe를 누르고, TicTacToc_CPP.exe를 눌러 빌드를 진행하고 프로그램을 실행시킵니다.

![캡쳐3](/images/capture4.png)

![캡쳐4](/images/capture3.png)

## How to use program

1. 프로그램을 실행시키면 다음과 같이 모드를 입력하는 창이 나오게 됩니다.

![프로그램0](/images/program_0.png)

2. 1을 눌러 Play against computer에 들어갈 경우, 먼저 플레이어의 순서를 입력하게 됩니다.

![프로그램1](/images/program_1.png)

![프로그램2](/images/program_2.png)

3. 플레이어의 순서를 1로 설정할 경우, 먼저 수를 두게 됩니다.

![프로그램3](/images/program_3.png)

4. 게임을 계속 진행해 게임 결과를 얻습니다. 아무 키나 입력하고 엔터 키를 누를 경우 메인 화면으로 돌아갑니다.

![프로그램4](/images/program_4.png)

![프로그램5](/images/program_5.png)

5. 2를 눌러 Play against player에 들어갈 경우, 플레이어(현재 플레이어)의 순서를 입력하게 됩니다.

![프로그램6](/images/program_6.png)

6. Play against computer와 마찬가지로 게임을 계속 진행해 결과를 얻으면 이를 저장하고 표시해줍니다.

아무 키나 입력하고 엔터 키를 누를 경우 메인 화면으로 돌아갑니다.

![프로그램7](/images/program_7.png)

7. 3을 입력하면 현재 게임 결과를 표시해줍니다.
 
아무 키나 입력하고 엔터 키를 누를 경우 메인 화면으로 돌아갑니다.

![프로그램8](/images/program_8.png)

8. 0을 입력하면 프로그램을 종료합니다.

![프로그램9](/images/program_9.png)

---

### 주의사항

입력을 대기할 때에는 엔터키만 누른다고 해서 다음으로 넘어가지 않습니다. 

꼭 아무 문자나 입력하고 엔터 키를 누르셔야 합니다.

---

## How to use code

### header.h
```cpp
#include <util/header.h
```

프로젝트에서 필요한 헤더파일은 `header.h` 에 포함되어 있습니다.

### BoardController

```cpp
BoardController *boardController = new BoardController()
boardController->start();
```

BoardController의 인스턴스를 생성하고 start 함수를 호출해 게임을 시작합니다.

### BoardView

```cpp
BoardView::getInstance().[함수명]
```

BoardView는 싱글톤 패턴을 적용했으므로 getInstance()함수를 호출해 인스턴스를 받아오고 이를 통해 함수를 호출합니다.
